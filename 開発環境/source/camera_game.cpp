//==========================================
//
//  ゲームシーンのカメラ(camera_game.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_game.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "input.h"
#include "enemymanager.h"
#include "boss.h"
#include "gametime.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float PLAYER_DISTANCE = 50.0f; //プレイヤーから注視点の距離
	const float REVISION_SPEED_FOV = 0.1f; // 視野角の拡縮速度
	const float REVISION_SPEED_POS = 0.05f; // 始点の移動速度
	const D3DXVECTOR3 LOCK_BOSS = D3DXVECTOR3(1800.0f, 150.0f, 0.0f);
	const float BOSS_DISTANCE = -620.0f;
	const D3DXVECTOR3 RUSH_DISTANCE = D3DXVECTOR3(-50.0f, 60.0f, -150.0f);
	const float QUAKE_RANGE_LIMIT = 10.0f; // 揺れの上限
	const float QUAKE_TIME_LIMIT = 1.0f; // 揺れ時間上限
}

//==========================================
//  コンストラクタ
//==========================================
CCameraGame::CCameraGame()
{
	m_Quake.rangeR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Quake.rangeV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Quake.time = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
CCameraGame::~CCameraGame()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCameraGame::Init(void)
{
	//プレイヤー座標を取得
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//注視点を設定
	m_posR = posPlayer;
	m_posR.y = V_HEIGHT; // 高さを補正する

	//視点を設定
	m_posV = m_posR + D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);

	return CCamera::Init();
}

//==========================================
//  更新処理
//==========================================
void CCameraGame::Update(void)
{
	// 状態毎の処理
	if (CGameManager::GetState() == CGameManager::STATE_BOSS)
	{
		// カメラを固定する
		LockBoss();
	}
	else if (CGameManager::GetState() == CGameManager::STATE_RUSH || CGameManager::GetState() == CGameManager::STATE_END)
	{
		LockRush();
	}
	else
	{
		//プレイヤーを向く
		MovePlayer();
	}

	//ローカル変数宣言
	float fDiff = DEFAULT_FAV - m_fFov; //差分

	//差分を加算
	m_fFov += fDiff * REVISION_SPEED_FOV;

	// 揺れ
	Quake();

	CCamera::Update();
}

//==========================================
//  揺れの設定
//==========================================
void CCameraGame::SetQuake(const D3DXVECTOR3& range, float time)
{
	// 揺れ範囲の設定
	m_Quake.rangeR = range * 0.5f;
	m_Quake.rangeV = range * 0.5f;

	// 揺れ時間の設定
	if (time < QUAKE_TIME_LIMIT)
	{
		m_Quake.time = time;
	}
	else
	{
		m_Quake.time = QUAKE_TIME_LIMIT;
	}
}

//==========================================
//  揺れの加算
//==========================================
void CCameraGame::AddQuake(const D3DXVECTOR3& range, float time)
{
	// 揺れ範囲の設定
	m_Quake.rangeR += range * 0.5f;
	m_Quake.rangeV += range * 0.5f;

	// 揺れ時間の設定
	if (m_Quake.time < QUAKE_TIME_LIMIT)
	{
		m_Quake.time += time;
	}
	else
	{
		m_Quake.time = QUAKE_TIME_LIMIT;
	}
}

//==========================================
//  画面揺れの設定
//==========================================
void CCameraGame::Quake()
{
	// 継続時間の判定
	if (m_Quake.time <= 0.0f)
	{
		// リセット
		m_Quake.time = 0.0f;
		m_Quake.rangeR = m_Quake.rangeV  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 揺れない
		return;
	}

	// 揺れ上限の設定
	if (m_Quake.rangeR.x >= QUAKE_RANGE_LIMIT)
	{
		m_Quake.rangeR.x = QUAKE_RANGE_LIMIT;
	}
	if (m_Quake.rangeR.y >= QUAKE_RANGE_LIMIT)
	{
		m_Quake.rangeR.y = QUAKE_RANGE_LIMIT;
	}
	if (m_Quake.rangeR.z >= QUAKE_RANGE_LIMIT)
	{
		m_Quake.rangeR.z = QUAKE_RANGE_LIMIT;
	}
	if (m_Quake.rangeV.x >= QUAKE_RANGE_LIMIT)
	{
		m_Quake.rangeV.x = QUAKE_RANGE_LIMIT;
	}
	if (m_Quake.rangeV.y >= QUAKE_RANGE_LIMIT)
	{
		m_Quake.rangeV.y = QUAKE_RANGE_LIMIT;
	}
	if (m_Quake.rangeV.z >= QUAKE_RANGE_LIMIT)
	{
		m_Quake.rangeV.z = QUAKE_RANGE_LIMIT;
	}

	// 継続時間を更新
	m_Quake.time -= CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// 誤差を作成する
	float Rand = ((float)rand() - ((float)RAND_MAX * 0.5f)) / ((float)RAND_MAX * 0.5f);

	// 誤差範囲に誤差を適用する
	m_posR += m_Quake.rangeR * Rand;
	m_posV += m_Quake.rangeV * Rand;
}

//==========================================
//  プレイヤーを向く処理
//==========================================
void CCameraGame::MovePlayer(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 Pos = m_posR; //現在の位置
	m_posR.y = V_HEIGHT; // 高さを補正する
	D3DXVECTOR3 Dest = CGameManager::GetPlayer()->GetPos(); //目標の位置
	D3DXVECTOR3 Diff = {}; //目標と現在の位置の差
	D3DXVECTOR3 rot = CGameManager::GetPlayer()->GetRot(); //プレイヤーの方向
	float fDistance = sinf(rot.y) * PLAYER_DISTANCE;

	//差分を調整
	Dest.x -= fDistance;

	//移動補正
	Diff = Dest - Pos;	//目標までの移動方向の差分

	//適用
	m_posR += Diff * 0.1f;

	//視点を更新
	m_posV = m_posR + D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);
}

//==========================================
//  ボス戦のカメラ固定処理
//==========================================
void CCameraGame::LockBoss(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 Pos = m_posR; //現在の位置
	D3DXVECTOR3 Dest = LOCK_BOSS; //目標の位置
	D3DXVECTOR3 Diff = {}; //目標と現在の位置の差

	//移動補正
	Diff = Dest - Pos;	//目標までの移動方向の差分

	//適用
	m_posR += Diff * REVISION_SPEED_POS;

	//視点を更新
	m_posV = m_posR + D3DXVECTOR3(0.0f, R_HEIGHT, BOSS_DISTANCE);
}

//==========================================
//  ロック状態のカメラ固定
//==========================================
void CCameraGame::LockRush()
{
	// 注視点を設定
	m_posR = CGameManager::GetEnemy()->GetBoss()->GetCenterPos();
	m_posR.x -= 30.0f;

	// 視点を設定
	m_posV = m_posR + RUSH_DISTANCE;
}
