//==========================================
//
//  爆散エフェクト(splash.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "splash.h"
#include "manager.h"
#include "renderer.h"
#include "gametime.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "slash_effect.h"

//==========================================
//  コンストラクタ
//==========================================
CSplash::CSplash(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CSplash::~CSplash()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CSplash::Init(void)
{
	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::SPLASH));

	// アニメーションを設定
	SetAnim(14, 2, false, TYPE_U);

	// 初期化
	return CObject3D_Anim::Init();
}

//==========================================
//  終了処理
//==========================================
void CSplash::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CSplash::Update(void)
{
	// 更新する
	CObject3D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CSplash::Draw(void)
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
	CObject3D_Anim::Draw();

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
CSplash* CSplash::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const D3DXCOLOR& col)
{
	// インスタンス生成
	CSplash* pSplash = new CSplash;

	// NULLチェック
	if (pSplash == nullptr) { return nullptr; }

	// 値の設定
	pSplash->m_pos = pos;
	pSplash->m_rot = rot;
	pSplash->m_size = size;
	pSplash->m_col = col;

	// 初期化処理
	pSplash->Init();

	// 値を返す
	return pSplash;
}
