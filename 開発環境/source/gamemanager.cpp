//==========================================
//
//  �Q�[���}�l�[�W���N���X(gamemanager.cpp)
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
//  �ÓI�����o�ϐ��錾
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
//  �萔��`
//==========================================
namespace
{
	const float END_FOG = 560.0f;
	const float LIMIT_FOG = 100.0f;
	const float START_FOG = 300.0f;
}

//==========================================
//  �R���X�g���N�^
//==========================================
CGameManager::CGameManager()
{
	m_fTimer = 0.0f;
	m_Progress = TUTORIAL_ENEMY;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CGameManager::~CGameManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CGameManager::Init(void)
{
	// �t�H�O�̋�����ݒ�
	Fog::SetStart(START_FOG);
	Fog::SetEnd(END_FOG);

	//��Ԃ̏�����
	m_State = STATE_START;

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-2500.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	// �G�l�~�[�}�l�[�W���̐���
	if (m_pEnemy == nullptr)
	{
		m_pEnemy = CEnemyManager::Create();
	}

	//�����̐���
	CBuild::Create();

	//�w�i�̐���
	CBg::Create(D3DXVECTOR3(0.0f, 300.0f, 20000.0f), D3DXVECTOR3(60000.0f, 0.0f, 20000.0f), 1);

	//���̐���
	CFeild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(6000.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 6.0f), CFeild::SOIL);
	
	//���̐���
	CFeild::Create(D3DXVECTOR3(0.0f, -3000.0f, 0.0f), D3DXVECTOR3(60000.0f, 0.0f, 60000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CFeild::WATER);

	// �`���[�g���A���̐���
	CTutorial::Create();
	CTutorial::Create();

	//�J�����̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = CSceneManager::GetCamera();
		m_pCamera->Init();
	}

	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//BGM�̍Đ�
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CGameManager::Uninit(void)
{
	//���C�g�̏I���A�j��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// �G�l�~�[�}�l�[�W���̔j��
	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Uninit();
		m_pEnemy = nullptr;
	}

	// �̗͕\���̔j��
	if (m_pLife != nullptr)
	{
		m_pLife = nullptr;
	}

	// �J�����̏I��
	m_pCamera = NULL;

	// �t�H�O���I��
	Fog::Set(false);

	//BGM�̒�~
	CManager::GetInstance()->GetInstance()->GetSound()->Stop();
}

//==========================================
//  �X�V����
//==========================================
void CGameManager::Update(void)
{
	//�O��̏�Ԃ�ۑ�����
	m_oldState = m_State;

	// �G�l�~�[�}�l�[�W���̍X�V
	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Update();
	}

	// ��ԊǗ�
	TaskState();

	//���C�g�̍X�V
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	// �{�X��Ɉڍs����
	if (m_pPlayer->GetPos().x >= 1400.0f)
	{
		m_State = STATE_BOSS;
	}

	// �A����ԂɈڍs����
	if (m_pEnemy->GetRush())
	{
		m_State = STATE_RUSH;

		// �̗͕\���𐶐�
		if (m_pLife == nullptr)
		{
			m_pLife = CBossLife::Create();
			CRush::Create();
			CStick::Create();

			// �t�H�O��ݒ�
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

	// �I����Ԃ̏���
	if (m_State == STATE_END)
	{
		// �t�H�O���X�V
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

	// ���U���g�ɑJ��
	if (Fog::Get() && Fog::GetCol().r >= 1.0f)
	{
		// �v���C���ʂ𐬌��ɐݒ�
		CSceneManager::SetClear(true);

		// ���U���g�ɑJ��
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}

	//���U���g�ɑJ��
	if (m_pPlayer->GetDeath())
	{
		// �v���C���ʂ����s�ɐݒ�
		CSceneManager::SetClear(false);

		// ���U���g�ɑJ��
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}

#ifdef _DEBUG

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_0))
	{
		// �v���C���ʂ����s�ɐݒ�
		CSceneManager::SetClear(false);

		// ���U���g�ɑJ��
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_9))
	{
		// �v���C���ʂ����s�ɐݒ�
		CSceneManager::SetClear(true);

		// ���U���g�ɑJ��
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}

#endif
}

//==========================================
//  �`�揈��
//==========================================
void CGameManager::Draw(void)
{

}

//==========================================
//  �`���[�g���A������
//==========================================
void CGameManager::TaskTutorial()
{

}

//==========================================
//  ��ԊǗ��̏���
//==========================================
void CGameManager::TaskState()
{
	// �Q�[�����X�^�[�g
	if (m_State == STATE_START && m_pPlayer->GetPos().x >= -2250.0f)
	{
		m_State = STATE_NORMAL;
	}
}
