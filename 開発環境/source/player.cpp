//==========================================
//
//  �v���C���[�N���X(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <windows.h>
#include "player.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "sound.h"
#include "debugproc.h"
#include "camera.h"
#include "model.h"
#include "motion.h"
#include "layer.h"
#include "gamemanager.h"
#include "camera.h"
#include "gametime.h"
#include "effect3D.h"
#include "orbit.h"
#include "slash.h"
#include "enemy.h"
#include "slash_effect.h"
#include "lifemanager.h"
#include "enemymanager.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float HIT_LENGTH = 25.0f; // �G�Ƃ̐ڐG�Ɏg������̑傫��
	const float ATTACK_SPEED = 1000.0f; // �U�����̈ړ����x
	const float ATTACK_TIME = 0.2f; // �U���Ɏg�p���鎞��
	const float PLAYER_SPEED = 350.0f; //�v���C���[�̈ړ����x
	const float PLAYER_HEIGHT = 40.0f; //�v���C���[�̍���
	const float DASH_DISTANCE = 200.0f; //�_�b�V���̈ړ�����
	const float HIT_RANGE = 2020.0f; //�q�b�g����͈�
	const float JUMP_MOVE = 600.0f; //�W�����v��
	const float GRAVITY = 1500.0f; //�d��
	const int MAX_ATTACK_COUNT = 3; // �A���U���̍ő吔
	const float ATTACK_COOL_TIME = 0.2f; // �U���̃N�[���^�C��
	const float LIMIT_HEIGHT_NORMAL = 300.0f; // �����̏㏸���E
	const float LIMIT_HEIGHT_BOSS = 380.0f; // �{�X�풆�̏㏸���E
	const float LIMIT_WIDTH_BOSS = 1350.0f; // �{�X�풆�̈ړ����E
	const int MAX_LIFE = 10; // �̗͏��
	const float DAMAGE_TIME = 0.8f;
	const float DAMAGE_SPEED = 0.3f; // �_���[�W��Ԓ��̈ړ��{��
	const D3DXCOLOR SLASH_COLOR = D3DXCOLOR(0.1f, 1.0f, 0.1f, 1.0f);
	const D3DXVECTOR3 ENEMY_DISTANCE = D3DXVECTOR3(-60.0f, -20.0f, 0.0f);
}

//==========================================
//  �R���X�g���N�^
//==========================================
CPlayer::CPlayer(int nPriority) : CObject_Char(nPriority),
m_fStateCounter(0.0f),
m_AttackCoolTime(ATTACK_COOL_TIME),
m_AttackCounter(0),
m_bAttack(true),
m_posStart(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
m_pOrbit(nullptr),
m_nLife(MAX_LIFE),
m_bDamage(false),
m_fDamageCounter(0.0f),
m_fHitLength(HIT_LENGTH),
m_bDoubleJump(false)
{
	m_CenterPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDashAngle = 0.0f;
	m_bRand = true;
	m_bDash = false;
	m_oldposModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_State = NEUTRAL;
	m_oldState = NEUTRAL;
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
}

//==========================================
//  �f�X�g���N�^
//==========================================
CPlayer::~CPlayer()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CPlayer::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_PLAYER);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	HRESULT hr = CObject_Char::Init();

	//���[�V�������Ƀ��f����n��
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_WAIT);

	//���S���W��ݒ�
	m_CenterPos = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	// �O�Ղ̐���
	if (m_pOrbit == nullptr)
	{
		m_pOrbit = COrbit::Create(m_ppModel[14], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 30.0f, 3.0f), 6);
		m_pOrbit->SwitchDraw(false);
	}

	// �̗͂�\��
	CLifeManager::Create();

	return hr;
}

//==========================================
//  �I������
//==========================================
void CPlayer::Uninit(void)
{
	// �O�Ղ̏I��
	if (m_pOrbit != nullptr)
	{
		m_pOrbit->Uninit();
		m_pOrbit = nullptr;
	}

	CObject_Char::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CPlayer::Update(void)
{
	// �O����W�ɕۑ�
	m_oldPos = m_pos;
	m_oldposModel = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	DebugProc::Print("�v���C���[�ʒu : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);

	// �o�ߎ��Ԃ��擾����
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// ���S���W��ݒ�
	m_CenterPos = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	// ���߂��h���Ƃ�
	if (CGameManager::GetState() == CGameManager::STATE_RUSH || CGameManager::GetState() == CGameManager::STATE_END)
	{
		// ���b�V�����
		m_State = RUSH;

		// ������␳
		m_rot.y = -D3DX_PI * 0.5f;

		// ���W��␳
		m_pos = CGameManager::GetEnemy()->GetBoss()->GetCenterPos() + ENEMY_DISTANCE;

		// �E�X�e�B�b�N���͂��������ꍇ
		if (CManager::GetInstance()->GetJoyPad()->GetStickTriggerR(CJoyPad::STICK_ALL))
		{
			// �U���̕������Z�o����
			float rot = atan2f(rand() - (RAND_MAX * 0.5f), rand() - (RAND_MAX * 0.5f));

			// �U���𐶐�
			CSlash::Create(CGameManager::GetEnemy()->GetBoss()->GetCenterPos(), rot);
		}
	}
	else
	{
		// �U��
		if (CGameManager::GetState() != CGameManager::STATE_END)
		{
			if (CManager::GetInstance()->GetJoyPad()->GetPress(CJoyPad::BUTTON_RB) || m_State == IAI)
			{
				//Dash();
			}
			else
			{
				Attack();
			}

			// �W�����v
			Jump();
		}

		// �ړ��̏���
		Move();

		// ��]�̏���
		Rotate();

		// �ړ�����
		Limit();

		// �d��
		Gravity();

		// �_���[�W
		Damage();

		// �̗͂�0�ɂȂ����玀��
		if (m_nLife == 0)
		{
			m_State = DEATH;
			ChangeColor(false);
		}
	}

	// ���[�V����
	Motion();

	// �X�V
	CObject_Char::Update();

	// ���Ƀ_���[�W��Ԃ̎�
	if (m_bDamage)
	{
		// �_���[�W���Ԃ̉��Z
		m_fDamageCounter += m_fDeltaTime;

		// ��莞�Ԃ��o�߂��Ă�����
		if (m_fDamageCounter >= DAMAGE_TIME)
		{
			m_bDamage = false;
			ChangeColor(false);
		}
	}

#ifdef _DEBUG

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		m_pos.x = 1300.0f;
	}

#endif
}

//==========================================
//  �`�揈��
//==========================================
void CPlayer::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  �U�����󂯂����̏���
//==========================================
void CPlayer::Attacked()
{
	// ���Ƀ_���[�W��Ԃ̎�
	if (m_bDamage)
	{
		// ������
		return;
	}

	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_DEATH);
	--m_nLife;
	m_bDamage = true;
	m_fDamageCounter = 0.0f;
	ChangeColor(true);
}

//==========================================
//  �I�u�W�F�N�g��������
//==========================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//�C���X�^���X����
	CPlayer *pPlayer = NULL;

	//NULL�`�F�b�N
	if (pPlayer == NULL)
	{
		//���������m��
		pPlayer = new CPlayer;
	}

	//�e����̕ۑ�
	pPlayer->m_pos = pos;
	pPlayer->m_size = size;
	pPlayer->m_rot = rot;

	//������
	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}

	//�|�C���^��Ԃ�
	return pPlayer;
}

//==========================================
//  ���[�V�����̍X�V
//==========================================
void CPlayer::Motion(void)
{
	//��ԍX�V
	if (m_State == DEATH || m_State == IAI || m_State ==RUSH)
	{
		//�X�V���Ȃ�
	}
	else if (!m_bRand) //���n���ĂȂ����
	{
		if (m_move.y > 0.0f)
		{
			m_State = JUMP;
		}
		else
		{
			m_State = FALL;
		}
	}
	else if (m_move.x != 0.0f) //�ړ����Ă�����
	{
		m_State = WALK;
	}
	else //��L�̂ǂ�ł��Ȃ����
	{
		m_State = NEUTRAL;
	}

	//���[�V�������X�V
	if (m_State != m_oldState)
	{
		switch (m_State)
		{
		case IAI:
			m_pMotion->Set(CMotion::PLAYER_IAI);
			break;
		case JUMP:
			m_pMotion->Set(CMotion::PLAYER_JUMP);
			break;
		case FALL:
			m_pMotion->Set(CMotion::PLAYER_FALL);
			break;
		case WALK:
			m_pMotion->Set(CMotion::PLAYER_WALK);
			break;
		case NEUTRAL:
			m_pMotion->Set(CMotion::PLAYER_WAIT);
			break;
		case DEATH:
			m_pMotion->Set(CMotion::PLAYER_DEATH);
			break;
		case RUSH:
			m_pMotion->Set(CMotion::PLAYER_IAI);
			break;
		}
	}

	//���݂̏�Ԃ�ۑ�
	m_oldState = m_State;
}

//==========================================
//  �ړ�����
//==========================================
void CPlayer::Limit(void)
{
	//X���W�̐���
	if (CGameManager::GetState() != CGameManager::STATE_START && CGameManager::GetState() != CGameManager::STATE_END)
	{
		if (m_pos.x < -2250.0f)
		{
			m_pos.x = -2250.0f;
		}
		if (m_pos.x > 2250.0f)
		{
			m_pos.x = 2250.0f;
		}
	}

	//Y���W�̐���
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
	}
	if (m_pos.y <= 0.0f)
	{
		m_bRand = true;
		m_bDoubleJump = false;
	}

	if (CGameManager::GetState() != CGameManager::STATE_BOSS)
	{
		if (m_pos.y > LIMIT_HEIGHT_NORMAL)
		{
			m_pos.y = LIMIT_HEIGHT_NORMAL;
		}
	}
	else
	{
		if (m_pos.y > LIMIT_HEIGHT_BOSS)
		{
			m_pos.y = LIMIT_HEIGHT_BOSS;
		}
		if (m_pos.x < LIMIT_WIDTH_BOSS)
		{
			m_pos.x = LIMIT_WIDTH_BOSS;
		}
	}
}

//==========================================
//  �ړ��̏���
//==========================================
void CPlayer::Move(void)
{
	// �U����Ԓ��͔�����
	if (m_State == IAI)
	{
		return;
	}

	//���[�J���ϐ��錾
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_State != DEATH)
	{
		//�p�b�h�ړ��ʂ��擾
		move = CManager::GetInstance()->GetJoyPad()->GetStickL(0.1f);

		//�L�[�{�[�h�ړ��ʂ̎擾
		if (move.x == 0.0f)
		{
			move = CManager::GetInstance()->GetKeyboard()->GetWASD();
		}
	}

	//�������s
	if (CGameManager::GetState() == CGameManager::STATE_START)
	{
		move.x = 1.0f;
	}

	//�ړ��ʂ̓K�p
	m_move.x = move.x * PLAYER_SPEED;

	//�����ɂ��ړ��̒�~
	m_move.x += (0.0f - m_move.x) * 0.1f;


	//�ړ��ʂ�K�p
	m_pos += m_move * m_fDeltaTime;
}

//==========================================
//  ��]����
//==========================================
void CPlayer::Rotate(void)
{
	//�ړ����ĂȂ����͉�]���Ȃ�
	if (m_move.x == 0.0f)
	{
		return;
	}

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
//  �W�����v�̏���
//==========================================
void CPlayer::Jump(void)
{
	// �U�����ɔ�����
	if (m_State == IAI)
	{
		return;
	}

	// ���S���ɔ�����
	if (m_State == DEATH)
	{
		return;
	}
	if (CGameManager::GetState() == CGameManager::STATE_START || CGameManager::GetState() == CGameManager::STATE_END)
	{
		return;
	}

	//���n�t���O���I�t�̎�
	else if (!m_bRand && m_bDoubleJump)
	{
		return;
	}

	//�W�����v!
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_SPACE) || CManager::GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_LB))
	{
		if(!m_bRand)
		{
			m_bDoubleJump = true;
		}

		// ���n���Ă��Ȃ����
		m_move.y = JUMP_MOVE;
		m_bRand = false;
	}
}

//==========================================
//  �d�͂̏���
//==========================================
void CPlayer::Gravity(void)
{
	// �U�����͏d�͂��󂯂Ȃ�
	if (m_State == IAI)
	{
		return;
	}

	//�d�̖͂�������
	if (m_bRand)
	{
		m_move.y = 0.0f;
		return;
	}
	else if (m_move.y <= -JUMP_MOVE)
	{
		m_move.y = -JUMP_MOVE;
		return;
	}

	//�ړ��ʂ̌���
	m_move.y -= GRAVITY * CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();
}

//==========================================
//  �E��
//==========================================
void CPlayer::Damage(void)
{
	// �U�����͍U�����󂯂Ȃ�
	if (m_State == IAI || m_State == DEATH)
	{
		return;
	}

	//�����蔻��̐���
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�擪�̃A�h���X���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject* pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_ENEMY || pObj->GetType() == CObject::TYPE_BOSS) //�G�̏ꍇ
			{
				if (pObj->GetObjState() == CObject::NORMAL)
				{
					//�Ώۂ̍��W���擾����
					D3DXVECTOR3 pos = pObj->GetPos();

					//�x�N�g���̎Z�o
					D3DXVECTOR3 vec = m_CenterPos - pos;

					//�x�N�g���̑傫�����r����
					if (HIT_LENGTH * HIT_LENGTH >= (vec.x * vec.x + vec.y * vec.y))
					{
						// �_���[�W����
						Attacked();
					}
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}

//==========================================
//  �U���̏���
//==========================================
void CPlayer::Attack()
{
	// ���S��Ԓ��͔�����
	if (m_State == DEATH)
	{
		return;
	}

	// �E�X�e�B�b�N���͂��������ꍇ
	if (CManager::GetInstance()->GetJoyPad()->GetStickTriggerR(CJoyPad::STICK_ALL))
	{
		// �E�X�e�B�b�N���͂̒l���擾
		D3DXVECTOR3 vecInput = CManager::GetInstance()->GetJoyPad()->GetStickR(0.1f);

		// �U���̕������Z�o����
		float rot = atan2f(vecInput.z, vecInput.x);

		// �U���𐶐�
		CSlash::Create(m_CenterPos, rot);
	}
#ifdef _DEBUG

	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_RIGHT))
	{
		// �U���̕������Z�o����
		float rot = D3DX_PI;

		// �U���𐶐�
		CSlash::Create(m_CenterPos, rot);
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LEFT))
	{
		// �U���̕������Z�o����
		float rot = -D3DX_PI;

		// �U���𐶐�
		CSlash::Create(m_CenterPos, rot);
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_UP))
	{
		// �U���̕������Z�o����
		float rot = D3DX_PI * 0.5f;

		// �U���𐶐�
		CSlash::Create(m_CenterPos, rot);
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_DOWN))
	{
		// �U���̕������Z�o����
		float rot = D3DX_PI * -0.5f;

		// �U���𐶐�
		CSlash::Create(m_CenterPos, rot);
	}

#endif
}

//==========================================
//  �_�b�V������
//==========================================
void CPlayer::Dash()
{
	// ���S��Ԓ��͔�����
	if (m_State == DEATH)
	{
		return;
	}

	// �N�[���^�C������薢�����ƍU���s��
	if (m_AttackCoolTime < ATTACK_COOL_TIME)
	{
		// �U���̃N�[���^�C�������Z
		m_AttackCoolTime += m_fDeltaTime;

		return;
	}

	// �E�X�e�B�b�N���͂̒l���擾
	D3DXVECTOR3 vecInput = CManager::GetInstance()->GetJoyPad()->GetStickR(0.1f);

	// ���͒l��ύX����
	vecInput.y = vecInput.z;
	vecInput.z = 0.0f;

	// �E�X�e�B�b�N���͂��������ꍇ
	if (CManager::GetInstance()->GetJoyPad()->GetStickTriggerR(CJoyPad::STICK_ALL) && m_State != IAI)
	{
		// ���͒l�𐳋K������
		D3DXVec3Normalize(&vecInput, &vecInput);

		// �ړ��ʂ���͕����ɕ�������
		m_move = vecInput * ATTACK_SPEED * m_fDeltaTime;

		// �U����ԂɑJ��
		m_State = IAI;

		// �U�����Ԃ����Z�b�g
		m_fStateCounter = 0.0f;

		// �J�n�n�_���L�^����
		m_posStart = m_CenterPos;

		// �O�Ղ�`��
		m_pOrbit->SwitchDraw(true);
	}

	// �U����Ԓ��̏ꍇ
	if (m_State == IAI)
	{
		// �U�����Ԃ̉��Z
		m_fStateCounter += m_fDeltaTime;

		// �ړ�����
		m_pos += m_move;

		// �U������
		Hit();

		// ��莞�ԂōU������������
		if (m_fStateCounter >= ATTACK_TIME)
		{
			// �J�E���^�[�����Z�b�g
			m_fStateCounter = 0.0f;

			// �󒆂ɂ�����W�����v��Ԃɂ���
			if (m_pos.y > 0.0f)
			{
				// ���n�t���O�I�t
				m_bRand = false;

				// �������
				m_State = FALL;
			}
			else
			{
				// �ҋ@���
				m_State = NEUTRAL;
			}

			// �N�[���^�C�������Z�b�g
			m_AttackCoolTime = 0.0f;

			// �O�Ղ�`��
			m_pOrbit->SwitchDraw(false);
		}
	}
}

//==========================================
//  �G�Ƃ̓����蔻��
//==========================================
void CPlayer::Hit()
{
	//�����蔻��̐���
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�擪�̃A�h���X���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject* pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_ENEMY) //�G�̏ꍇ
			{
				if (pObj->GetObjState() == CObject::NORMAL) // �ʏ��Ԃ̏ꍇ
				{
					// �ڕW�_���擾����
					D3DXVECTOR3 pos = pObj->GetPos();

					// �n�_����I�_�܂ł̃x�N�g�������߂�
					D3DXVECTOR3 vecLine = m_CenterPos - m_posStart;

					// �n�_����ڕW�_�܂ł̃x�N�g�������߂�
					D3DXVECTOR3 vecToPos = pos - m_posStart;

					// �e�x�N�g���̑傫�������߂�
					float lengthLine = sqrtf((vecLine.x * vecLine.x) + (vecLine.y * vecLine.y));
					float lengthToPos = sqrtf((vecToPos.x * vecToPos.x) + (vecToPos.y * vecToPos.y));

					// �}��ϐ�t�����߂�
					float t = (lengthLine * lengthToPos) / (lengthLine * lengthLine);

					// �����̔���
					if (0.0f <= t && t <= 1.0f)
					{
						// �ڕW�_���璼���ɐ��������������̌�_�����߂�
						D3DXVECTOR3 posCross = m_posStart + (t * vecLine);

						// ��_����ڕW�_�܂ł̃x�N�g�������߂�
						D3DXVECTOR3 vecToCross = pos - posCross;

						// ���苗���̔�r
						if (m_fHitLength * m_fHitLength >= (vecToCross.x * vecToCross.x) + (vecToCross.y * vecToCross.y))
						{
							// �������Ă������̉��o�n����
							CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SLICE);
							pObj->SetState(CObject::ATTACKED);
						}
					}
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}
