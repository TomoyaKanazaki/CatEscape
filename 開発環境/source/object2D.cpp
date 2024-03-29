//==========================================
//
//  オブジェクト2Dクラス(object2D.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object2D.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

//==========================================
//  コンストラクタ
//==========================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//==========================================
//  デストラクタ
//==========================================
CObject2D::~CObject2D()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CObject2D::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetInstance()->GetRenderer()->GetDevice();

	//ローカル変数宣言
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
	m_fAngle = atan2f(m_size.x, m_size.y);

	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	)))
	{
		return E_FAIL;
	}

	//頂点バッファの呼び出し
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3
	(
		m_pos.x + sinf((m_rot.z + m_fAngle) - D3DX_PI) * m_fLength,
		m_pos.y + cosf((m_rot.z + m_fAngle) - D3DX_PI) * m_fLength,
		0.0f
	);
	pVtx[1].pos = D3DXVECTOR3
	(
		m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f
	);
	pVtx[2].pos = D3DXVECTOR3
	(
		m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength,
		m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength,
		0.0f
	);
	pVtx[3].pos = D3DXVECTOR3
	(
		m_pos.x + sinf((m_rot.z + m_fAngle)) * m_fLength,
		m_pos.y + cosf((m_rot.z + m_fAngle)) * m_fLength,
		0.0f
	);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CObject2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CObject2D::Update(void)
{
	//対角線 / 2の計算
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
	m_fAngle = atan2f(m_size.x, m_size.y);

	//頂点バッファの呼び出し
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3
	(
		m_pos.x + sinf((m_rot.z + m_fAngle) - D3DX_PI) * m_fLength,
		m_pos.y + cosf((m_rot.z + m_fAngle) - D3DX_PI) * m_fLength,
		0.0f
	);
	pVtx[1].pos = D3DXVECTOR3
	(
		m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f
	);
	pVtx[2].pos = D3DXVECTOR3
	(
		m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength,
		m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength,
		0.0f
	);
	pVtx[3].pos = D3DXVECTOR3
	(
		m_pos.x + sinf((m_rot.z + m_fAngle)) * m_fLength,
		m_pos.y + cosf((m_rot.z + m_fAngle)) * m_fLength,
		0.0f
	);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  描画処理
//==========================================
void CObject2D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetInstance()->GetRenderer()->GetDevice();

	//Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//==========================================
//  テクスチャ座標の変更
//==========================================
void CObject2D::SetTex(D3DXVECTOR2 min, D3DXVECTOR2 max)
{
	//頂点バッファの呼び出し
	VERTEX_2D *pVtx;

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
void CObject2D::SetCol(const D3DXCOLOR col)
{
	//色を設定する
	m_col = col;

	//頂点バッファの呼び出し
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//設定した色の適用
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].col = m_col;
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//==========================================
//  透明度の変更
//==========================================
void CObject2D::AddAlpah(float fDiff)
{
	//透明度を加算
	m_col.a += fDiff;

	//頂点バッファの呼び出し
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//設定した色の適用
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pVtx[nCnt].col = m_col;
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}
