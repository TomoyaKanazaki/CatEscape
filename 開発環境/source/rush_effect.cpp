//==========================================
//
//  連撃エフェクト(rush_effect.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "rush_effect.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CRush::CRush(int nPriority) : CObject2D_Anim(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CRush::~CRush()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CRush::Init()
{
	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::RUSH));

	// アニメーションを設定
	SetAnim(10, 4, false, TYPE_V);

	// サイズを設定
	m_size = D3DXVECTOR3(FLOAT_SCREEN_WIDTH, FLOAT_SCREEN_HEIGHT, 0.0f);

	// 位置を設定
	m_pos = D3DXVECTOR3(FLOAT_SCREEN_WIDTH * 0.5f, FLOAT_SCREEN_HEIGHT * 0.5f, 0.0f);

	return CObject2D_Anim::Init();
}

//==========================================
//  終了処理
//==========================================
void CRush::Uninit()
{
	CObject2D_Anim::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CRush::Update()
{
	CObject2D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CRush::Draw()
{
	CObject2D_Anim::Draw();
}

//==========================================
//  生成処理
//==========================================
CRush* CRush::Create()
{
	// インスタンス生成
	CRush* pRush = new CRush;

	// 初期化処理
	pRush->Init();

	return pRush;
}
