//==========================================
//
//  �A���G�t�F�N�g(rush_effect.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "rush_effect.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CRush::CRush(int nPriority) : CObject2D_Anim(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CRush::~CRush()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CRush::Init()
{
	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::RUSH));

	// �A�j���[�V������ݒ�
	SetAnim(10, 4, false, TYPE_V);

	// �T�C�Y��ݒ�
	m_size = D3DXVECTOR3(FLOAT_SCREEN_WIDTH, FLOAT_SCREEN_HEIGHT, 0.0f);

	// �ʒu��ݒ�
	m_pos = D3DXVECTOR3(FLOAT_SCREEN_WIDTH * 0.5f, FLOAT_SCREEN_HEIGHT * 0.5f, 0.0f);

	return CObject2D_Anim::Init();
}

//==========================================
//  �I������
//==========================================
void CRush::Uninit()
{
	CObject2D_Anim::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CRush::Update()
{
	CObject2D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CRush::Draw()
{
	CObject2D_Anim::Draw();
}

//==========================================
//  ��������
//==========================================
CRush* CRush::Create()
{
	// �C���X�^���X����
	CRush* pRush = new CRush;

	// ����������
	pRush->Init();

	return pRush;
}
