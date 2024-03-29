//==========================================
//
//  オブジェクト3Dクラス(object3D.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object3D.h"
#include "manager.h"
#include "renderer.h"
#include "gamemanager.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const D3DXVECTOR3 CObject3D::mc_sizeExplosion = D3DXVECTOR3(30.0f, 30.0f, 30.0f);

//==========================================
//  コンストラクタ
//==========================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_mtxWorld = {};
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bBillboard = false;
}

//==========================================
//  デストラクタ
//==========================================
CObject3D::~CObject3D()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CObject3D::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ローカル変数宣言
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
	m_fAngle = (m_size.x, m_size.y);

	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	)))
	{
		return E_FAIL;
	}

	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (GetType() == TYPE_FIELD )
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_size.x * 0.5f, 0.0f, m_size.y * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_size.x * 0.5f, 0.0f, m_size.y * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(-m_size.x * 0.5f, 0.0f, -m_size.y * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_size.x * 0.5f, 0.0f, -m_size.y * 0.5f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_size.x * 0.5f, m_size.y * 0.5f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_size.x * 0.5f, m_size.y * 0.5f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	//頂点カラーの設定
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].col = m_col;
	}

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	m_oldPos = m_pos;

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CObject3D::Uninit(void)
{
	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CObject3D::Update(void)
{
	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//サイズの更新
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
	m_fAngle = (m_size.y, m_size.x);

	if (GetType() == TYPE_FIELD)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_size.x * 0.5f, 0.0f, m_size.y * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_size.x * 0.5f, 0.0f, m_size.y * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(-m_size.x * 0.5f, 0.0f, -m_size.y * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_size.x * 0.5f, 0.0f, -m_size.y * 0.5f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_size.x * 0.5f, m_size.y * 0.5f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_size.x * 0.5f, m_size.y * 0.5f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	//頂点カラーの設定
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].col = m_col;
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	m_oldPos = m_pos;
}

//==========================================
//  描画処理
//==========================================
void CObject3D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans, mtxView; //計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビルボードを作る
	if (m_bBillboard)
	{
		//ビューマトリックスの取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラに対して正面に向ける
		D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);

		//値の補正
		m_mtxWorld._41 = m_pos.x;
		m_mtxWorld._42 = m_pos.y;
		m_mtxWorld._43 = m_pos.z;
	}
	else
	{
		//向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置の反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	}

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//==========================================
//  テクスチャ座標の変更
//==========================================
void CObject3D::SetTex(D3DXVECTOR2 min, D3DXVECTOR2 max)
{
	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(min.x, min.y);
	pVtx[1].tex = D3DXVECTOR2(max.x, min.y);
	pVtx[2].tex = D3DXVECTOR2(min.x, max.y);
	pVtx[3].tex = D3DXVECTOR2(max.x, max.y);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  色の設定
//==========================================
void CObject3D::SetCol(const D3DXCOLOR col)
{
	//色を設定する
	m_col = col;

	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//設定した色の適用
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  不透明度の設定
//==========================================
void CObject3D::SetAlpha(const float fAlpha)
{
	if (fAlpha > 1.0f)
	{
		m_col.a = 1.0f;
	}
	else if (fAlpha < 0.0f)
	{
		m_col.a = 0.0f;
	}
	else
	{
		m_col.a = fAlpha;
	}
}

//==========================================
//  高さを取得する処理
//==========================================
float CObject3D::GetHeight(const D3DXVECTOR3 TargetPos)
{
	//ローカル変数宣言
	D3DXVECTOR3 VtxPos[4]; //頂点の位置を保存する
	D3DXVECTOR3 NorPlane[2]; //対象になる法線
	float fHeight = 0.0f; //返り値

	//頂点バッファの呼び出し
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの頂点を取得
	VtxPos[0] = pVtx[0].pos;
	VtxPos[1] = pVtx[1].pos;
	VtxPos[2] = pVtx[2].pos;
	VtxPos[3] = pVtx[3].pos;

	//法線を取得
	NorPlane[0] = pVtx[0].nor;
	NorPlane[1] = pVtx[3].nor;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	if
		(
			((VtxPos[1].z - VtxPos[0].z) * (TargetPos.x - VtxPos[0].x)) - ((VtxPos[1].x - VtxPos[0].x) * (TargetPos.z - VtxPos[0].z)) > 0.0f &&
			((VtxPos[2].z - VtxPos[1].z) * (TargetPos.x - VtxPos[1].x)) - ((VtxPos[2].x - VtxPos[1].x) * (TargetPos.z - VtxPos[1].z)) > 0.0f &&
			((VtxPos[0].z - VtxPos[2].z) * (TargetPos.x - VtxPos[2].x)) - ((VtxPos[0].x - VtxPos[2].x) * (TargetPos.z - VtxPos[2].z)) > 0.0f
		)
	{
		//法線が垂直でない場合
		if (NorPlane[0].y != 0.0f)
		{
			fHeight = (-(TargetPos.x * NorPlane[0].x + TargetPos.z * NorPlane[0].z) + (VtxPos[0].x * NorPlane[0].x + VtxPos[0].y * NorPlane[0].y + VtxPos[0].z * NorPlane[0].z)) / NorPlane[0].y;
		}
	}

	if
		(
			((VtxPos[2].z - VtxPos[3].z) * (TargetPos.x - VtxPos[3].x)) - ((VtxPos[2].x - VtxPos[3].x) * (TargetPos.z - VtxPos[3].z)) > 0.0f &&
			((VtxPos[1].z - VtxPos[2].z) * (TargetPos.x - VtxPos[2].x)) - ((VtxPos[1].x - VtxPos[2].x) * (TargetPos.z - VtxPos[2].z)) > 0.0f &&
			((VtxPos[3].z - VtxPos[1].z) * (TargetPos.x - VtxPos[1].x)) - ((VtxPos[3].x - VtxPos[1].x) * (TargetPos.z - VtxPos[1].z)) > 0.0f
		)
	{
		//法線が垂直でない場合
		if (NorPlane[1].y != 0.0f)
		{
			fHeight = (-(TargetPos.x * NorPlane[1].x + TargetPos.z * NorPlane[1].z) + (VtxPos[3].x * NorPlane[1].x + VtxPos[3].y * NorPlane[1].y + VtxPos[3].z * NorPlane[1].z)) / NorPlane[1].y;
		}
	}

	return fHeight;
}

//==========================================
//  当たり判定
//==========================================
bool CObject3D::Collision(CObject::TYPE type)
{
	//ローカル変数宣言
	bool bHit = false;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//自分のアドレスを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			if (pObj->GetType() == type)
			{
				//頂点バッファの呼び出し
				VERTEX_3D *pVtx;

				//頂点バッファをロック
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//判定に必要なベクトルを算出する
				D3DXVECTOR3 vecToPos = pObj->GetPos() - (m_pos + D3DXVECTOR3(cosf(-m_rot.y) * pVtx[0].pos.x, 0.0f, sinf(-m_rot.y) * pVtx[0].pos.z));
				D3DXVECTOR3 vecToMove = pObj->GetPos() - pObj->GetOldPos();
				D3DXVECTOR3 vecVtx = (m_pos + D3DXVECTOR3(cosf(m_rot.y) * pVtx[1].pos.x, 0.0f, sinf(m_rot.y) * pVtx[1].pos.z)) - (m_pos + D3DXVECTOR3(cosf(-m_rot.y) * pVtx[0].pos.x, 0.0f, sinf(-m_rot.y) * pVtx[0].pos.z));
				D3DXVECTOR3 posBase = (m_pos + D3DXVECTOR3(cosf(-m_rot.y) * pVtx[0].pos.x, 0.0f, sinf(-m_rot.y) * pVtx[0].pos.z));

				//頂点バッファをアンロック
				m_pVtxBuff->Unlock();

				//交点の計算に必要な値を算出
				float fPosMove = (vecToPos.z * vecToMove.x) - (vecToPos.x * vecToMove.z);
				float fVtxMove = (vecVtx.z * vecToMove.x) - (vecVtx.x * vecToMove.z);
				float fRate = fPosMove / fVtxMove;

				//接触を判定する
				if (0.0f <= fRate && fRate <= 1.0f)
				{
					bHit = true;
				}
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}

	//値を返す
	return bHit;
}

//==========================================
//  当たり判定
//==========================================
bool CObject3D::Collision(CObject::TYPE type, D3DXVECTOR3 *pCrossPoint)
{
	//ローカル変数宣言
	bool bHit = false;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//自分のアドレスを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			if (pObj->GetType() == type)
			{
				//頂点バッファの呼び出し
				VERTEX_3D *pVtx;

				//頂点バッファをロック
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//判定に使用する頂点の座標を取得
				D3DXVECTOR3 Vtx0 = (m_pos + D3DXVECTOR3(cosf(m_rot.y) * pVtx[0].pos.x, 0.0f, sinf(m_rot.y) * pVtx[0].pos.y));
				D3DXVECTOR3 Vtx3 = (m_pos + D3DXVECTOR3(cosf(m_rot.y) * pVtx[3].pos.x, 0.0f, sinf(m_rot.y) * pVtx[3].pos.y));

				//頂点バッファをアンロック
				m_pVtxBuff->Unlock();

				//判定対象の前回と今回の座標を取得
				D3DXVECTOR3 pos = pObj->GetPos();
				D3DXVECTOR3 posOld = pObj->GetOldPos();

				//判定に必要なベクトルを算出する
				D3DXVECTOR3 vecToPos = pos - Vtx0; //頂点から今回の座標
				D3DXVECTOR3 vecToMove = pos - posOld; //前回の座標から今回の座標
				D3DXVECTOR3 vecVtx = Vtx3 - Vtx0; //左端の頂点から右端の頂点

				//接触を判定する
				if ((Vtx3.z - Vtx0.z) * (pos.x - Vtx0.x) - (Vtx3.x - Vtx0.x) * (pos.z - Vtx0.z) < 0.0f)
				{
					//交点の計算に必要な値を算出
					float fPosMove = (vecToPos.z * vecToMove.x) - (vecToPos.x * vecToMove.z);
					float fVtxMove = (vecVtx.z * vecToMove.x) - (vecVtx.x * vecToMove.z);
					float fRate = fPosMove / fVtxMove;

					//交点がに頂点間にあった場合
					if (0.0f <= fRate && fRate <= 1.0f)
					{
						//接触フラグを立てる
						bHit = true;

						//交点を算出
						D3DXVECTOR3 CrossPoint = Vtx0 + (vecVtx * fRate);
						CrossPoint.y = 0.0f;
						*pCrossPoint = CrossPoint;
						pObj->SetPos(CrossPoint);

						//対象のオブジェクトを破棄
						pObj->Uninit();
					}
				}
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}

	//値を返す
	return bHit;
}
