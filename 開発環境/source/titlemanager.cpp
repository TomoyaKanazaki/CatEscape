//==========================================
//
//  タイトルマネージャ(titlemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "titlemanager.h"
#include "manager.h"
#include "scenemanager.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "sound.h"
#include "title.h"
#include "texture.h"
#include "doll.h"
#include "bg.h"
#include "field.h"
#include "build.h"
#include "camera_title.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CLight* CTitleManager::m_pLight = NULL;
CTitle* CTitleManager::m_pTitle = NULL;
CDoll* CTitleManager::m_pDoll = NULL;
CCamera* CTitleManager::m_pCamera = NULL;

//==========================================
//  コンストラクタ
//==========================================
CTitleManager::CTitleManager()
{
	m_nCntScene = 0;
}

//==========================================
//  デストラクタ
//==========================================
CTitleManager::~CTitleManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTitleManager::Init(void)
{
	//タイトルロゴ
	m_pTitle =  CTitle::Create(D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(300.0f, 100.0f, 0.0f));

	//人形を設置
	m_pDoll = CDoll::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));

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
	if (m_pCamera == NULL)
	{
		m_pCamera = CSceneManager::GetCamera();
	}

	//BGMの再生
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CTitleManager::Uninit(void)
{
	//ライトの終了、破棄
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// カメラの終了
	m_pCamera = NULL;

	//BGMの停止
	CManager::GetInstance()->GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CTitleManager::Update(void)
{
	//画面遷移
	if (CManager::GetInstance()->GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_A) || CManager::GetInstance()->GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_END);
		if (CManager::GetInstance()->GetInstance()->GetSceneManager()->SetNext(CSceneManager::GAME))
		{
			m_pTitle->CutTitle();
			m_pDoll->Dash();
		}
		return;
	}
	else if (m_nCntScene >= 900)
	{
		CManager::GetInstance()->GetInstance()->GetSceneManager()->SetNext(CSceneManager::RANKING);
		return;
	}

	//ライトの更新
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}
}

//==========================================
//  描画処理
//==========================================
void CTitleManager::Draw(void)
{

}
