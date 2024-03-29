//==========================================
//
//  �G�N���X(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "gamemanager.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "enemy_lantern.h"
#include "enemy_umbrella.h"
#include "boss.h"
#include "gametime.h"
#include "camera.h"
#include "boss_result.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float SLICE_SCALE = 1.0f;
	const float DAMAGE = 1.0f; //���̍U���Ŏ󂯂�_���[�W
	const D3DXVECTOR3 ENEMY_SIZE_DEFAULT = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	const float INVINCIBLE_TIME = 0.1f; // ���G����
}

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
float CEnemy::m_AllDamage = 0.0f; // �󂯂��_���[�W�̍��v

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemy::CEnemy(int nPriority) : CObject_Char(nPriority),
m_type(NONE),
m_fLife(0.0f),
m_fInvincible(0.0f)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemy::Init(void)
{
	return CObject_Char::Init();
}

//==========================================
//  �I������
//==========================================
void CEnemy::Uninit(void)
{
	// �I��
	CObject_Char::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemy::Update(void)
{
	// �ړ��ʂ̓K�p
	m_pos += m_move;

	CObject_Char::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemy::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  ��������
//==========================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, CEnemy::TYPE type)
{
	//�ϐ��錾
	CEnemy* pEnemy = nullptr;

	//���������m��
	switch (type)
	{
	case LANTERN:
		pEnemy = new CEnemy_Lantern;
		break;

	case UMBRELLA:
		pEnemy = new CEnemy_Umbrella;
		break;

	case BOSS:
		pEnemy = new CBoss;
		break;

	case RESULT:
		pEnemy = new CBossResult;
		break;

	default:
		pEnemy = nullptr;
		break;
	}

	// NULL�`�F�b�N
	if (pEnemy == nullptr) { return nullptr; }

	//�l��ݒ�
	pEnemy->m_pos = pos;
	pEnemy->m_type = type;

	//����������
	pEnemy->Init();

	return pEnemy;
}

//==========================================
//  �ړ�����������
//==========================================
void CEnemy::RotateToMove(void)
{
	//�ړ����ĂȂ����͉�]���Ȃ�
	if (m_move.x == 0.0f)
	{
		return;
	}

	//�E�ɐi�ގ��͉E������
	if (m_move.x > 0.0f)
	{
		m_rot.y = D3DX_PI;
	}

	//���ɐi�ނƂ��͍�������
	if (m_move.x < 0.0f)
	{
		m_rot.y = 0.0f;
	}
}

//==========================================
//  �v���C���[������
//==========================================
void CEnemy::RotateToPlayer()
{
	//���[�J���ϐ��錾
	float fRotMove = m_rot.y; //���݂̊p�x
	float fRotDest = 0.0f; //�ڕW�̊p�x
	float fRotDiff = 0.0f; //�ڕW�ƌ��݂̊p�x�̍�

	// �v���C���[�̈ʒu���擾
	D3DXVECTOR3 posPolyer = CGameManager::GetPlayer()->GetPos();

	// �v���C���[�̂������������
	if (posPolyer.x > m_pos.x)
	{
		fRotDest = -D3DX_PI * 0.5f;
	}
	if (posPolyer.x < m_pos.x)
	{
		fRotDest = D3DX_PI * 0.5f;
	}

	//�ړ��␳
	fRotDiff = fRotDest - fRotMove;	//�ڕW�܂ł̈ړ������̍���

	//�p�x�̕␳
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff += (-D3DX_PI * 2);
	}
	else if (fRotDiff <= -D3DX_PI)
	{
		fRotDiff += (D3DX_PI * 2);
	}

	//�����]��
	m_rot.y += fRotDiff * 0.2f;

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
//  �팂���̏���
//==========================================
void CEnemy::Attacked()
{
	// ��Ԗ��̏���
	if (m_ObjState == ATTACKED)
	{
		// ��ʊO���ƍU�����󂯂Ȃ�
		if (CGameManager::GetCamera()->OnScreen(m_pos))
		{
			m_fLife -= DAMAGE;
			m_AllDamage += DAMAGE;
			WhiteOut(true);
		}

		m_ObjState = INVINCIBLE;
		return;
	}
	else if (m_ObjState == INVINCIBLE)
	{
		// ���Ԃ̉��Z
		m_fInvincible += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

		// ���G���Ԃ̉���
		if (m_fInvincible >= INVINCIBLE_TIME)
		{
			m_ObjState = NORMAL;
			m_fInvincible = 0.0f;
			WhiteOut(false);
		}
	}

	// �̗͂��s�����玀��
	if (m_fLife <= 0.0f)
	{
		Uninit();
	}
}
