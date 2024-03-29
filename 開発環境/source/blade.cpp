//==========================================
//
//  刀弾クラス(blade.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "blade.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "gametime.h"
#include "camera.h"
#include "orbit.h"
#include "motion.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float MOVE_SPEED = 300.0f; // 単位時間当たりの移動量
	const float WAIT_TIME = 1.0f; // 出現後移動するまでの待機時間
	const float HIT_LENGTH = 60.0f; // 判定距離
	const float ROTATE_SPEED = 0.1f;
}

//==========================================
//  コンストラクタ
//==========================================
CBlade::CBlade(int nPriority) : CObject_Char(nPriority),
m_rotation(0.0f),
m_Time(0.0f),
m_pOrbit(nullptr)
{
}

//==========================================
//  デストラクタ
//==========================================
CBlade::~CBlade()
{
}

//==========================================
//  初期化処理
//==========================================
HRESULT CBlade::Init(void)
{
	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::BLADE);

	// 初期化処理
	HRESULT hr = CObject_Char::Init();

	// 移動量の設定
	SetMove();

	// 剣に軌跡を付ける
	if (m_pOrbit == nullptr)
	{
		m_pOrbit = COrbit::Create(m_ppModel[0], D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, -50.0f), 10);
		m_pOrbit->SwitchDraw(false);
	}

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CBlade::Uninit(void)
{
	CObject_Char::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBlade::Update(void)
{
	// デルタタイムを取得
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// 出現時間を加算
	m_Time += m_fDeltaTime;

	// 移動量の適用
	if (m_Time >= WAIT_TIME)
	{
		m_pos += m_move * m_fDeltaTime;
		m_pOrbit->SwitchDraw(true);
	}

	// 回転
	m_rot.x += m_Time * ROTATE_SPEED;

	// 当たり判定
	Hit();

	CObject_Char::Update();

	// 画面外で削除
	if (!CGameManager::GetCamera()->OnScreen(m_pos))
	{
		m_pOrbit->SwitchDraw(false);
		Uninit();
	}
}

//==========================================
//  描画処理
//==========================================
void CBlade::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  生成処理
//==========================================
CBlade* CBlade::Create(const D3DXVECTOR3& pos)
{
	// インスタンス生成
	CBlade* pBullet = new CBlade;

	// NULLチェック
	if (pBullet == nullptr) { return nullptr; }

	// 位置を設定
	pBullet->m_pos = pos;

	// 初期化処理
	pBullet->Init();

	return pBullet;
}

//==========================================
//  移動量の設定
//==========================================
void CBlade::SetMove()
{
	// プレイヤーの座標を取得
	D3DXVECTOR3 vec = CGameManager::GetPlayer()->GetCenterPos() - m_pos;
	
	//右に進む時は右を向く
	if (vec.x > 0.0f)
	{
		m_rot.y = -D3DX_PI * 0.5f;
	}

	//左に進むときは左を向く
	if (vec.x < 0.0f)
	{
		m_rot.y = D3DX_PI * 0.5f;
	}

	// ベクトルを正規化
	D3DXVec3Normalize(&vec, &vec);

	// 単位時間当たりの移動量を適用する
	m_move = vec * MOVE_SPEED;
}

//==========================================
//  当たり判定
//==========================================
void CBlade::Hit()
{
	// プレイヤーへのベクトルを算出
	D3DXVECTOR3 vec = CGameManager::GetPlayer()->GetCenterPos() - m_pos;
	vec.z = 0.0f;

	// 距離を測る
	if (HIT_LENGTH * HIT_LENGTH > vec.x * vec.x + vec.y * vec.y)
	{
		// 当たっていた時の処理
		CGameManager::GetPlayer()->Attacked();
	}
}
