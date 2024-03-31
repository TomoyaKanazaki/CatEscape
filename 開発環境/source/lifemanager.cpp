//==========================================
//
//  体力表示の管理クラス(lifemanager.cpp)
//  Author : Chaba
//
//==========================================
#include "lifemanager.h"
#include "manager.h"
#include "gamemanager.h"
#include "player.h"
#include "texture.h"
#include "life.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 FRAME_SIZE = D3DXVECTOR3(600.0f, 100.0f, 0.0f);
	const D3DXVECTOR3 FRAME_POS = D3DXVECTOR3(300.0f, FLOAT_SCREEN_HEIGHT - 50.0f, 0.0f);
}

//==========================================
//  コンストラクタ
//==========================================
CLifeManager::CLifeManager(int nPriority) : CObject2D(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CLifeManager::~CLifeManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CLifeManager::Init(void)
{
	// サイズを設定
	m_size = FRAME_SIZE;

	// 位置を設定
	m_pos = FRAME_POS;

	// 初期化
	HRESULT hr = CObject2D::Init();

	// 色を設定
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::PLAYER_FRAME));

	// 体力を表示
	for (int i = 0; i < 10; ++i)
	{
		CLife::Create();
	}

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CLifeManager::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CLifeManager::Update(void)
{
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CLifeManager::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CLifeManager* CLifeManager::Create()
{
	// インスタンス生成
	CLifeManager* pLife = new CLifeManager;

	// 初期化処理
	pLife->Init();

	return pLife;
}
