//==========================================
//
//  3Dポリゴンのエフェクト(effect3D.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "effect3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CEffect3D::CEffect3D()
{

}

//==========================================
//  デストラクタ
//==========================================
CEffect3D::~CEffect3D()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEffect3D::Init(void)
{
	// テクスチャを割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::EFFECT));

	// 初期化
	return CObject3D::Init();
}

//==========================================
//  終了処理
//==========================================
void CEffect3D::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEffect3D::Update(void)
{
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CEffect3D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//描画
	CObject3D::Draw();

	//アルファブレンディングの設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CEffect3D* CEffect3D::Create(D3DXVECTOR3 pos, bool BillBoard)
{
	// インスタンス生成
	CEffect3D* pEffect = new CEffect3D;

	// NULLチェック
	if (pEffect == NULL) { return nullptr; }

	// 値を設定
	pEffect->m_pos = pos; // 座標
	pEffect->SwitchBillboard(BillBoard); // ビルボード設定

	// 初期化処理
	if (FAILED(pEffect->Init())) { return nullptr; }

	// 値を返す
	return pEffect;
}
