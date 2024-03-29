//==========================================
//
//  体力表示の管理クラス(enemylifemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemylifemanager.h"
#include "manager.h"
#include "gamemanager.h"
#include "player.h"
#include "texture.h"
#include "enemylife.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 FRAME_SIZE = D3DXVECTOR3(600.0f, 100.0f, 0.0f);
	const D3DXVECTOR3 FRAME_POS = D3DXVECTOR3(FLOAT_SCREEN_WIDTH - 300.0f, 50.0f, 0.0f);
}

//==========================================
//  コンストラクタ
//==========================================
CEnemyLifeManager::CEnemyLifeManager(int nPriority) : CObject2D(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyLifeManager::~CEnemyLifeManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyLifeManager::Init(void)
{
	// サイズを設定
	m_size = FRAME_SIZE;

	// 位置を設定
	m_pos = FRAME_POS;

	// 向きを設定
	m_rot.z = D3DX_PI;

	// 初期化
	HRESULT hr = CObject2D::Init();

	// 色を設定
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ENEMY_FRAME));

	// 体力表示
	for (int i = 0; i < 5; ++i)
	{
		CEnemyLife::Create();
	}

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CEnemyLifeManager::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyLifeManager::Update(void)
{
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemyLifeManager::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CEnemyLifeManager* CEnemyLifeManager::Create()
{
	// インスタンス生成
	CEnemyLifeManager* pLife = new CEnemyLifeManager;

	// 初期化処理
	pLife->Init();

	return pLife;
}
