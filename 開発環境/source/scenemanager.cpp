//==========================================
//
//  画面遷移管理クラス(scenemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "scenemanager.h"
#include "titlemanager.h"
#include "gamemanager.h"
#include "resultmanager.h"
#include "camera_game.h"
#include "camera_title.h"
#include "camera_result.h"
#include "fade.h"
#include "scene.h"
#include "object.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"
#include "sound.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CScene *CSceneManager::m_pScene = nullptr;
CCamera *CSceneManager::m_pCamera = nullptr;
bool CSceneManager::m_bClear = true;

//==========================================
//  コンストラクタ
//==========================================
CSceneManager::CSceneManager() :
	m_Scene(NONE),
	m_Next(NONE),
	m_pFade(nullptr)
{
	m_pScene = nullptr;
}

//==========================================
//  デストラクタ
//==========================================
CSceneManager::~CSceneManager()
{

}

//==========================================
//  初期化処理
//==========================================
void CSceneManager::Init(SCENE newsecene)
{
	//新しいシーンを設定
	m_Scene = newsecene;

	//シーンを生成
	if (m_pScene == nullptr)
	{
		switch (m_Scene)
		{
		case TITLE:
			m_pScene = new CTitleManager;
			m_pCamera = new CCameraTitle;
			break;
		case GAME:
			m_pScene = new CGameManager;
			m_pCamera = new CCameraGame;
			break;
		case RESULT:
			m_pScene = new CResultManager;
			m_pCamera = new CCameraResult;
			break;
		case RANKING:
			break;
		default:
			break;
		}
	}
	else
	{
		return;
	}

	//シーンを初期化
	if (m_pScene != nullptr)
	{
		m_pScene->Init();
	}

	//カメラを生成
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera;
	}

	//カメラを初期化
	if (m_pCamera != nullptr)
	{
		m_pCamera->Init();
	}

	//フェードを生成
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create(60, CFade::MODE_IN);
	}
}

//==========================================
//  終了処理
//==========================================
void CSceneManager::Uninit(void)
{
	//シーンを終了、破棄
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//全オブジェクトを破棄
	CObject::ReleaseAll();

	//カメラを終了、破棄
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//==========================================
//  更新処理
//==========================================
void CSceneManager::Update(void)
{
	//シーンを更新
	if (m_pScene != NULL)
	{
		m_pScene->Update();
	}
	
	//カメラを更新
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//フェードを更新
	if (m_pFade != NULL)
	{
		//フェードが完了したら削除する
		if (m_pFade->GetState() == true)
		{
			//フェードモードを保存
			CFade::MODE mode = m_pFade->GetMode();

			//終了、破棄
			m_pFade->Uninit();
			delete m_pFade;
			m_pFade = NULL;

			//次のシーンを生成する
			if (mode == CFade::MODE_OUT)
			{
				Uninit();
				Init(m_Next);
			}
		}
	}
}

//==========================================
//  描画処理
//==========================================
void CSceneManager::Draw(void)
{
	//シーンの描画
	if (m_pScene != NULL)
	{
		m_pScene->Draw();
	}

	//現在のシーンを表示
	switch (m_Scene)
	{
	case TITLE:
		DebugProc::Print("現在のシーン : タイトル\n");
		break;
	case GAME:
		DebugProc::Print("現在のシーン : ゲーム\n");
		break;
	case RESULT:
		DebugProc::Print("現在のシーン : リザルト\n");
		break;
	case RANKING:
		DebugProc::Print("現在のシーン : ランキング\n");
		break;
	default:
		break;
	}
}

//==========================================
//  設定処理
//==========================================
bool CSceneManager::SetNext(SCENE next)
{
	//次のシーンを記録
	m_Next = next;

	//フェードを生成
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create(60, CFade::MODE_OUT);
		return true;
	}

	return false;
}

//==========================================
//  生成処理
//==========================================
CSceneManager *CSceneManager::Create(SCENE scene)
{
	//インスタンス生成
	CSceneManager *pScene = NULL;

	//NULLチェック
	if (pScene == NULL)
	{
		//メモリを確保
		pScene = new CSceneManager;
	}

	//初期化
	if (pScene != NULL)
	{
		pScene->Init(scene);
	}

	//ポインタを返す
	return pScene;
}
