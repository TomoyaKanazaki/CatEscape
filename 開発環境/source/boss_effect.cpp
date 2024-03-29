//==========================================
//
//  ボス出現エフェクト(boss_effect.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss_effect.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 EFFECT_SIZE = D3DXVECTOR3(500.0f, 500.0f, 500.0f); // エフェクトの大きさ
}

//==========================================
//  コンストラクタ
//==========================================
CBossEffect::CBossEffect(int nPriority) : CObject3D_Anim(nPriority),
m_TexIdx(0)
{

}

//==========================================
//  デストラクタ
//==========================================
CBossEffect::~CBossEffect()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBossEffect::Init(void)
{
	// サイズを設定
	m_size = EFFECT_SIZE;

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::BOSS1));

	// アニメーションを設定
	SetAnim(8, 3, false, TYPE_U);

	return CObject3D_Anim::Init();
}

//==========================================
//  終了処理
//==========================================
void CBossEffect::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBossEffect::Update(void)
{
	CObject3D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CBossEffect::Draw(void)
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

	CObject3D_Anim::Draw();

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
CBossEffect* CBossEffect::Create(const D3DXVECTOR3& pos)
{
	// インスタンス生成
	CBossEffect* pEffect = new CBossEffect;

	// NULLチェック
	if (pEffect == nullptr) { return nullptr; }

	// 値を設定
	pEffect->m_pos = pos;

	// 初期化処理
	pEffect->Init();

	return pEffect;
}
