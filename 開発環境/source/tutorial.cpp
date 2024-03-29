//==========================================
//
//  操作方法(tutorial.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial.h"
#include "enemymanager.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 TUTORIAL_SIZE = D3DXVECTOR3(225.0f, 63.0f, 0.0f); // ポリゴンサイズ
	const D3DXVECTOR3 TUTORIAL_POS = D3DXVECTOR3(117.0f, 44.0f, 0.0f); // ポリゴン座標
}

//==========================================
//  静的メンバ変数宣言
//==========================================
int CTutorial::m_nIdx = 0;

//==========================================
//  コンストラクタ
//==========================================
CTutorial::CTutorial(int nPriority) : CObject2D(nPriority)
{
}

//==========================================
//  デストラクタ
//==========================================
CTutorial::~CTutorial()
{
	--m_nIdx;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CTutorial::Init(void)
{
	// 位置を設定
	m_pos = TUTORIAL_POS;
	m_pos.y += TUTORIAL_SIZE.y * m_nIdx; 

	// 大きさを設定
	m_size = TUTORIAL_SIZE;

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::TUTORIAL0 + m_nIdx));

	// インデックス加算
	++m_nIdx;

	return CObject2D::Init();
}

//==========================================
//  終了処理
//==========================================
void CTutorial::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTutorial::Update(void)
{
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CTutorial::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CTutorial* CTutorial::Create()
{
	// インスタンス生成
	CTutorial* pTutorial = new CTutorial;

	// NULLチェック
	if (pTutorial == nullptr) { return nullptr; }

	// 初期化処理
	pTutorial->Init();

	return pTutorial;
}
