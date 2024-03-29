//==========================================
//
//  ��(field.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CFeild::CFeild(int nPriority) : CObject_Mesh(nPriority)
{
	m_type = MAX;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CFeild::~CFeild()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CFeild::Init(void)
{
	return CObject_Mesh::Init();
}

//==========================================
//  �I������
//==========================================
void CFeild::Uninit(void)
{
	CObject_Mesh::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CFeild::Update(void)
{
	//�e�N�X�`�����W���X�V
	if (m_type == WATER)
	{
		D3DXVECTOR2 tex = D3DXVECTOR2(0.003f, 0.0f);
		AddTexPos(tex);
	}

	CObject_Mesh::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CFeild::Draw(void)
{
	CObject_Mesh::Draw();
}

//==========================================
//  ��������
//==========================================
CFeild* CFeild::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR2 uv, type type)
{
	//�C���X�^���X����
	CFeild* pField = NULL;

	//NULL�`�F�b�N
	if (pField == NULL)
	{
		//���������m��
		pField = new CFeild;
	}

	if (pField == NULL)
	{
		return NULL;
	}

	//��������ݒ�
	pField->m_Mesh.nNumMesh_U = (int)uv.x;
	pField->m_Mesh.nNumMesh_V = (int)uv.y;
	pField->m_pos = pos;
	pField->m_size = size;
	pField->m_rot = rot;
	pField->m_type = type;

	//������
	pField->Init();

	//�e�N�X�`���̊��蓖��
	switch (type)
	{
	case WATER:
		pField->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::WATER));
		break;
	case SOIL:
		pField->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::FIELD));
		break;
	}

	//�|�C���^��Ԃ�
	return pField;
}
