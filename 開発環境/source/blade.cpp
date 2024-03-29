//==========================================
//
//  ���e�N���X(blade.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "blade.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "gametime.h"
#include "camera.h"
#include "orbit.h"
#include "motion.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float MOVE_SPEED = 300.0f; // �P�ʎ��ԓ�����̈ړ���
	const float WAIT_TIME = 1.0f; // �o����ړ�����܂ł̑ҋ@����
	const float HIT_LENGTH = 60.0f; // ���苗��
	const float ROTATE_SPEED = 0.1f;
}

//==========================================
//  �R���X�g���N�^
//==========================================
CBlade::CBlade(int nPriority) : CObject_Char(nPriority),
m_rotation(0.0f),
m_Time(0.0f),
m_pOrbit(nullptr)
{
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBlade::~CBlade()
{
}

//==========================================
//  ����������
//==========================================
HRESULT CBlade::Init(void)
{
	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::BLADE);

	// ����������
	HRESULT hr = CObject_Char::Init();

	// �ړ��ʂ̐ݒ�
	SetMove();

	// ���ɋO�Ղ�t����
	if (m_pOrbit == nullptr)
	{
		m_pOrbit = COrbit::Create(m_ppModel[0], D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, -50.0f), 10);
		m_pOrbit->SwitchDraw(false);
	}

	return hr;
}

//==========================================
//  �I������
//==========================================
void CBlade::Uninit(void)
{
	CObject_Char::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBlade::Update(void)
{
	// �f���^�^�C�����擾
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// �o�����Ԃ����Z
	m_Time += m_fDeltaTime;

	// �ړ��ʂ̓K�p
	if (m_Time >= WAIT_TIME)
	{
		m_pos += m_move * m_fDeltaTime;
		m_pOrbit->SwitchDraw(true);
	}

	// ��]
	m_rot.x += m_Time * ROTATE_SPEED;

	// �����蔻��
	Hit();

	CObject_Char::Update();

	// ��ʊO�ō폜
	if (!CGameManager::GetCamera()->OnScreen(m_pos))
	{
		m_pOrbit->SwitchDraw(false);
		Uninit();
	}
}

//==========================================
//  �`�揈��
//==========================================
void CBlade::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  ��������
//==========================================
CBlade* CBlade::Create(const D3DXVECTOR3& pos)
{
	// �C���X�^���X����
	CBlade* pBullet = new CBlade;

	// NULL�`�F�b�N
	if (pBullet == nullptr) { return nullptr; }

	// �ʒu��ݒ�
	pBullet->m_pos = pos;

	// ����������
	pBullet->Init();

	return pBullet;
}

//==========================================
//  �ړ��ʂ̐ݒ�
//==========================================
void CBlade::SetMove()
{
	// �v���C���[�̍��W���擾
	D3DXVECTOR3 vec = CGameManager::GetPlayer()->GetCenterPos() - m_pos;
	
	//�E�ɐi�ގ��͉E������
	if (vec.x > 0.0f)
	{
		m_rot.y = -D3DX_PI * 0.5f;
	}

	//���ɐi�ނƂ��͍�������
	if (vec.x < 0.0f)
	{
		m_rot.y = D3DX_PI * 0.5f;
	}

	// �x�N�g���𐳋K��
	D3DXVec3Normalize(&vec, &vec);

	// �P�ʎ��ԓ�����̈ړ��ʂ�K�p����
	m_move = vec * MOVE_SPEED;
}

//==========================================
//  �����蔻��
//==========================================
void CBlade::Hit()
{
	// �v���C���[�ւ̃x�N�g�����Z�o
	D3DXVECTOR3 vec = CGameManager::GetPlayer()->GetCenterPos() - m_pos;
	vec.z = 0.0f;

	// �����𑪂�
	if (HIT_LENGTH * HIT_LENGTH > vec.x * vec.x + vec.y * vec.y)
	{
		// �������Ă������̏���
		CGameManager::GetPlayer()->Attacked();
	}
}
