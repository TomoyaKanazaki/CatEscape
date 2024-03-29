//==========================================
//
//  �X�e�B�b�N���肮��UI(stick.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "stick.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "gamemanager.h"
#include "stick_base.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 STICKPOS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f); // �ʒu
	const D3DXVECTOR3 STICKSIZE = D3DXVECTOR3(100.0f, 100.0f, 0.0f); // �ʒu
	const float STICK_DEAD = 0.0f; // �f�b�h�]�[��
	const float CENTER_DISTANCE = 30.0f; // ���S���痣����鋗��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CStick::CStick(int nPriority) : CObject2D(nPriority)
{
}

//==========================================
//  �f�X�g���N�^
//==========================================
CStick::~CStick()
{
}

//==========================================
//  ����������
//==========================================
HRESULT CStick::Init(void)
{
	// ���W��ݒ�
	m_pos = STICKPOS;

	// �傫����ݒ�
	m_size = STICKSIZE;

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::STICK));

	// ���S��ݒ�
	CBase::Create(STICKPOS);

	return CObject2D::Init();
}

//==========================================
//  �I������
//==========================================
void CStick::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CStick::Update(void)
{
	// �X�e�B�b�N�̓��͂��擾
	D3DXVECTOR3 rot = CManager::GetInstance()->GetJoyPad()->GetStickR(STICK_DEAD);
	D3DXVec3Normalize(&rot, &rot);

	// �ʒu�𔽉f����
	m_pos.x = STICKPOS.x + (rot.x * CENTER_DISTANCE);
	m_pos.y = STICKPOS.y - (rot.z * CENTER_DISTANCE);

	CObject2D::Update();

	// �I��
	if (CGameManager::GetState() == CGameManager::STATE_END)
	{
		Uninit();
	}
}

//==========================================
//  �`�揈��
//==========================================
void CStick::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CStick* CStick::Create()
{
	// �C���X�^���X����
	CStick* pStick = new CStick;

	// NULL�`�F�b�N
	if (pStick == nullptr) { return nullptr; }

	// ����������
	pStick->Init();

	return pStick;
}
