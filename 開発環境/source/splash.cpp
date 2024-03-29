//==========================================
//
//  ���U�G�t�F�N�g(splash.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "splash.h"
#include "manager.h"
#include "renderer.h"
#include "gametime.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "slash_effect.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CSplash::CSplash(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CSplash::~CSplash()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CSplash::Init(void)
{
	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::SPLASH));

	// �A�j���[�V������ݒ�
	SetAnim(14, 2, false, TYPE_U);

	// ������
	return CObject3D_Anim::Init();
}

//==========================================
//  �I������
//==========================================
void CSplash::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CSplash::Update(void)
{
	// �X�V����
	CObject3D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CSplash::Draw(void)
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
	CObject3D_Anim::Draw();

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
CSplash* CSplash::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const D3DXCOLOR& col)
{
	// �C���X�^���X����
	CSplash* pSplash = new CSplash;

	// NULL�`�F�b�N
	if (pSplash == nullptr) { return nullptr; }

	// �l�̐ݒ�
	pSplash->m_pos = pos;
	pSplash->m_rot = rot;
	pSplash->m_size = size;
	pSplash->m_col = col;

	// ����������
	pSplash->Init();

	// �l��Ԃ�
	return pSplash;
}
