//==========================================
//
//  3D�|���S���̃G�t�F�N�g(effect3D.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "effect3D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CEffect3D::CEffect3D()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEffect3D::~CEffect3D()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEffect3D::Init(void)
{
	// �e�N�X�`�������蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::EFFECT));

	// ������
	return CObject3D::Init();
}

//==========================================
//  �I������
//==========================================
void CEffect3D::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEffect3D::Update(void)
{
	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEffect3D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`��
	CObject3D::Draw();

	//�A���t�@�u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CEffect3D* CEffect3D::Create(D3DXVECTOR3 pos, bool BillBoard)
{
	// �C���X�^���X����
	CEffect3D* pEffect = new CEffect3D;

	// NULL�`�F�b�N
	if (pEffect == NULL) { return nullptr; }

	// �l��ݒ�
	pEffect->m_pos = pos; // ���W
	pEffect->SwitchBillboard(BillBoard); // �r���{�[�h�ݒ�

	// ����������
	if (FAILED(pEffect->Init())) { return nullptr; }

	// �l��Ԃ�
	return pEffect;
}
