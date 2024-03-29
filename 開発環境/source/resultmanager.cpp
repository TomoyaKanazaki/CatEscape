//==========================================
//
//  リザルトマネージャ(resultmanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "resultmanager.h"
#include "manager.h"
#include "gametime.h"
#include "debugproc.h"
#include "scenemanager.h"
#include "input.h"
#include "sound.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "bg.h"
#include "field.h"
#include "build.h"
#include "camera_title.h"
#include "running.h"
#include "result.h"
#include "boss_result.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CLight* CResultManager::m_pLight = NULL;
CCamera* CResultManager::m_pCamera = nullptr;
CRunning* CResultManager::m_pRunning = nullptr;

//==========================================
//  コンストラクタ
//==========================================
CResultManager::CResultManager()
{
	m_fCntScene = 0.0f;
	m_nRank = 0;
}

//==========================================
//  デストラクタ
//==========================================
CResultManager::~CResultManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CResultManager::Init(void)
{
	//建物の生成
	CBuild::Create();

	//背景の生成
	CBg::Create(D3DXVECTOR3(0.0f, 0.0f, 20000.0f), D3DXVECTOR3(60000.0f, 0.0f, 20000.0f), 1);

	//床の生成
	CFeild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(6000.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 6.0f), CFeild::SOIL);

	//水の生成
	CFeild::Create(D3DXVECTOR3(0.0f, -3000.0f, 0.0f), D3DXVECTOR3(60000.0f, 0.0f, 60000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CFeild::WATER);

	//ライトの生成
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//カメラの生成
	if (m_pCamera == nullptr)
	{
		m_pCamera = CSceneManager::GetCamera();
	}

	//BGMの再生
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_RESULT);

	// プレイヤー出す
	if (m_pRunning == nullptr)
	{
		m_pRunning = CRunning::Create();
	}

	// 敵を出す
	if (!CSceneManager::GetClear())
	{
		CEnemy::Create(m_pCamera->GetPosR(), CEnemy::RESULT);
	}

	// メッセージを生成
	CResult::Create();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CResultManager::Uninit(void)
{
	//BGMの停止
	CManager::GetInstance()->GetInstance()->GetSound()->Stop();

	// カメラの終了
	if (m_pCamera != nullptr)
	{
		m_pCamera = nullptr;
	}

	// プレイヤーを開放
	if (m_pRunning != nullptr)
	{
		m_pRunning = nullptr;
	}
}

//==========================================
//  更新処理
//==========================================
void CResultManager::Update(void)
{
	//画面遷移
	if (CManager::GetInstance()->GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_A) || CManager::GetInstance()->GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetInstance()->GetSceneManager()->SetNext(CSceneManager::TITLE);
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_END);
		return;
	}
}

//==========================================
//  描画処理
//==========================================
void CResultManager::Draw(void)
{

}
