//==========================================
//
//  メッシュオブジェクトクラス(object_mesh.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object_mesh.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CObject_Mesh::CObject_Mesh(int nPriority) : CObject(nPriority),
m_bOrbit(false)
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_Mesh.nNumIdx = 0;
	m_Mesh.nNumMesh = 0;
	m_Mesh.nNumMesh_U = 0;
	m_Mesh.nNumMesh_V = 0;
	m_Mesh.nNumVtx = 0;
	m_Mesh.nNumVtx_U = 0;
	m_Mesh.nNumVtx_V = 0;
	m_mtxWorld = {};
	m_pTexture = NULL;
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Patern = NORMAL;
}

//==========================================
//  デストラクタ
//==========================================
CObject_Mesh::~CObject_Mesh()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CObject_Mesh::Init(void)
{
	//頂点生成用変数の設定
	CalcData();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4 * m_Mesh.nNumMesh,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);

	//頂点バッファの情報を設定
	SetVtx();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * m_Mesh.nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL
	);

	//インデックスバッファの情報を設定
	SetIdx();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CObject_Mesh::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CObject_Mesh::Update(void)
{

}

//==========================================
//  描画処理
//==========================================
void CObject_Mesh::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 軌跡専用の処理
	if (m_bOrbit)
	{
		//アルファテストの有効化
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		//アルファブレンディングを加算合成に設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		//Zテストの無効化
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		//ライティングを無効化
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//カリングを無効化
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	//ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive
	(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_Mesh.nNumVtx, //頂点数
		0,
		m_Mesh.nNumMesh //プリミティブ数
	);

	//カリングを有効化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファブレンディングの設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  生成処理
//==========================================
CObject_Mesh * CObject_Mesh::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR2 uv)
{
	//インスタンス生成
	CObject_Mesh *pMesh = NULL;

	//NULLチェック
	if (pMesh == NULL)
	{
		//メモリを確保
		pMesh = new CObject_Mesh;
	}

	if (pMesh == NULL)
	{
		return NULL;
	}

	//分割数を設定
	pMesh->m_Mesh.nNumMesh_U = (int)uv.x;
	pMesh->m_Mesh.nNumMesh_V = (int)uv.y;
	pMesh->m_pos = pos;
	pMesh->m_size = size;
	pMesh->m_rot = rot;
	pMesh->m_Color = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);

	//初期化
	pMesh->Init();

	//ポインタを返す
	return pMesh;
}

//==========================================
//  頂点バッファの設定処理
//==========================================
void CObject_Mesh::SetVtx(void)
{
	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_Mesh.nNumVtx; nCntVtx++)
	{
		//法線の設定
		pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[nCntVtx].col = m_Color;
	}	

	//頂点座標の設定
	for (int nCntVtxU = 0; nCntVtxU < m_Mesh.nNumVtx_U; nCntVtxU++)
	{
		for (int nCntVtxV = 0; nCntVtxV < m_Mesh.nNumVtx_V; nCntVtxV++)
		{
			pVtx[nCntVtxU + (nCntVtxV * m_Mesh.nNumVtx_U)].pos = D3DXVECTOR3
			(
				-(m_size.x * 0.5f) + ((m_size.x / m_Mesh.nNumMesh_U) * nCntVtxU),
				0.0f,
				(m_size.z * 0.5f) - ((m_size.z / m_Mesh.nNumMesh_V) * nCntVtxV)
			);

			//テクスチャ座標の設定
			switch (m_Patern)
			{
			case NORMAL:
				pVtx[nCntVtxU + (nCntVtxV * m_Mesh.nNumVtx_U)].tex = D3DXVECTOR2((float)(nCntVtxU % m_Mesh.nNumVtx_U), (float)(nCntVtxV % m_Mesh.nNumVtx_V));
				break;
			case LOOP:
				pVtx[nCntVtxU + (nCntVtxV * m_Mesh.nNumVtx_U)].tex = D3DXVECTOR2((float)(nCntVtxU % 2), (float)(nCntVtxV % m_Mesh.nNumVtx_V));
				break;
			default:
				break;
			}
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  インデックスバッファの設定処理
//==========================================
void CObject_Mesh::SetIdx(void)
{
	//インデックス情報へのポインタ
	WORD *pIdx;

	//インデックスバッファをロックし、頂点番号データへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点データの設定
	for (int nCntIdx = 0, nCntTurn = 0, nCntVtx = 0; nCntIdx < m_Mesh.nNumIdx; nCntIdx += 2)
	{
		if (nCntIdx == (2 * ((m_Mesh.nNumVtx_U * nCntTurn) + m_Mesh.nNumVtx_U + nCntTurn))) //折り返し地点
		{
			pIdx[nCntIdx] = pIdx[nCntIdx - 1];
			pIdx[nCntIdx + 1] = nCntVtx + m_Mesh.nNumVtx_U;
			nCntTurn++;
		}
		else //その他
		{
			pIdx[nCntIdx] = nCntVtx + m_Mesh.nNumVtx_U;
			pIdx[nCntIdx + 1] = nCntVtx;
			nCntVtx++;
		}
	}

	//インデックスバッファのアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  各データの計算処理
//==========================================
void CObject_Mesh::CalcData(void)
{
	m_Mesh.nNumVtx_U = m_Mesh.nNumMesh_U + 1;
	m_Mesh.nNumVtx_V = m_Mesh.nNumMesh_V + 1;
	m_Mesh.nNumVtx = m_Mesh.nNumVtx_U * m_Mesh.nNumVtx_V;
	m_Mesh.nNumIdx = (m_Mesh.nNumVtx * 2) - (2 * (abs(m_Mesh.nNumMesh_U - m_Mesh.nNumMesh_V)) + 4);
	if (m_Mesh.nNumMesh_U < m_Mesh.nNumMesh_V)
	{
		m_Mesh.nNumIdx += (m_Mesh.nNumMesh_V - m_Mesh.nNumMesh_U) * 4;
	}
	m_Mesh.nNumMesh = m_Mesh.nNumIdx - 2;
}

//==========================================
//  メッシュフィールド上の存在判定(判定のみ)
//==========================================
bool CObject_Mesh::OnMesh(const D3DXVECTOR3 pos)
{
	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//上の存在判定
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_U - 1; nCnt++)
	{
		int IdxStart = nCnt; //左
		int IdxEnd = nCnt + 1; //右
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//範囲外だった場合false
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//下の存在判定
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_U - 1; nCnt++)
	{
		int IdxStart = (m_Mesh.nNumVtx_U * m_Mesh.nNumMesh_V) + nCnt + 1; //右
		int IdxEnd = IdxStart - 1; //左
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//範囲外だった場合false
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//右の判定
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V - 1; nCnt++)
	{
		int IdxStart = (nCnt + 1) * m_Mesh.nNumVtx_U - 1; //上
		int IdxEnd = IdxStart + m_Mesh.nNumVtx_U; //下
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//範囲外だった場合false
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//左の判定
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V - 1; nCnt++)
	{
		int IdxEnd = nCnt * m_Mesh.nNumVtx_V; //上
		int IdxStart = IdxEnd + m_Mesh.nNumVtx_U; //下
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//範囲外だった場合false
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return true;
}

//==========================================
//  メッシュフィールド上の存在判定(押し戻し)
//==========================================
bool CObject_Mesh::OnMesh(const D3DXVECTOR3 pos, const D3DXVECTOR3 oldpos, D3DXVECTOR3 *pVecLine, D3DXVECTOR3 *pVecToPos)
{
	//ローカル変数宣言
	//int nCntPoint = 0;

	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//上の存在判定
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_U - 1; nCnt++)
	{
		int IdxStart = nCnt; //左
		int IdxEnd = nCnt + 1; //右
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//範囲外だった場合false
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			*pVecLine = posEnd - posStart;
			*pVecToPos = posEnd - oldpos;

			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//下の存在判定
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_U - 1; nCnt++)
	{
		int IdxStart = (m_Mesh.nNumVtx_U * m_Mesh.nNumMesh_V) + nCnt + 1; //右
		int IdxEnd = IdxStart - 1; //左
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//範囲外だった場合false
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			*pVecLine = posEnd - posStart;
			*pVecToPos = posEnd - oldpos;

			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//右の判定
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V - 1; nCnt++)
	{
		int IdxStart = (nCnt + 1) * m_Mesh.nNumVtx_U - 1; //上
		int IdxEnd = IdxStart + m_Mesh.nNumVtx_U; //下
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//範囲外だった場合false
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			*pVecLine = posEnd - posStart;
			*pVecToPos = posEnd - oldpos;

			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//左の判定
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx_V - 1; nCnt++)
	{
		int IdxEnd = nCnt * m_Mesh.nNumVtx_V; //上
		int IdxStart = IdxEnd + m_Mesh.nNumVtx_U; //下
		D3DXVECTOR3 posStart = pVtx[IdxStart].pos;
		D3DXVECTOR3 posEnd = pVtx[IdxEnd].pos;

		//範囲外だった場合false
		if (CheckOnMesh(pos, posStart, posEnd))
		{
			*pVecLine = posEnd - posStart;
			*pVecToPos = posEnd - oldpos;

			//頂点バッファをアンロック
			m_pVtxBuff->Unlock();
			return false;
		}
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
	
	return true;
}

//==========================================
//  頂点座標の更新
//==========================================
void CObject_Mesh::SetVtxPos(const D3DXVECTOR3 pos, const int nIdx)
{
	//インデックスをチェック
	if (nIdx < m_Mesh.nNumVtx)
	{
		//頂点バッファの呼び出し
		VERTEX_3D *pVtx;

		//頂点バッファをロック
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//インデックスを指定して頂点座標を変更する
		pVtx[nIdx].pos = pos;

		//頂点バッファをアンロック
		m_pVtxBuff->Unlock();
	}
}

//==========================================
//  色の設定
//==========================================
void CObject_Mesh::SetColor(D3DXCOLOR col)
{
	//色を保存
	m_Color = col;

	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_Mesh.nNumVtx; nCntVtx++)
	{
		//頂点カラーの設定
		pVtx[nCntVtx].col = m_Color;
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  テクスチャ座標の更新
//==========================================
void CObject_Mesh::AddTexPos(D3DXVECTOR2 AddTex)
{
	//頂点バッファの呼び出し
	VERTEX_3D* pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標を加算
	for (int nCnt = 0; nCnt < m_Mesh.nNumVtx; nCnt++)
	{
		pVtx[nCnt].tex += AddTex;
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  判定
//==========================================
bool CObject_Mesh::CheckOnMesh(const D3DXVECTOR3 &posJudge, const D3DXVECTOR3 &posStart, const D3DXVECTOR3 &posEnd) const
{
	return (posEnd.z - posStart.z) * (posJudge.x - posStart.x) - (posEnd.x - posStart.x) * (posJudge.z - posStart.z) < 0.0f;
}
