//==========================================
//
//  �}�l�[�W���N���X(manager.cpp)
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
//  �ÓI�����o�ϐ��錾
//==========================================
CManager* CManager::m_pManager = nullptr;
HWND CManager::m_Wnd = NULL;

//==========================================
//  �R���X�g���N�^
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
//  �f�X�g���N�^
//==========================================
CManager::~CManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�ϐ��̕ۑ�
	m_Instance = hInstance;
	m_Wnd = hWnd;
	m_Window = bWindow;

	//�Q�[���^�C�}�[�̐���
	if (m_pGameTime == NULL)
	{
		m_pGameTime = new CGameTime;
		m_pGameTime->Init();
	}

	//�����_���[�̐���
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}

	//�����_���[�̏�����
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return E_FAIL;
		}
	}
	
	//�T�E���h�̐���
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}

	//�T�E���h�̏�����
	if (m_pSound != NULL)
	{
		if (FAILED(m_pSound->Init(hWnd)))
		{
			return E_FAIL;
		}
	}

	//�e�N�X�`���̓ǂݍ���
	if (m_pTexture == NULL)
	{
		//�C���X�^���X����
		m_pTexture = new CTexture;

		//�ǂݍ��݂��ς�ł��邩�ۂ�
		if (m_pTexture != NULL)
		{
			if (CTexture::GetLoadState() == false)
			{
				//�e�N�X�`����ǂݍ���
				m_pTexture->Load();
			}
		}
	}

	//���f���̓ǂݍ���
	if (CModel::GetLoadState() == false)
	{
		//���f����ǂݍ���
		CModel::Load();
	}

	//�K�w�\����ǂݍ���
	CLayer::Load();

	//���[�V��������ǂݍ���
	CMotion::Load();

	//�f�o�b�O�\���̏�����
	DebugProc::Init();

	//�L�[�{�[�h�̐���
	if (m_pKeyboard == NULL)
	{
		m_pKeyboard = new CKeyboard;
	}

	//�L�[�{�[�h�̏�����
	if (m_pKeyboard != NULL)
	{
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//�}�E�X�̐���
	if (m_pMouse == NULL)
	{
		m_pMouse = new CMouse;
	}

	//�}�E�X�̏�����
	if (m_pMouse != NULL)
	{
		if (FAILED(m_pMouse->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//�W���C�p�b�h�̐���
	if (m_pJoyPad == NULL)
	{
		m_pJoyPad = new CJoyPad;
	}

	//�W���C�p�b�h�̏�����
	if (m_pJoyPad != NULL)
	{
		if (FAILED(m_pJoyPad->Init()))
		{
			MessageBox(hWnd, "���̃Q�[���̓Q�[���p�b�h���g�p���ăv���C����Q�[���ł��B\n�Q�[���p�b�h��ڑ����ċN���������Ă��������B", "�N���G���[", MB_ICONWARNING);

#ifndef _DEBUG
			return E_FAIL;
#endif
		}
	}

	//�V�[���}�l�[�W���̐���
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
//  �I������
//==========================================
void CManager::Uninit(void)
{
	//�I�u�W�F�N�g�̏I��
	CObject::ReleaseAll();

	//�V�[���}�l�[�W���̏I��
	if (m_pSceneManager != NULL)
	{
		m_pSceneManager->Uninit();
		delete m_pSceneManager;
		m_pSceneManager = NULL;
	}

	//�����_���[�̏I���A�j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�T�E���h�̏I���A�j��
	if (m_pSound != NULL)
	{
		m_pSound->Stop();
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//�f�o�b�O�\���̏I���A�j��
	DebugProc::Uninit();

	//�L�[�{�[�h�̏I���A�j��
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	//�}�E�X�̏I���A�j��
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}
	
	//�W���C�p�b�h�̏I���A�j��
	if (m_pJoyPad != NULL)
	{
		m_pJoyPad->Uninit();
		delete m_pJoyPad;
		m_pJoyPad = NULL;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->UnLoad();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	//���f����j��
	if (CModel::GetLoadState())
	{
		//���f����j��
		CModel::UnLoad();
	}

	//�K�w�\����j��
	CLayer::UnLoad();

	//�Q�[���^�C�}�[�̔j��
	if (m_pGameTime != NULL)
	{
		m_pGameTime->Uninit();
		delete m_pGameTime;
	}
}

//==========================================
//  �X�V����
//==========================================
void CManager::Update(void)
{
	//�Q�[���^�C�}�[�̍X�V
	if (m_pGameTime != NULL)
	{
		m_pGameTime->Update();
	}

	//�L�[�{�[�h�̍X�V����
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}

	//�}�E�X�̍X�V����
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}
	
	//�W���C�p�b�h�̍X�V����
	if (m_pJoyPad != NULL)
	{
		m_pJoyPad->Update();
	}

	//�����_���[�̍X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	//�f�o�b�O�\���̍X�V����
	DebugProc::Update();

	//�V�[���}�l�[�W���̍X�V
	if (m_pSceneManager != NULL)
	{
		m_pSceneManager->Update();
	}
}

//==========================================
//  �`�揈��
//==========================================
void CManager::Draw(void)
{
	//�����_���[�̕`�揈��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//==========================================
//  �}�l�[�W���̎擾
//==========================================
CManager *CManager::GetInstance(void)
{
	//�C���X�^���X����
	if (m_pManager == NULL)
	{
		m_pManager = new CManager;
	}

	return m_pManager;
}

//==========================================
//  �����[�X
//==========================================
HRESULT CManager::Release(void)
{
	if (m_pManager != nullptr)
	{
		//���g�̔j��
		delete m_pManager;
		m_pManager = nullptr;
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}
