//==========================================
//
//  スティックぐりぐりUI(stick.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "stick.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "gamemanager.h"
#include "stick_base.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 STICKPOS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f); // 位置
	const D3DXVECTOR3 STICKSIZE = D3DXVECTOR3(100.0f, 100.0f, 0.0f); // 位置
	const float STICK_DEAD = 0.0f; // デッドゾーン
	const float CENTER_DISTANCE = 30.0f; // 中心から離れられる距離
}

//==========================================
//  コンストラクタ
//==========================================
CStick::CStick(int nPriority) : CObject2D(nPriority)
{
}

//==========================================
//  デストラクタ
//==========================================
CStick::~CStick()
{
}

//==========================================
//  初期化処理
//==========================================
HRESULT CStick::Init(void)
{
	// 座標を設定
	m_pos = STICKPOS;

	// 大きさを設定
	m_size = STICKSIZE;

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::STICK));

	// 中心を設定
	CBase::Create(STICKPOS);

	return CObject2D::Init();
}

//==========================================
//  終了処理
//==========================================
void CStick::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CStick::Update(void)
{
	// スティックの入力を取得
	D3DXVECTOR3 rot = CManager::GetInstance()->GetJoyPad()->GetStickR(STICK_DEAD);
	D3DXVec3Normalize(&rot, &rot);

	// 位置を反映する
	m_pos.x = STICKPOS.x + (rot.x * CENTER_DISTANCE);
	m_pos.y = STICKPOS.y - (rot.z * CENTER_DISTANCE);

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
void CStick::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CStick* CStick::Create()
{
	// インスタンス生成
	CStick* pStick = new CStick;

	// NULLチェック
	if (pStick == nullptr) { return nullptr; }

	// 初期化処理
	pStick->Init();

	return pStick;
}
