//==========================================
//
//  ヒット時のエフェクト(hit_effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "hit_effect.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 EFFECT_SIZE = D3DXVECTOR3(200.0f, 200.0f, 200.0f); // サイズ
}

//==========================================
//  コンストラクタ
//==========================================
CHitEffect::CHitEffect(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CHitEffect::~CHitEffect()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CHitEffect::Init(void)
{
	// サイズを設定
	m_size = EFFECT_SIZE;

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::HIT));

	// アニメーションを設定
	SetAnim(15, 1, false, TYPE_U);

	return CObject3D_Anim::Init();
}

//==========================================
//  終了処理
//==========================================
void CHitEffect::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CHitEffect::Update(void)
{
	CObject3D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CHitEffect::Draw(void)
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

	//カリングを無効化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CObject3D_Anim::Draw();

	//カリングを有効化
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

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
CHitEffect* CHitEffect::Create(const D3DXVECTOR3& pos)
{
	// インスタンス生成
	CHitEffect* pEffect = new CHitEffect;

	// NULLチェック
	if (pEffect == nullptr) { return nullptr; }

	// 位置を設定
	pEffect->m_pos = pos;

	// 初期化処理
	pEffect->Init();

	return pEffect;
}
