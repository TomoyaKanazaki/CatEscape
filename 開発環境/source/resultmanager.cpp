//==========================================
//
//  ���U���g�}�l�[�W��(resultmanager.cpp)
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
//  �ÓI�����o�ϐ��錾
//==========================================
CLight* CResultManager::m_pLight = NULL;
CCamera* CResultManager::m_pCamera = nullptr;
CRunning* CResultManager::m_pRunning = nullptr;

//==========================================
//  �R���X�g���N�^
//==========================================
CResultManager::CResultManager()
{
	m_fCntScene = 0.0f;
	m_nRank = 0;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CResultManager::~CResultManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CResultManager::Init(void)
{
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
	if (m_pCamera == nullptr)
	{
		m_pCamera = CSceneManager::GetCamera();
	}

	//BGM�̍Đ�
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_RESULT);

	// �v���C���[�o��
	if (m_pRunning == nullptr)
	{
		m_pRunning = CRunning::Create();
	}

	// �G���o��
	if (!CSceneManager::GetClear())
	{
		CEnemy::Create(m_pCamera->GetPosR(), CEnemy::RESULT);
	}

	// ���b�Z�[�W�𐶐�
	CResult::Create();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CResultManager::Uninit(void)
{
	//BGM�̒�~
	CManager::GetInstance()->GetInstance()->GetSound()->Stop();

	// �J�����̏I��
	if (m_pCamera != nullptr)
	{
		m_pCamera = nullptr;
	}

	// �v���C���[���J��
	if (m_pRunning != nullptr)
	{
		m_pRunning = nullptr;
	}
}

//==========================================
//  �X�V����
//==========================================
void CResultManager::Update(void)
{
	//��ʑJ��
	if (CManager::GetInstance()->GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_A) || CManager::GetInstance()->GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetInstance()->GetSceneManager()->SetNext(CSceneManager::TITLE);
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_END);
		return;
	}
}

//==========================================
//  �`�揈��
//==========================================
void CResultManager::Draw(void)
{

}
