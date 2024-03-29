//==========================================
//
//  �Q�[���V�[���̃J����(camera_game.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_game.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "input.h"
#include "enemymanager.h"
#include "boss.h"
#include "gametime.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float PLAYER_DISTANCE = 50.0f; //�v���C���[���璍���_�̋���
	const float REVISION_SPEED_FOV = 0.1f; // ����p�̊g�k���x
	const float REVISION_SPEED_POS = 0.05f; // �n�_�̈ړ����x
	const D3DXVECTOR3 LOCK_BOSS = D3DXVECTOR3(1800.0f, 150.0f, 0.0f);
	const float BOSS_DISTANCE = -620.0f;
	const D3DXVECTOR3 RUSH_DISTANCE = D3DXVECTOR3(-50.0f, 60.0f, -150.0f);
	const float QUAKE_RANGE_LIMIT = 10.0f; // �h��̏��
	const float QUAKE_TIME_LIMIT = 1.0f; // �h�ꎞ�ԏ��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CCameraGame::CCameraGame()
{
	m_Quake.rangeR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Quake.rangeV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Quake.time = 0.0f;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CCameraGame::~CCameraGame()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCameraGame::Init(void)
{
	//�v���C���[���W���擾
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//�����_��ݒ�
	m_posR = posPlayer;
	m_posR.y = V_HEIGHT; // ������␳����

	//���_��ݒ�
	m_posV = m_posR + D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);

	return CCamera::Init();
}

//==========================================
//  �X�V����
//==========================================
void CCameraGame::Update(void)
{
	// ��Ԗ��̏���
	if (CGameManager::GetState() == CGameManager::STATE_BOSS)
	{
		// �J�������Œ肷��
		LockBoss();
	}
	else if (CGameManager::GetState() == CGameManager::STATE_RUSH || CGameManager::GetState() == CGameManager::STATE_END)
	{
		LockRush();
	}
	else
	{
		//�v���C���[������
		MovePlayer();
	}

	//���[�J���ϐ��錾
	float fDiff = DEFAULT_FAV - m_fFov; //����

	//���������Z
	m_fFov += fDiff * REVISION_SPEED_FOV;

	// �h��
	Quake();

	CCamera::Update();
}

//==========================================
//  �h��̐ݒ�
//==========================================
void CCameraGame::SetQuake(const D3DXVECTOR3& range, float time)
{
	// �h��͈͂̐ݒ�
	m_Quake.rangeR = range * 0.5f;
	m_Quake.rangeV = range * 0.5f;

	// �h�ꎞ�Ԃ̐ݒ�
	if (time < QUAKE_TIME_LIMIT)
	{
		m_Quake.time = time;
	}
	else
	{
		m_Quake.time = QUAKE_TIME_LIMIT;
	}
}

//==========================================
//  �h��̉��Z
//==========================================
void CCameraGame::AddQuake(const D3DXVECTOR3& range, float time)
{
	// �h��͈͂̐ݒ�
	m_Quake.rangeR += range * 0.5f;
	m_Quake.rangeV += range * 0.5f;

	// �h�ꎞ�Ԃ̐ݒ�
	if (m_Quake.time < QUAKE_TIME_LIMIT)
	{
		m_Quake.time += time;
	}
	else
	{
		m_Quake.time = QUAKE_TIME_LIMIT;
	}
}

//==========================================
//  ��ʗh��̐ݒ�
//==========================================
void CCameraGame::Quake()
{
	// �p�����Ԃ̔���
	if (m_Quake.time <= 0.0f)
	{
		// ���Z�b�g
		m_Quake.time = 0.0f;
		m_Quake.rangeR = m_Quake.rangeV  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �h��Ȃ�
		return;
	}

	// �h�����̐ݒ�
	if (m_Quake.rangeR.x >= QUAKE_RANGE_LIMIT)
	{
		m_Quake.rangeR.x = QUAKE_RANGE_LIMIT;
	}
	if (m_Quake.rangeR.y >= QUAKE_RANGE_LIMIT)
	{
		m_Quake.rangeR.y = QUAKE_RANGE_LIMIT;
	}
	if (m_Quake.rangeR.z >= QUAKE_RANGE_LIMIT)
	{
		m_Quake.rangeR.z = QUAKE_RANGE_LIMIT;
	}
	if (m_Quake.rangeV.x >= QUAKE_RANGE_LIMIT)
	{
		m_Quake.rangeV.x = QUAKE_RANGE_LIMIT;
	}
	if (m_Quake.rangeV.y >= QUAKE_RANGE_LIMIT)
	{
		m_Quake.rangeV.y = QUAKE_RANGE_LIMIT;
	}
	if (m_Quake.rangeV.z >= QUAKE_RANGE_LIMIT)
	{
		m_Quake.rangeV.z = QUAKE_RANGE_LIMIT;
	}

	// �p�����Ԃ��X�V
	m_Quake.time -= CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// �덷���쐬����
	float Rand = ((float)rand() - ((float)RAND_MAX * 0.5f)) / ((float)RAND_MAX * 0.5f);

	// �덷�͈͂Ɍ덷��K�p����
	m_posR += m_Quake.rangeR * Rand;
	m_posV += m_Quake.rangeV * Rand;
}

//==========================================
//  �v���C���[����������
//==========================================
void CCameraGame::MovePlayer(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 Pos = m_posR; //���݂̈ʒu
	m_posR.y = V_HEIGHT; // ������␳����
	D3DXVECTOR3 Dest = CGameManager::GetPlayer()->GetPos(); //�ڕW�̈ʒu
	D3DXVECTOR3 Diff = {}; //�ڕW�ƌ��݂̈ʒu�̍�
	D3DXVECTOR3 rot = CGameManager::GetPlayer()->GetRot(); //�v���C���[�̕���
	float fDistance = sinf(rot.y) * PLAYER_DISTANCE;

	//�����𒲐�
	Dest.x -= fDistance;

	//�ړ��␳
	Diff = Dest - Pos;	//�ڕW�܂ł̈ړ������̍���

	//�K�p
	m_posR += Diff * 0.1f;

	//���_���X�V
	m_posV = m_posR + D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);
}

//==========================================
//  �{�X��̃J�����Œ菈��
//==========================================
void CCameraGame::LockBoss(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 Pos = m_posR; //���݂̈ʒu
	D3DXVECTOR3 Dest = LOCK_BOSS; //�ڕW�̈ʒu
	D3DXVECTOR3 Diff = {}; //�ڕW�ƌ��݂̈ʒu�̍�

	//�ړ��␳
	Diff = Dest - Pos;	//�ڕW�܂ł̈ړ������̍���

	//�K�p
	m_posR += Diff * REVISION_SPEED_POS;

	//���_���X�V
	m_posV = m_posR + D3DXVECTOR3(0.0f, R_HEIGHT, BOSS_DISTANCE);
}

//==========================================
//  ���b�N��Ԃ̃J�����Œ�
//==========================================
void CCameraGame::LockRush()
{
	// �����_��ݒ�
	m_posR = CGameManager::GetEnemy()->GetBoss()->GetCenterPos();
	m_posR.x -= 30.0f;

	// ���_��ݒ�
	m_posV = m_posR + RUSH_DISTANCE;
}
