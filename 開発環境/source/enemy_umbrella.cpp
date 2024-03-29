//==========================================
//
//  唐笠お化け(enemy_umbrella.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_umbrella.h"
#include "model.h"
#include "motion.h"
#include "gamemanager.h"
#include "camera.h"
#include "manager.h"
#include "gametime.h"
#include "player.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 UMBRELLA_SIZE = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	const float MAX_LIFE = 5.0f;
	const float ROTATION_SPEED = 0.1f; // 1フレームの回転量
	const float POS_DISTANCE = 80.0f; // 初期位置からの距離
	const float LOOK_PLAYER = 150.0f; // プレイヤーを発見する距離
	const D3DXVECTOR3 CENTER_POS = D3DXVECTOR3(0.0f, 40.0f, 0.0f); // 中心座標とオブジェクト座標の差
}

//==========================================
//  コンストラクタ
//==========================================
CEnemy_Umbrella::CEnemy_Umbrella() :
	m_posDefault(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_fMoveTime(0.0f),
	m_bLook(false)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemy_Umbrella::~CEnemy_Umbrella()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy_Umbrella::Init(void)
{
	//タイプの設定
	SetType(TYPE_ENEMY);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::ENEMY_UMBRELLA);

	// 初期化
	HRESULT hr = CObject_Char::Init();

	//モーション情報にモデルを渡す
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::UMBRELLA_WAIT);

	// サイズを設定
	m_size = UMBRELLA_SIZE;
	CalcHitLength(m_size);

	// 体力を設定
	m_fLife = MAX_LIFE;
	
	// 初期位置を保存
	m_posDefault = m_pos;

	// 中心座標の設定
	m_posCenter = m_pos + CENTER_POS;

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CEnemy_Umbrella::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy_Umbrella::Update(void)
{
	// 発見判定フラグ分岐
	if (m_bLook)
	{
		// プレイヤーを向く
		RotateToPlayer();
	}
	else
	{
		// くるくる回る
		RotationLoop();
		Move();

		// プレイヤーの発見
		//m_bLook = CalcDistancePlayer();
	}

	// 被撃時の処理
	Attacked();

	// 中心座標の設定
	m_posCenter = m_pos + CENTER_POS;

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy_Umbrella::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  回転処理
//==========================================
void CEnemy_Umbrella::RotationLoop()
{
	//回転
	m_rot.y += ROTATION_SPEED;

	//角度の補正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += (-D3DX_PI * 2);
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += (D3DX_PI * 2);
	}
}

//==========================================
//  移動
//==========================================
void CEnemy_Umbrella::Move()
{
	// 移動時間の加算
	m_fMoveTime += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// 上限設定
	if (m_fMoveTime >= D3DX_PI * 2.0f)
	{
		m_fMoveTime -= D3DX_PI * 2.0f;
	}

	// 座標を設定
	m_pos.y = m_posDefault.y + (cosf(m_fMoveTime) * POS_DISTANCE);
	m_pos.x = m_posDefault.x + (sinf(m_fMoveTime) * POS_DISTANCE);
}

//==========================================
//  プレイヤーの発見判定
//==========================================
bool CEnemy_Umbrella::CalcDistancePlayer()
{
	// 画面外の場合は判定しない
	if (!CGameManager::GetCamera()->OnScreen(m_pos))
	{
		return false;
	}

	// プレイヤーの距離を取得
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetCenterPos();

	// プレイヤーへのベクトルを求める
	D3DXVECTOR3 vec = pos - m_pos;

	// 発見距離の判定をする
	if (LOOK_PLAYER * LOOK_PLAYER >= vec.x * vec.x + vec.y * vec.y)
	{
		return true;
	}

	return false;
}
