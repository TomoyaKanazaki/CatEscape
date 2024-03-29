//==========================================
//
//  スティックぐりぐりUI(stick_base.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "stick_base.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "gamemanager.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 STICKSIZE = D3DXVECTOR3(80.0f, 80.0f, 0.0f); // 位置
}

//==========================================
//  コンストラクタ
//==========================================
CBase::CBase(int nPriority) : CObject2D(nPriority)
{
}

//==========================================
//  デストラクタ
//==========================================
CBase::~CBase()
{
}

//==========================================
//  初期化処理
//==========================================
HRESULT CBase::Init(void)
{
	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::BASE));

	// 大きさを設定
	m_size = STICKSIZE;

	return CObject2D::Init();
}

//==========================================
//  終了処理
//==========================================
void CBase::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBase::Update(void)
{
	CObject2D::Update();

	// 終了
	if (CGameManager::GetState() == CGameManager::STATE_END)
	{
		Uninit();
	}
}

//==========================================
//  描画処理
//==========================================
void CBase::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CBase* CBase::Create(const D3DXVECTOR3& pos)
{
	// インスタンス生成
	CBase* pBase = new CBase;

	// NULLチェック
	if (pBase == nullptr) { return pBase; }

	// 数値を設定
	pBase->m_pos = pos;

	// 初期化処理
	pBase->Init();

	return pBase;
}
