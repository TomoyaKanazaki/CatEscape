//==========================================
//
//  �w�i�N���X(bg.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bg.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CBg::CBg(int nPriority) : CObject_Mesh(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CBg::~CBg()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBg::Init(void)
{
	//�e�N�X�`���p�^�[���̐ݒ�
	SetPatern(CObject_Mesh::NORMAL);

	return CObject_Mesh::Init();
}

//==========================================
//  �I������
//==========================================
void CBg::Uninit(void)
{
	CObject_Mesh::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBg::Update(void)
{
	//�e�N�X�`�����W���X�V
	D3DXVECTOR2 tex = D3DXVECTOR2(0.00002f, 0.0f);
	AddTexPos(tex);

	CObject_Mesh::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBg::Draw(void)
{
	CObject_Mesh::Draw();
}

//==========================================
//  ��������
//==========================================
CBg* CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumPorygon)
{
	//�C���X�^���X����
	CBg* pBG = nullptr;

	//���������m��
	if (pBG == nullptr)
	{
		pBG = new CBg;
	}
	else
	{
		return nullptr;
	}

	//�l��ۑ�
	pBG->m_pos = pos;
	pBG->m_size = size;
	pBG->m_Mesh.nNumMesh_U = nNumPorygon;
	pBG->m_Mesh.nNumMesh_V = 1;
	pBG->m_rot.x = -D3DX_PI * 0.5f;

	//������
	pBG->Init();

	//�e�N�X�`�������蓖�Ă�
	pBG->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::SKY));

	return pBG;
}
