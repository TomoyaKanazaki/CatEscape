//==========================================
//
//  ゲームマネージャクラス(gamemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gamemanager.h"
#include "manager.h"
#include "sound.h"
#include "player.h"
#include "light.h"
#include "camera.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"
#include "scenemanager.h"
#include "model.h"
#include "renderer.h"
#include "bg.h"
#include "field.h"
#include "gametime.h"
#include "build.h"
#include "fog.h"
#include "enemymanager.h"
#include "bosslife.h"
#include "rush_effect.h"
#include "tutorial.h"
#include "stick.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CGameManager::m_fDashTime = 0.8f;
CPlayer* CGameManager::m_pPlayer = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CGameManager::State CGameManager::m_State = NONE;
CGameManager::State CGameManager::m_oldState = NONE;
CGameManager::Progress CGameManager::m_Progress = TUTORIAL_ENEMY;
CEnemyManager* CGameManager::m_pEnemy = nullptr;
CBossLife* CGameManager::m_pLife = nullptr;

//==========================================
//  定数定義
//==========================================
namespace
{
	const float END_FOG = 560.0f;
	const float LIMIT_FOG = 100.0f;
	const float START_FOG = 300.0f;
}

//==========================================
//  コンストラクタ
//==========================================
CGameManager::CGameManager()
{
	m_fTimer = 0.0f;
	m_Progress = TUTORIAL_ENEMY;
}

//==========================================
//  デストラクタ
//==========================================
CGameManager::~CGameManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CGameManager::Init(void)
{
	// フォグの距離を設定
	Fog::SetStart(START_FOG);
	Fog::SetEnd(END_FOG);

	//状態の初期化
	m_State = STATE_START;

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-2500.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	// エネミーマネージャの生成
	if (m_pEnemy == nullptr)
	{
		m_pEnemy = CEnemyManager::Create();
	}

	//建物の生成
	CBuild::Create();

	//背景の生成
	CBg::Create(D3DXVECTOR3(0.0f, 300.0f, 20000.0f), D3DXVECTOR3(60000.0f, 0.0f, 20000.0f), 1);

	//床の生成
	CFeild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(6000.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 6.0f), CFeild::SOIL);
	
	//水の生成
	CFeild::Create(D3DXVECTOR3(0.0f, -3000.0f, 0.0f), D3DXVECTOR3(60000.0f, 0.0f, 60000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CFeild::WATER);

	// チュートリアルの生成
	CTutorial::Create();
	CTutorial::Create();

	//カメラの生成
	if (m_pCamera == NULL)
	{
		m_pCamera = CSceneManager::GetCamera();
		m_pCamera->Init();
	}

	//ライトの生成
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//BGMの再生
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CGameManager::Uninit(void)
{
	//ライトの終了、破棄
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// エネミーマネージャの破棄
	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Uninit();
		m_pEnemy = nullptr;
	}

	// 体力表示の破棄
	if (m_pLife != nullptr)
	{
		m_pLife = nullptr;
	}

	// カメラの終了
	m_pCamera = NULL;

	// フォグを終了
	Fog::Set(false);

	//BGMの停止
	CManager::GetInstance()->GetInstance()->GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CGameManager::Update(void)
{
	//前回の状態を保存する
	m_oldState = m_State;

	// エネミーマネージャの更新
	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Update();
	}

	// 状態管理
	TaskState();

	//ライトの更新
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	// ボス戦に移行する
	if (m_pPlayer->GetPos().x >= 1400.0f)
	{
		m_State = STATE_BOSS;
	}

	// 連撃状態に移行する
	if (m_pEnemy->GetRush())
	{
		m_State = STATE_RUSH;

		// 体力表示を生成
		if (m_pLife == nullptr)
		{
			m_pLife = CBossLife::Create();
			CRush::Create();
			CStick::Create();

			// フォグを設定
			Fog::Set(true);
			Fog::SetCol(D3DXCOLOR(0.9f, 1.0f, 0.9f, 1.0f));
		}

		if (m_pLife != nullptr)
		{
			if (m_pLife->GetDeath())
			{
				m_State = STATE_END;
			}
		}
	}

	// 終了状態の処理
	if (m_State == STATE_END)
	{
		// フォグを更新
		D3DXCOLOR col = Fog::GetCol();
		col += D3DXCOLOR(0.02f, 0.0f, 0.02f, 0.0f);
		Fog::SetCol(col);
		float end = Fog::GetEnd();
		if (end >= LIMIT_FOG)
		{
			end -= 10.0f;
		}
		Fog::SetEnd(end);
	}

	// リザルトに遷移
	if (Fog::Get() && Fog::GetCol().r >= 1.0f)
	{
		// プレイ結果を成功に設定
		CSceneManager::SetClear(true);

		// リザルトに遷移
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}

	//リザルトに遷移
	if (m_pPlayer->GetDeath())
	{
		// プレイ結果を失敗に設定
		CSceneManager::SetClear(false);

		// リザルトに遷移
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}

#ifdef _DEBUG

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_0))
	{
		// プレイ結果を失敗に設定
		CSceneManager::SetClear(false);

		// リザルトに遷移
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_9))
	{
		// プレイ結果を失敗に設定
		CSceneManager::SetClear(true);

		// リザルトに遷移
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}

#endif
}

//==========================================
//  描画処理
//==========================================
void CGameManager::Draw(void)
{

}

//==========================================
//  チュートリアル処理
//==========================================
void CGameManager::TaskTutorial()
{

}

//==========================================
//  状態管理の処理
//==========================================
void CGameManager::TaskState()
{
	// ゲームをスタート
	if (m_State == STATE_START && m_pPlayer->GetPos().x >= -2250.0f)
	{
		m_State = STATE_NORMAL;
	}
}
