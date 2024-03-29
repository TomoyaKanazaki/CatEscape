//==========================================
//
//  ���}������(enemy_umbrella.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy_umbrella.h"
#include "model.h"
#include "motion.h"
#include "gamemanager.h"
#include "camera.h"
#include "manager.h"
#include "gametime.h"
#include "player.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 UMBRELLA_SIZE = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	const float MAX_LIFE = 5.0f;
	const float ROTATION_SPEED = 0.1f; // 1�t���[���̉�]��
	const float POS_DISTANCE = 80.0f; // �����ʒu����̋���
	const float LOOK_PLAYER = 150.0f; // �v���C���[�𔭌����鋗��
	const D3DXVECTOR3 CENTER_POS = D3DXVECTOR3(0.0f, 40.0f, 0.0f); // ���S���W�ƃI�u�W�F�N�g���W�̍�
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy_Umbrella::CEnemy_Umbrella() :
	m_posDefault(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_fMoveTime(0.0f),
	m_bLook(false)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy_Umbrella::~CEnemy_Umbrella()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy_Umbrella::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_UMBRELLA);

	// ������
	HRESULT hr = CObject_Char::Init();

	//���[�V�������Ƀ��f����n��
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::UMBRELLA_WAIT);

	// �T�C�Y��ݒ�
	m_size = UMBRELLA_SIZE;
	CalcHitLength(m_size);

	// �̗͂�ݒ�
	m_fLife = MAX_LIFE;
	
	// �����ʒu��ۑ�
	m_posDefault = m_pos;

	// ���S���W�̐ݒ�
	m_posCenter = m_pos + CENTER_POS;

	return hr;
}

//==========================================
//  �I������
//==========================================
void CEnemy_Umbrella::Uninit(void)
{
	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy_Umbrella::Update(void)
{
	// ��������t���O����
	if (m_bLook)
	{
		// �v���C���[������
		RotateToPlayer();
	}
	else
	{
		// ���邭����
		RotationLoop();
		Move();

		// �v���C���[�̔���
		//m_bLook = CalcDistancePlayer();
	}

	// �팂���̏���
	Attacked();

	// ���S���W�̐ݒ�
	m_posCenter = m_pos + CENTER_POS;

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy_Umbrella::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  ��]����
//==========================================
void CEnemy_Umbrella::RotationLoop()
{
	//��]
	m_rot.y += ROTATION_SPEED;

	//�p�x�̕␳
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += (-D3DX_PI * 2);
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += (D3DX_PI * 2);
	}
}

//==========================================
//  �ړ�
//==========================================
void CEnemy_Umbrella::Move()
{
	// �ړ����Ԃ̉��Z
	m_fMoveTime += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// ����ݒ�
	if (m_fMoveTime >= D3DX_PI * 2.0f)
	{
		m_fMoveTime -= D3DX_PI * 2.0f;
	}

	// ���W��ݒ�
	m_pos.y = m_posDefault.y + (cosf(m_fMoveTime) * POS_DISTANCE);
	m_pos.x = m_posDefault.x + (sinf(m_fMoveTime) * POS_DISTANCE);
}

//==========================================
//  �v���C���[�̔�������
//==========================================
bool CEnemy_Umbrella::CalcDistancePlayer()
{
	// ��ʊO�̏ꍇ�͔��肵�Ȃ�
	if (!CGameManager::GetCamera()->OnScreen(m_pos))
	{
		return false;
	}

	// �v���C���[�̋������擾
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetCenterPos();

	// �v���C���[�ւ̃x�N�g�������߂�
	D3DXVECTOR3 vec = pos - m_pos;

	// ���������̔��������
	if (LOOK_PLAYER * LOOK_PLAYER >= vec.x * vec.x + vec.y * vec.y)
	{
		return true;
	}

	return false;
}
