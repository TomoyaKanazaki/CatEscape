//==========================================
//
//  �̗͕\��(life.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "life.h"
#include "manager.h"
#include "gamemanager.h"
#include "player.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 LIFE_SIZE = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	const D3DXVECTOR3 LIFE_LEFT_POS = D3DXVECTOR3(30.0f, FLOAT_SCREEN_HEIGHT - 45.0f, 0.0f);
}

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CLife::m_nNum = 0; // �̗�

//==========================================
//  �R���X�g���N�^
//==========================================
CLife::CLife(int nPriority) : CObject2D(nPriority),
m_nIdx(m_nNum)
{
	++m_nNum;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CLife::~CLife()
{
	--m_nNum;
}

//==========================================
//  ����������
//==========================================
HRESULT CLife::Init(void)
{
	// �T�C�Y��ݒ�
	m_size = LIFE_SIZE;

	// �ʒu��ݒ�
	m_pos = LIFE_LEFT_POS;
	m_pos.x += LIFE_SIZE.x * m_nIdx;

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::LEAF));

	return CObject2D::Init();
}

//==========================================
//  �I������
//==========================================
void CLife::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CLife::Update(void)
{
	// �v���C���[�̃��C�t���擾
	int nLife = CGameManager::GetPlayer()->GetLife();

	// �v���C���[�̃��C�t�������������Ă��������
	if (m_nIdx + 1 > nLife)
	{
		Uninit();
		return;
	}

	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CLife::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CLife* CLife::Create()
{
	// �C���X�^���X����
	CLife* pLife = new CLife;

	// ����������
	pLife->Init();

	return pLife;
}
