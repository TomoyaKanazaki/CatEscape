//==========================================
//
//  �^�C�g���}�l�[�W��(titlemanager.cpp)
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
//  �ÓI�����o�ϐ��錾
//==========================================
CLight* CTitleManager::m_pLight = NULL;
CTitle* CTitleManager::m_pTitle = NULL;
CDoll* CTitleManager::m_pDoll = NULL;
CCamera* CTitleManager::m_pCamera = NULL;

//==========================================
//  �R���X�g���N�^
//==========================================
CTitleManager::CTitleManager()
{
	m_nCntScene = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CTitleManager::~CTitleManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTitleManager::Init(void)
{
	//�^�C�g�����S
	m_pTitle =  CTitle::Create(D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(300.0f, 100.0f, 0.0f));

	//�l�`��ݒu
	m_pDoll = CDoll::Create(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));

	//�����̐���
	CBuild::Create();

	//�w�i�̐���
	CBg::Create(D3DXVECTOR3(0.0f, 0.0f, 20000.0f), D3DXVECTOR3(60000.0f, 0.0f, 20000.0f), 1);

	//���̐���
	CFeild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(6000.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 6.0f), CFeild::SOIL);

	//���̐���
	CFeild::Create(D3DXVECTOR3(0.0f, -3000.0f, 0.0f), D3DXVECTOR3(60000.0f, 0.0f, 60000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CFeild::WATER);

	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//�J�����̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = CSceneManager::GetCamera();
	}

	//BGM�̍Đ�
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTitleManager::Uninit(void)
{
	//���C�g�̏I���A�j��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// �J�����̏I��
	m_pCamera = NULL;

	//BGM�̒�~
	CManager::GetInstance()->GetSound()->Stop();
}

//==========================================
//  �X�V����
//==========================================
void CTitleManager::Update(void)
{
	//��ʑJ��
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

	//���C�g�̍X�V
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}
}

//==========================================
//  �`�揈��
//==========================================
void CTitleManager::Draw(void)
{

}
