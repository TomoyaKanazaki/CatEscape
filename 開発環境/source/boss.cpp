//==========================================
//
//  �{�X�N���X(boss.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss.h"
#include "model.h"
#include "motion.h"
#include "gamemanager.h"
#include "camera.h"
#include "debugproc.h"
#include "manager.h"
#include "gametime.h"
#include "boss_effect.h"
#include "texture.h"
#include "orbit.h"
#include "player.h"
#include "bullet.h"
#include "enemylifemanager.h"
#include "blade.h"
#include "input.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 BOSS_SIZE = D3DXVECTOR3(100.0f, 100.0f, 50.0f); // �{�X�̑傫��
	const D3DXVECTOR3 CENTER_POS = D3DXVECTOR3(0.0f, 40.0f, 0.0f); // ���S���W�ƃI�u�W�F�N�g���W�̍�
	const D3DXVECTOR3 TARGET_POS[2] = { D3DXVECTOR3(1450.0f, 150.0f, 0.0f), D3DXVECTOR3(2150.0f, 150.0f, 0.0f) }; // ��{�ҋ@�ʒu
	const float MAX_LIFE = 100.0f; // �̗͂̍ő�l
	const float DAMAGE = 1.0f; // ���̍U������󂯂�_���[�W��
	const float INVINCIBLE_TIME = 0.1f; // ���G����
	const float MOVE_SPEED = 200.0f; // �ړ����x
	const float POS_ERROR = 10.0f; // �ڕW�ʒu�Ƃ̋��e�덷
	const float ACTION_DEFERMENT = 1.0f; // ���̍s���܂ł̗P�\����
	const float ATTACK_LENGTH = 500.0f; // �������U�������鋗��
	const int ATTACK_KIND = 3; // �U���̎��
	const float SCREEN_CENTER = 1800.0f; // ��ʂ̒��S
	const float DASH_BEFORE = 1.5f; // �ːi�̑O�ɉ�ʊO�őҋ@���鎞��
	const float DASH_AFTER = 0.5f; // �ːi�̌�ɉ�ʊO�őҋ@���鎞��
	const float DASH_SPEED = -5.0f; // �ːi�̑��x
	const float LIMIT_HEIGHT = 50.0f; // �Œ�̍���
	const float ATTACK_SPEED = 200.0f; // �U�����̈ړ����x
	const float ATTACK_MIN_LENGTH = 50.0f; // �U�����̈ړ����x
	const D3DXVECTOR3 RAIN_POS = D3DXVECTOR3(1800.0f, 300.0f, 0.0f); // �J�~�炵�̑ҋ@�ʒu
	const D3DXVECTOR3 RUSH_POS = D3DXVECTOR3(1800.0f, 100.0f, 0.0f); // �J�~�炵�̑ҋ@�ʒu
	const float RAIN_ADD = 60.0f; // �J�~�炵�s�����ǉ�����郉�C�t
	const int RAINBULLET_NUM = 10; // �J�~�炵�ŏo���e�̐�
}

//==========================================
//  �R���X�g���N�^
//==========================================
CBoss::CBoss(int nPriority) : CEnemy(nPriority),
m_State(POP),
m_oldState(POP),
m_MoveTimer(0.0f),
m_Wait(false),
m_Dash(false),
m_nAttackKind(ATTACK_KIND),
m_bRain(false),
m_bRainWait(false),
m_nBulletNum(0)
{
	m_pOrbit[0] = m_pOrbit[1] = nullptr;
} 

//==========================================
//  �f�X�g���N�^
//==========================================
CBoss::~CBoss()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBoss::Init(void)
{
	// �^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	// �K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_BOSS);

	// ������
	HRESULT hr = CObject_Char::Init();

	// �Z�b�g�A�b�v
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::BOSS_POP);

	// �T�C�Y��ݒ�
	m_size = BOSS_SIZE;
	CalcHitLength(m_size);

	// �̗͂�ݒ�
	m_fLife = MAX_LIFE;

	// �o���G�t�F�N�g�̔���
	CBossEffect::Create(m_pos);

	// �F�ύX�t���O�𗧂Ă�
	ChangeColor(true);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	// ���S���W�̐ݒ�
	m_posCenter = m_pos + CENTER_POS;

	// ���ɋO�Ղ�t����
	if (m_pOrbit[0] == nullptr)
	{
		m_pOrbit[0] = COrbit::Create(m_ppModel[4], D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, -115.0f), 10);
		m_pOrbit[0]->SwitchDraw(false);
	}
	if (m_pOrbit[1] == nullptr)
	{
		m_pOrbit[1] = COrbit::Create(m_ppModel[5], D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, -115.0f), 10);
		m_pOrbit[1]->SwitchDraw(false);
	}

	// ���[�V������ݒ�
	m_pMotion->Set(CMotion::BOSS_WAIT);

	// �̗͕\��
	CEnemyLifeManager::Create();

	return hr;
}

//==========================================
//  �I������
//==========================================
void CBoss::Uninit(void)
{
	// �O�Ղ̏I��
	for (int i = 0; i < 2; ++i)
	{
		if (m_pOrbit[i] != nullptr)
		{
			m_pOrbit[i]->Uninit();
			m_pOrbit[i] = nullptr;
		}
	}

	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBoss::Update(void)
{
	// �f���^�^�C���̎擾
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// �s�����x�����Z����
	if (m_col.a < 1.0f)
	{
		m_col.a += m_fDeltaTime;

		if (m_col.a > 1.0f) // �o������
		{
			m_col.a = 1.0f;
			ChangeColor(false);
			m_State = MOVE;

			// �ڕW�ʒu��ݒ�
			m_TargetPos = TARGET_POS[rand() % 2];
		}
	}

	// �팂���̏���
	Attacked();

	// �ҋ@���ɍs���̒��I���s��
	if (m_State == NEUTRAL)
	{
		Neutral();
	}

	//�ړ����Ƒҋ@���Ƀv���C���[������
	if (m_State == NEUTRAL || m_State == MOVE)
	{
		RotateToPlayer();
	}

	// �ړ�
	Move();

	// ���S����
	if (m_fLife <= 0.0f)
	{
		m_pos = RUSH_POS;
		m_State = RUSH;
	}

	// ���[�V����
	Motion();

	// �U������
	AttackState();

	// �f�o�b�O�\��
	DebugProc::Print("�{�X�̗̑� : %f\n", m_fLife);
	DebugProc::Print("�ړ��� : %f\n", m_move.x);
	DebugProc::Print("�ʒu : %f, %f\n", m_pos.x, m_pos.y);
	DebugProc::Print("��� : ");
	switch (m_State)
	{
	case POP: // �o�����
		DebugProc::Print("�o��\n");
		break;
	case MOVE: // �ړ����
		DebugProc::Print("�ړ�\n");
		break;
	case NEUTRAL: // �ҋ@���
		DebugProc::Print("�ҋ@\n");
		break;
	case DEATH: // ���S���
		DebugProc::Print("���S\n");
		break;
	case ATTACK: // �ʏ�U��
		DebugProc::Print("�U��\n");
		break;
	case DASH: // �ːi�U��
		DebugProc::Print("�ːi\n");
		break;
	case BULLET: // �������U��
		DebugProc::Print("�S��\n");
		break;
	case RAIN: // �J�~�炵
		DebugProc::Print("�~�J\n");
		break;
	case RUSH: // �ƂǂߘA��
		DebugProc::Print("�K�E\n");
		break;
	}

	if (m_State == RUSH)
	{
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// �X�V
	CEnemy::Update();

	// ���S���W�̐ݒ�
	m_posCenter = m_pos + CENTER_POS;

	// �̗͂������Ă�����U���p�^�[���𑝂₷
	if (!m_bRain && m_fLife <= RAIN_ADD)
	{
		m_bRain = true;
		++m_nAttackKind;
	}

#ifdef _DEBUG

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_1))
	{
		m_fLife = 0.0f;
	}

#endif
}

//==========================================
//  �`�揈��
//==========================================
void CBoss::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  �팂���̏���
//==========================================
void CBoss::Attacked()
{
	// �o����Ԃ���ю��S��Ԓ��͍U�����󂯂Ȃ�
	if (m_State == POP || m_State == DEATH)
	{
		return;
	}

	// ��Ԗ��̏���
	if (m_ObjState == ATTACKED)
	{
		m_fLife -= DAMAGE;
		m_AllDamage += DAMAGE;
		m_ObjState = INVINCIBLE;
		WhiteOut(true);
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
}

//==========================================
//  ���[�V����
//==========================================
void CBoss::Motion()
{
	//���[�V�������X�V
	if (m_State != m_oldState)
	{
		switch (m_State)
		{
		case POP: // �o�����
			m_pMotion->Set(CMotion::BOSS_POP);
			break;
		case MOVE: // �ړ����
			m_pMotion->Set(CMotion::BOSS_WAIT);
			break;
		case NEUTRAL: // �ҋ@���
			m_pMotion->Set(CMotion::BOSS_WAIT);
			break;
		case DEATH: // ���S���
			m_pMotion->Set(CMotion::BOSS_DEATH);
			break;
		case ATTACK: // �ʏ�U��
			m_pMotion->Set(CMotion::BOSS_ATTACK);
			break;
		case DASH: // �ːi�U��
			m_pMotion->Set(CMotion::BOSS_DASH);			
			break;
		case BULLET: // �������U��
			m_pMotion->Set(CMotion::BOSS_BULLET);
			break;
		case RAIN: // �J�~�炵
			m_pMotion->Set(CMotion::BOSS_WAIT);
			break;
		case RUSH: // ���߂̘A��
			m_pMotion->Set(CMotion::BOSS_DEATH);
			break;
		}
	}

	//���݂̏�Ԃ�ۑ�
	m_oldState = m_State;
}

//==========================================
//  �ړ�����
//==========================================
void CBoss::Move()
{
	// �ړ���Ԃ̎��̂�
	if (m_State != MOVE)
	{
		return;
	}

	// �ڕW�ʒu�ƌ��݈ʒu�����ԃx�N�g�����쐬����
	D3DXVECTOR3 vec = m_TargetPos - m_pos;

	// �x�N�g���̑傫�����덷�͈͓��Ȃ��~
	if (POS_ERROR * POS_ERROR >= vec.x * vec.x + vec.y * vec.y)
	{
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_State = NEUTRAL;
		return;
	}

	// �x�N�g���𐳋K��
	D3DXVec3Normalize(&vec, &vec);

	// �ړ��ʂ�ڕW�ʒu�Ɍ�����
	vec *= MOVE_SPEED * m_fDeltaTime;

	// �ړ��ʂ�K�p
	m_move = vec;
}

//==========================================
//  ��]����
//==========================================
void CBoss::Rotate()
{
	//���[�J���ϐ��錾
	float fRotMove = m_rot.y; //���݂̊p�x
	float fRotDest = 0.0f; //�ڕW�̊p�x
	float fRotDiff = 0.0f; //�ڕW�ƌ��݂̊p�x�̍�

	//�E�ɐi�ގ��͉E������
	if (m_move.x > 0.0f)
	{
		fRotDest = -D3DX_PI * 0.5f;
	}

	//���ɐi�ނƂ��͍�������
	if (m_move.x < 0.0f)
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
//  �ҋ@���̍s��
//==========================================
void CBoss::Neutral()
{
	// �s���^�C�}�[�̉��Z
	m_MoveTimer += m_fDeltaTime;

	// ��莞�Ԃ��o�߂��Ă��Ȃ��ꍇ
	if (m_MoveTimer <= ACTION_DEFERMENT)
	{
		return;
	}

	// �s���^�C�}�[�̃��Z�b�g
	m_MoveTimer = 0.0f;

	// �U���̎�ނ����߂闐��
	int Rand = rand() % m_nAttackKind;

	switch (Rand)
	{
	case 0:
		m_State = DASH;
		break;
	case 1:
		m_State = ATTACK;
		break;
	case 2:
		m_State = BULLET;
		break;
	case 3:
		m_State = RAIN;
		break;
	}
}

//==========================================
//  �U������
//==========================================
void CBoss::AttackState()
{
	Shot();
	Attack();
	Dash();
	Rain();
}

//==========================================
//  �������U��
//==========================================
void CBoss::Shot()
{
	// �������U����Ԃ���Ȃ������甲����
	if (m_State != BULLET)
	{
		return;
	}

	// �U�����[�V����������������e���o��
	if (m_pMotion->GetFinish())
	{
		// �e�𔭎�
		CBullet::Create(m_posCenter);

		// �ړ��s���ɖ߂�
		m_State = MOVE;

		// �ڕW�ʒu��ݒ�
		m_TargetPos = TARGET_POS[rand() % 2];
	}
}

//==========================================
//  �O�A�U��
//==========================================
void CBoss::Attack()
{
	// �U����Ԃ���Ȃ������甲����
	if (m_State != ATTACK)
	{
		return;
	}

	// �O�Ղ̕`����I��
	for (int i = 0; i < 2; ++i)
	{
		if (m_pOrbit[i] != nullptr)
		{
			m_pOrbit[i]->SwitchDraw(true);
		}
	}

	// �v���C���[�Ɍ������Ĉړ�����
	MoveToPlayer();

	// �����蔻��
	Hit();

	// �v���C���[������
	RotateToPlayer();

	// �s�����Ԃ����Z
	m_MoveTimer += m_fDeltaTime;

	// �s�����Ԃ����ɒB������
	if (m_MoveTimer >= 3.0f)
	{
		// �O�Ղ̕`����I�t
		for (int i = 0; i < 2; ++i)
		{
			if (m_pOrbit[i] != nullptr)
			{
				m_pOrbit[i]->SwitchDraw(false);
			}
		}

		// �ړ����Ԃ̏�����
		m_MoveTimer = 0.0f;

		// �ړ���Ԃɖ߂�
		m_State = MOVE;

		// �ڕW�ʒu��ݒ�
		m_TargetPos = TARGET_POS[rand() % 2];
	}
}

//==========================================
//  �ːi�U��
//==========================================
void CBoss::Dash()
{
	// �ːi��Ԃ���Ȃ������甲����
	if (m_State != DASH)
	{
		return;
	}

	// �ړ�����������
	Rotate();

	// ��x��ʊO�ɏo��
	if (!m_Wait)
	{
		if (m_pos.x < SCREEN_CENTER)
		{
			m_move.x = -MOVE_SPEED * m_fDeltaTime;
		}
		else
		{
			m_move.x = MOVE_SPEED * m_fDeltaTime;
		}

		// ��ʊO�ɏo����
		if (!CGameManager::GetCamera()->OnScreen(m_posCenter))
		{
			m_MoveTimer += m_fDeltaTime; // ���Ԃ����Z
		}

		// ��莞�Ԃ��o�߂�����
		if (m_MoveTimer > DASH_BEFORE)
		{
			// �v���C���[�̍����ɍ��킹��
			m_pos.y = CGameManager::GetPlayer()->GetCenterPos().y;

			// ��������
			if (m_pos.y < LIMIT_HEIGHT)
			{
				m_pos.y = LIMIT_HEIGHT;
			}

			//�ړ��ʂɔ{����������
			m_move.x *= DASH_SPEED;

			// �t���O�𗧂Ă�
			m_Wait = true;

			// �^�C�}�[�����Z�b�g
			m_MoveTimer = 0.0f;

			// �O�Ղ𔭐�
			for (int i = 0; i < 2; ++i)
			{
				if (m_pOrbit[i] != nullptr)
				{
					m_pOrbit[i]->SwitchDraw(true);
				}
			}
		}
	}
	else
	{
		// ��ʓ��ɓ�������ːi���t���O�𗧂Ă�
		if (!m_Dash && CGameManager::GetCamera()->OnScreen(m_posCenter))
		{
			m_Dash = true;
		}

		// �ːi���ɉ�ʊO�ɏo����
		if (m_Dash && !CGameManager::GetCamera()->OnScreen(m_posCenter))
		{
			m_MoveTimer += m_fDeltaTime; // ���Ԃ����Z
		}

		// �����蔻��
		Hit();

		// ��莞�Ԃ��o�߂�����
		if (m_MoveTimer > DASH_AFTER)
		{
			// �t���O���ւ��܂�
			m_Wait = false;
			m_Dash = false;

			// �^�C�}�[�����Z�b�g
			m_MoveTimer = 0.0f;

			// �ړ���Ԃɖ߂�
			m_State = MOVE;

			// �ڕW�ʒu��ݒ�
			m_TargetPos = TARGET_POS[rand() % 2];

			// �O�Ղ��폜
			for (int i = 0; i < 2; ++i)
			{
				if (m_pOrbit[i] != nullptr)
				{
					m_pOrbit[i]->SwitchDraw(false);
				}
			}
		}
	}
}

//==========================================
//  �J�~�炵
//==========================================
void CBoss::Rain()
{
	// �ːi��Ԃ���Ȃ������甲����
	if (m_State != RAIN)
	{
		return;
	}

	// �ڕW�n�_�Ɍ������Ĉړ�����
	if (!m_bRainWait)
	{
		D3DXVECTOR3 vec = RAIN_POS - m_pos;

		// �x�N�g���̑傫�����덷�͈͓��Ȃ��~
		if (POS_ERROR * POS_ERROR >= vec.x * vec.x + vec.y * vec.y)
		{
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_bRainWait = true;
			m_MoveTimer = 0.0f;
			return;
		}

		// �x�N�g���𐳋K��
		D3DXVec3Normalize(&vec, &vec);

		// �ړ��ʂ�ڕW�ʒu�Ɍ�����
		vec *= MOVE_SPEED * m_fDeltaTime;

		// �ړ��ʂ�K�p
		m_move = vec;
	}
	else
	{
		//���[�J���ϐ��錾
		float fRotMove = m_rot.y; //���݂̊p�x
		float fRotDest = 0.0f; //�ڕW�̊p�x

		//�ړ��␳
		float fRotDiff = fRotDest - fRotMove;	//�ڕW�܂ł̈ړ������̍���

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

		// �s�����Ԃ����Z
		m_MoveTimer += m_fDeltaTime;

		// �s�����Ԃ��}������e�𐶐�
		if (m_MoveTimer >= 0.5f)
		{
			// �^�C�}�[�����Z�b�g
			m_MoveTimer = 0.0f;

			// �����擾
			int nRand = rand();

			// ���l�𐧌�����
			nRand %= (int)(TARGET_POS[0].x - TARGET_POS[1].x + 1);

			// �e�̐����ʒu��ݒ�
			D3DXVECTOR3 pos = m_posCenter;
			pos.x = TARGET_POS[0].x + (float)nRand;

			// �e�𐶐�
			CBlade::Create(pos);

			// �e�̐������Z
			++m_nBulletNum;

			// �e�̐������ȏ�ňړ����
			if (m_nBulletNum >= RAINBULLET_NUM)
			{
				m_State = MOVE;
				m_nBulletNum = 0;
				m_bRainWait = false;
			}
		}
	}
}

//==========================================
//  �U������
//==========================================
void CBoss::Hit()
{
	// ����쐬�p���W
	D3DXVECTOR3 pos[2] = { D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f) };

	// ���̋O�Ղɓ����蔻�����������
	for (int i = 0; i < 2; ++i)
	{
		// ���W���擾
		m_pOrbit[i]->GetForemostLine(&pos[0], &pos[1]);

		// �v���C���[���W���擾
		D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetCenterPos();

		// �v���C���[�T�C�Y���擾
		float length = CGameManager::GetPlayer()->GetHitLength();

		// �n�_����I�_�܂ł̃x�N�g�������߂�
		D3DXVECTOR3 vecLine = pos[0] - pos[1];

		// �n�_����ڕW�_�܂ł̃x�N�g�������߂�
		D3DXVECTOR3 vecToPos = posPlayer - pos[1];

		// �e�x�N�g���̑傫�������߂�
		float lengthLine = sqrtf((vecLine.x * vecLine.x) + (vecLine.y * vecLine.y));
		float lengthToPos = sqrtf((vecToPos.x * vecToPos.x) + (vecToPos.y * vecToPos.y));

		// �}��ϐ�t�����߂�
		float t = (lengthLine * lengthToPos) / (lengthLine * lengthLine);

		// �����̔���
		if (0.0f <= t && t <= 1.0f)
		{
			// �ڕW�_���璼���ɐ��������������̌�_�����߂�
			D3DXVECTOR3 posCross = pos[1] + (t * vecLine);

			// ��_����ڕW�_�܂ł̃x�N�g�������߂�
			D3DXVECTOR3 vecToCross = posPlayer - posCross;

			// ���苗���̔�r
			if (length * length >= (vecToCross.x * vecToCross.x) + (vecToCross.y * vecToCross.y))
			{
				// �������Ă������̏���
				CGameManager::GetPlayer()->Attacked();
			}
		}

	}
}

//==========================================
//  �v���C���[�Ɍ������Ĉړ�����
//==========================================
void CBoss::MoveToPlayer()
{
	// �v���C���[�̈ʒu���擾
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetCenterPos();

	// ���݈ʒu����v���C���[�̈ʒu�ւ̃x�N�g�����Z�o
	D3DXVECTOR3 vec = posPlayer - m_pos;

	// �߂��ꍇ�͒�~
	if (ATTACK_MIN_LENGTH * ATTACK_MIN_LENGTH >= vec.x * vec.x + vec.y * vec.y)
	{
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		return;
	}

	// �x�N�g���𐳋K��
	D3DXVec3Normalize(&vec, &vec);

	// �ړ��ʂ�ݒ�
	m_move = vec * ATTACK_SPEED * m_fDeltaTime;
}
