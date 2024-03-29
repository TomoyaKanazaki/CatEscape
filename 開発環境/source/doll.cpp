//==========================================
//
//  �l�`�N���X(doll.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "doll.h"
#include "motion.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CDoll::CDoll(int nPriority) : CObject_Char(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CDoll::~CDoll()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CDoll::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_PLAYER);

	//�����̐ݒ�
	m_rot.y = -D3DX_PI * 0.5f;

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	//����������
	HRESULT hr = CObject_Char::Init();

	//���[�V�������Ƀ��f����n��
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_WAIT);
	m_pMotion->Set(CMotion::PLAYER_IAI);

	return hr;
}

//==========================================
//  �I������
//==========================================
void CDoll::Uninit(void)
{
	CObject_Char::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CDoll::Update(void)
{
	CObject_Char::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CDoll::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  �ړ�����
//==========================================
void CDoll::Dash(void)
{
	//�ʒu��ۑ�
	D3DXVECTOR3 pos = m_pos;
	m_pos *= -1.0f;
}

//==========================================
//  ��������
//==========================================
CDoll* CDoll::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CDoll* pDoll = new CDoll;

	//�l��ݒ�
	pDoll->m_pos = pos;

	//����������
	pDoll->Init();

	return pDoll;
}
