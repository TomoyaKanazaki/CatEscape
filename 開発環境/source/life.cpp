//==========================================
//
//  体力表示(life.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "life.h"
#include "manager.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 LIFE_SIZE = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	const D3DXVECTOR3 LIFE_LEFT_POS = D3DXVECTOR3(30.0f, FLOAT_SCREEN_HEIGHT - 45.0f, 0.0f);
}

//==========================================
//  静的メンバ変数宣言
//==========================================
int CLife::m_nNum = 0; // 体力

//==========================================
//  コンストラクタ
//==========================================
CLife::CLife(int nPriority) : CObject2D(nPriority),
m_nIdx(m_nNum)
{
	++m_nNum;
}

//==========================================
//  デストラクタ
//==========================================
CLife::~CLife()
{
	--m_nNum;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CLife::Init(void)
{
	// サイズを設定
	m_size = LIFE_SIZE;

	// 位置を設定
	m_pos = LIFE_LEFT_POS;
	m_pos.x += LIFE_SIZE.x * m_nIdx;

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::LEAF));

	return CObject2D::Init();
}

//==========================================
//  終了処理
//==========================================
void CLife::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CLife::Update(void)
{
	// プレイヤーのライフを取得
	int nLife = CGameManager::GetPlayer()->GetLife();

	// プレイヤーのライフが自分を上回っていたら消す
	if (m_nIdx + 1 > nLife)
	{
		Uninit();
		return;
	}

	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CLife::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CLife* CLife::Create()
{
	// インスタンス生成
	CLife* pLife = new CLife;

	// 初期化処理
	pLife->Init();

	return pLife;
}
