//==========================================
//
//  敵クラス(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "gamemanager.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "enemy_lantern.h"
#include "enemy_umbrella.h"
#include "boss.h"
#include "gametime.h"
#include "camera.h"
#include "boss_result.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float SLICE_SCALE = 1.0f;
	const float DAMAGE = 1.0f; //一回の攻撃で受けるダメージ
	const D3DXVECTOR3 ENEMY_SIZE_DEFAULT = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	const float INVINCIBLE_TIME = 0.1f; // 無敵時間
}

//==========================================
//  静的メンバ変数宣言
//==========================================
float CEnemy::m_AllDamage = 0.0f; // 受けたダメージの合計

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy(int nPriority) : CObject_Char(nPriority),
m_type(NONE),
m_fLife(0.0f),
m_fInvincible(0.0f)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy::Init(void)
{
	return CObject_Char::Init();
}

//==========================================
//  終了処理
//==========================================
void CEnemy::Uninit(void)
{
	// 終了
	CObject_Char::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy::Update(void)
{
	// 移動量の適用
	m_pos += m_move;

	CObject_Char::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  生成処理
//==========================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, CEnemy::TYPE type)
{
	//変数宣言
	CEnemy* pEnemy = nullptr;

	//メモリを確保
	switch (type)
	{
	case LANTERN:
		pEnemy = new CEnemy_Lantern;
		break;

	case UMBRELLA:
		pEnemy = new CEnemy_Umbrella;
		break;

	case BOSS:
		pEnemy = new CBoss;
		break;

	case RESULT:
		pEnemy = new CBossResult;
		break;

	default:
		pEnemy = nullptr;
		break;
	}

	// NULLチェック
	if (pEnemy == nullptr) { return nullptr; }

	//値を設定
	pEnemy->m_pos = pos;
	pEnemy->m_type = type;

	//初期化処理
	pEnemy->Init();

	return pEnemy;
}

//==========================================
//  移動方向を向く
//==========================================
void CEnemy::RotateToMove(void)
{
	//移動してない時は回転しない
	if (m_move.x == 0.0f)
	{
		return;
	}

	//右に進む時は右を向く
	if (m_move.x > 0.0f)
	{
		m_rot.y = D3DX_PI;
	}

	//左に進むときは左を向く
	if (m_move.x < 0.0f)
	{
		m_rot.y = 0.0f;
	}
}

//==========================================
//  プレイヤーを向く
//==========================================
void CEnemy::RotateToPlayer()
{
	//ローカル変数宣言
	float fRotMove = m_rot.y; //現在の角度
	float fRotDest = 0.0f; //目標の角度
	float fRotDiff = 0.0f; //目標と現在の角度の差

	// プレイヤーの位置を取得
	D3DXVECTOR3 posPolyer = CGameManager::GetPlayer()->GetPos();

	// プレイヤーのいる方向を向く
	if (posPolyer.x > m_pos.x)
	{
		fRotDest = -D3DX_PI * 0.5f;
	}
	if (posPolyer.x < m_pos.x)
	{
		fRotDest = D3DX_PI * 0.5f;
	}

	//移動補正
	fRotDiff = fRotDest - fRotMove;	//目標までの移動方向の差分

	//角度の補正
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff += (-D3DX_PI * 2);
	}
	else if (fRotDiff <= -D3DX_PI)
	{
		fRotDiff += (D3DX_PI * 2);
	}

	//方向転換
	m_rot.y += fRotDiff * 0.2f;

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
//  被撃時の処理
//==========================================
void CEnemy::Attacked()
{
	// 状態毎の処理
	if (m_ObjState == ATTACKED)
	{
		// 画面外だと攻撃を受けない
		if (CGameManager::GetCamera()->OnScreen(m_pos))
		{
			m_fLife -= DAMAGE;
			m_AllDamage += DAMAGE;
			WhiteOut(true);
		}

		m_ObjState = INVINCIBLE;
		return;
	}
	else if (m_ObjState == INVINCIBLE)
	{
		// 時間の加算
		m_fInvincible += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

		// 無敵時間の解除
		if (m_fInvincible >= INVINCIBLE_TIME)
		{
			m_ObjState = NORMAL;
			m_fInvincible = 0.0f;
			WhiteOut(false);
		}
	}

	// 体力が尽きたら死ぬ
	if (m_fLife <= 0.0f)
	{
		Uninit();
	}
}
