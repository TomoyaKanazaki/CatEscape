//==========================================
//
//  マネージャクラス(manager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "object2D.h"
#include "debugproc.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "model.h"
#include "layer.h"
#include "motion.h"
#include "scenemanager.h"
#include "gametime.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CManager* CManager::m_pManager = nullptr;
HWND CManager::m_Wnd = NULL;

//==========================================
//  コンストラクタ
//==========================================
CManager::CManager() :
m_pRenderer(NULL),
m_pKeyboard(NULL),
m_pMouse(NULL),
m_pJoyPad(NULL),
m_pSound(NULL),
m_pTexture(NULL),
m_pSceneManager(NULL),
m_pGameTime(NULL),
m_Instance(NULL),
m_Window(true),
m_nFPS(0)
{

}

//==========================================
//  デストラクタ
//==========================================
CManager::~CManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//変数の保存
	m_Instance = hInstance;
	m_Wnd = hWnd;
	m_Window = bWindow;

	//ゲームタイマーの生成
	if (m_pGameTime == NULL)
	{
		m_pGameTime = new CGameTime;
		m_pGameTime->Init();
	}

	//レンダラーの生成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}

	//レンダラーの初期化
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return E_FAIL;
		}
	}
	
	//サウンドの生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}

	//サウンドの初期化
	if (m_pSound != NULL)
	{
		if (FAILED(m_pSound->Init(hWnd)))
		{
			return E_FAIL;
		}
	}

	//テクスチャの読み込み
	if (m_pTexture == NULL)
	{
		//インスタンス生成
		m_pTexture = new CTexture;

		//読み込みが済んでいるか否か
		if (m_pTexture != NULL)
		{
			if (CTexture::GetLoadState() == false)
			{
				//テクスチャを読み込む
				m_pTexture->Load();
			}
		}
	}

	//モデルの読み込み
	if (CModel::GetLoadState() == false)
	{
		//モデルを読み込む
		CModel::Load();
	}

	//階層構造を読み込む
	CLayer::Load();

	//モーション情報を読み込む
	CMotion::Load();

	//デバッグ表示の初期化
	DebugProc::Init();

	//キーボードの生成
	if (m_pKeyboard == NULL)
	{
		m_pKeyboard = new CKeyboard;
	}

	//キーボードの初期化
	if (m_pKeyboard != NULL)
	{
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//マウスの生成
	if (m_pMouse == NULL)
	{
		m_pMouse = new CMouse;
	}

	//マウスの初期化
	if (m_pMouse != NULL)
	{
		if (FAILED(m_pMouse->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//ジョイパッドの生成
	if (m_pJoyPad == NULL)
	{
		m_pJoyPad = new CJoyPad;
	}

	//ジョイパッドの初期化
	if (m_pJoyPad != NULL)
	{
		if (FAILED(m_pJoyPad->Init()))
		{
			MessageBox(hWnd, "このゲームはゲームパッドを使用してプレイするゲームです。\nゲームパッドを接続して起動し直してください。", "起動エラー", MB_ICONWARNING);

#ifndef _DEBUG
			return E_FAIL;
#endif
		}
	}

	//シーンマネージャの生成
#ifdef _DEBUG
	if (m_pSceneManager == NULL)
	{
		m_pSceneManager = CSceneManager::Create(CSceneManager::TITLE);
	}
#else
	if (m_pSceneManager == NULL)
	{
		m_pSceneManager = CSceneManager::Create(CSceneManager::TITLE);
	}
#endif
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CManager::Uninit(void)
{
	//オブジェクトの終了
	CObject::ReleaseAll();

	//シーンマネージャの終了
	if (m_pSceneManager != NULL)
	{
		m_pSceneManager->Uninit();
		delete m_pSceneManager;
		m_pSceneManager = NULL;
	}

	//レンダラーの終了、破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//サウンドの終了、破棄
	if (m_pSound != NULL)
	{
		m_pSound->Stop();
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//デバッグ表示の終了、破棄
	DebugProc::Uninit();

	//キーボードの終了、破棄
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	//マウスの終了、破棄
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}
	
	//ジョイパッドの終了、破棄
	if (m_pJoyPad != NULL)
	{
		m_pJoyPad->Uninit();
		delete m_pJoyPad;
		m_pJoyPad = NULL;
	}

	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->UnLoad();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	//モデルを破棄
	if (CModel::GetLoadState())
	{
		//モデルを破棄
		CModel::UnLoad();
	}

	//階層構造を破棄
	CLayer::UnLoad();

	//ゲームタイマーの破棄
	if (m_pGameTime != NULL)
	{
		m_pGameTime->Uninit();
		delete m_pGameTime;
	}
}

//==========================================
//  更新処理
//==========================================
void CManager::Update(void)
{
	//ゲームタイマーの更新
	if (m_pGameTime != NULL)
	{
		m_pGameTime->Update();
	}

	//キーボードの更新処理
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}

	//マウスの更新処理
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}
	
	//ジョイパッドの更新処理
	if (m_pJoyPad != NULL)
	{
		m_pJoyPad->Update();
	}

	//レンダラーの更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	//デバッグ表示の更新処理
	DebugProc::Update();

	//シーンマネージャの更新
	if (m_pSceneManager != NULL)
	{
		m_pSceneManager->Update();
	}
}

//==========================================
//  描画処理
//==========================================
void CManager::Draw(void)
{
	//レンダラーの描画処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//==========================================
//  マネージャの取得
//==========================================
CManager *CManager::GetInstance(void)
{
	//インスタンス生成
	if (m_pManager == NULL)
	{
		m_pManager = new CManager;
	}

	return m_pManager;
}

//==========================================
//  リリース
//==========================================
HRESULT CManager::Release(void)
{
	if (m_pManager != nullptr)
	{
		//自身の破棄
		delete m_pManager;
		m_pManager = nullptr;
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}
