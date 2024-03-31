//==========================================
//
//  斬撃エフェクト(slash_effect.cpp)
//  Author : Chaba
//
//==========================================
#include "slash_effect.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "gametime.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const int NUM_TEXTURE = 1; // 斬撃エフェクトのテクスチャ数
	const int MIN_SIZE = 100; // 大きさの下限値
	const int MAX_SIZE = 200; // 大きさの上限値
	const float CLEAR_TIME = 5.0f; // 1 / n 秒で消える
	const float ALPHA = 0.7f; // 透明度
}

//==========================================
//  コンストラクタ
//==========================================
CSlash_Effect::CSlash_Effect(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CSlash_Effect::~CSlash_Effect()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CSlash_Effect::Init(void)
{
	m_size = D3DXVECTOR3(MAX_SIZE, MAX_SIZE, MAX_SIZE);

	D3DXVECTOR3 rot;
	rot.x = (float)(rand() % 629 - 314) * 0.01f;
	rot.y = (float)(rand() % 629 - 314) * 0.01f;
	rot.z = (float)(rand() % 629 - 314) * 0.01f;
	m_rot.x = rot.x;
	m_rot.y = rot.y;
	m_rot.z = rot.z;

	// 透明度設定
	m_col.a = ALPHA;

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::SLASH));

	// アニメーションを設定
	SetAnim(12, 2, false, TYPE_U);

	// 初期化
	return CObject3D_Anim::Init();
}

//==========================================
//  終了処理
//==========================================
void CSlash_Effect::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CSlash_Effect::Update(void)
{
	// 更新する
	CObject3D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CSlash_Effect::Draw(void)
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
CSlash_Effect* CSlash_Effect::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXCOLOR& col)
{
	// インスタンス生成
	CSlash_Effect* pSlash = new CSlash_Effect;

	// NULLチェック
	if (pSlash == nullptr) { return nullptr; }

	// 値の設定
	pSlash->m_pos = pos;
	pSlash->m_rot = rot;
	pSlash->m_col = col;

	// 初期化処理
	pSlash->Init();

	// 値を返す
	return pSlash;
}
