//==========================================
//
//  ������@(tutorial.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial.h"
#include "enemymanager.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 TUTORIAL_SIZE = D3DXVECTOR3(225.0f, 63.0f, 0.0f); // �|���S���T�C�Y
	const D3DXVECTOR3 TUTORIAL_POS = D3DXVECTOR3(117.0f, 44.0f, 0.0f); // �|���S�����W
}

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CTutorial::m_nIdx = 0;

//==========================================
//  �R���X�g���N�^
//==========================================
CTutorial::CTutorial(int nPriority) : CObject2D(nPriority)
{
}

//==========================================
//  �f�X�g���N�^
//==========================================
CTutorial::~CTutorial()
{
	--m_nIdx;
}

//==========================================
//  ����������
//==========================================
HRESULT CTutorial::Init(void)
{
	// �ʒu��ݒ�
	m_pos = TUTORIAL_POS;
	m_pos.y += TUTORIAL_SIZE.y * m_nIdx; 

	// �傫����ݒ�
	m_size = TUTORIAL_SIZE;

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::TUTORIAL0 + m_nIdx));

	// �C���f�b�N�X���Z
	++m_nIdx;

	return CObject2D::Init();
}

//==========================================
//  �I������
//==========================================
void CTutorial::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTutorial::Update(void)
{
	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CTutorial::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CTutorial* CTutorial::Create()
{
	// �C���X�^���X����
	CTutorial* pTutorial = new CTutorial;

	// NULL�`�F�b�N
	if (pTutorial == nullptr) { return nullptr; }

	// ����������
	pTutorial->Init();

	return pTutorial;
}
