//==========================================
//
//  �X�e�B�b�N���肮��UI(stick_base.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "stick_base.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "gamemanager.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 STICKSIZE = D3DXVECTOR3(80.0f, 80.0f, 0.0f); // �ʒu
}

//==========================================
//  �R���X�g���N�^
//==========================================
CBase::CBase(int nPriority) : CObject2D(nPriority)
{
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBase::~CBase()
{
}

//==========================================
//  ����������
//==========================================
HRESULT CBase::Init(void)
{
	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::BASE));

	// �傫����ݒ�
	m_size = STICKSIZE;

	return CObject2D::Init();
}

//==========================================
//  �I������
//==========================================
void CBase::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBase::Update(void)
{
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
void CBase::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CBase* CBase::Create(const D3DXVECTOR3& pos)
{
	// �C���X�^���X����
	CBase* pBase = new CBase;

	// NULL�`�F�b�N
	if (pBase == nullptr) { return pBase; }

	// ���l��ݒ�
	pBase->m_pos = pos;

	// ����������
	pBase->Init();

	return pBase;
}
