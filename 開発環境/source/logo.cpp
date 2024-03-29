//==========================================
//
//  ���S(logo.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo.h"
#include "manager.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CLogo::CLogo(int nPriority) : CObject2D(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CLogo::~CLogo()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CLogo::Init(void)
{
	return CObject2D::Init();
}

//==========================================
//  �I������
//==========================================
void CLogo::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CLogo::Update(void)
{
	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CLogo::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CLogo* CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::TEXTURE tex)
{
	//�ϐ��錾
	CLogo* pLogo = nullptr;

	//���������m��
	pLogo = new CLogo;

	//�l��ۑ�
	pLogo->m_pos = pos;
	pLogo->m_size = size;

	//������
	pLogo->Init();

	//�e�N�X�`�������蓖��
	pLogo->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(tex));

	return nullptr;
}
