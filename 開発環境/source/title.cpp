//==========================================
//
//  �^�C�g���̃��S(title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "cut.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CTitle::CTitle(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CTitle::~CTitle()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTitle::Init(void)
{
	return CObject3D::Init();
}

//==========================================
//  �I������
//==========================================
void CTitle::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTitle::Update(void)
{
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CTitle::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�J�����O���I�t
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�`��
	CObject3D::Draw();

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�J�����O���I��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//==========================================
//  �|���S�����a��
//==========================================
void CTitle::CutTitle(void)
{
	CCut::Create(m_pos, m_size, m_pTexture);
	Uninit();
}

//==========================================
//  ��������
//==========================================
CTitle* CTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X����
	CTitle *pTitle = new CTitle;

	//�l��ݒ�
	pTitle->m_pos = pos;
	pTitle->m_size = size;

	//����������
	pTitle->Init();

	//�e�N�X�`�����蓖��
	pTitle->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(CTexture::TITLE));

	return pTitle;
}
