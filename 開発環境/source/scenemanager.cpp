//==========================================
//
//  ��ʑJ�ڊǗ��N���X(scenemanager.cpp)
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
//  �ÓI�����o�ϐ��錾
//==========================================
CScene *CSceneManager::m_pScene = nullptr;
CCamera *CSceneManager::m_pCamera = nullptr;
bool CSceneManager::m_bClear = true;

//==========================================
//  �R���X�g���N�^
//==========================================
CSceneManager::CSceneManager() :
	m_Scene(NONE),
	m_Next(NONE),
	m_pFade(nullptr)
{
	m_pScene = nullptr;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CSceneManager::~CSceneManager()
{

}

//==========================================
//  ����������
//==========================================
void CSceneManager::Init(SCENE newsecene)
{
	//�V�����V�[����ݒ�
	m_Scene = newsecene;

	//�V�[���𐶐�
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

	//�V�[����������
	if (m_pScene != nullptr)
	{
		m_pScene->Init();
	}

	//�J�����𐶐�
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera;
	}

	//�J������������
	if (m_pCamera != nullptr)
	{
		m_pCamera->Init();
	}

	//�t�F�[�h�𐶐�
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create(60, CFade::MODE_IN);
	}
}

//==========================================
//  �I������
//==========================================
void CSceneManager::Uninit(void)
{
	//�V�[�����I���A�j��
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//�S�I�u�W�F�N�g��j��
	CObject::ReleaseAll();

	//�J�������I���A�j��
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}

//==========================================
//  �X�V����
//==========================================
void CSceneManager::Update(void)
{
	//�V�[�����X�V
	if (m_pScene != NULL)
	{
		m_pScene->Update();
	}
	
	//�J�������X�V
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//�t�F�[�h���X�V
	if (m_pFade != NULL)
	{
		//�t�F�[�h������������폜����
		if (m_pFade->GetState() == true)
		{
			//�t�F�[�h���[�h��ۑ�
			CFade::MODE mode = m_pFade->GetMode();

			//�I���A�j��
			m_pFade->Uninit();
			delete m_pFade;
			m_pFade = NULL;

			//���̃V�[���𐶐�����
			if (mode == CFade::MODE_OUT)
			{
				Uninit();
				Init(m_Next);
			}
		}
	}
}

//==========================================
//  �`�揈��
//==========================================
void CSceneManager::Draw(void)
{
	//�V�[���̕`��
	if (m_pScene != NULL)
	{
		m_pScene->Draw();
	}

	//���݂̃V�[����\��
	switch (m_Scene)
	{
	case TITLE:
		DebugProc::Print("���݂̃V�[�� : �^�C�g��\n");
		break;
	case GAME:
		DebugProc::Print("���݂̃V�[�� : �Q�[��\n");
		break;
	case RESULT:
		DebugProc::Print("���݂̃V�[�� : ���U���g\n");
		break;
	case RANKING:
		DebugProc::Print("���݂̃V�[�� : �����L���O\n");
		break;
	default:
		break;
	}
}

//==========================================
//  �ݒ菈��
//==========================================
bool CSceneManager::SetNext(SCENE next)
{
	//���̃V�[�����L�^
	m_Next = next;

	//�t�F�[�h�𐶐�
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create(60, CFade::MODE_OUT);
		return true;
	}

	return false;
}

//==========================================
//  ��������
//==========================================
CSceneManager *CSceneManager::Create(SCENE scene)
{
	//�C���X�^���X����
	CSceneManager *pScene = NULL;

	//NULL�`�F�b�N
	if (pScene == NULL)
	{
		//���������m��
		pScene = new CSceneManager;
	}

	//������
	if (pScene != NULL)
	{
		pScene->Init(scene);
	}

	//�|�C���^��Ԃ�
	return pScene;
}
