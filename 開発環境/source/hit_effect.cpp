//==========================================
//
//  �q�b�g���̃G�t�F�N�g(hit_effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "hit_effect.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 EFFECT_SIZE = D3DXVECTOR3(200.0f, 200.0f, 200.0f); // �T�C�Y
}

//==========================================
//  �R���X�g���N�^
//==========================================
CHitEffect::CHitEffect(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CHitEffect::~CHitEffect()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CHitEffect::Init(void)
{
	// �T�C�Y��ݒ�
	m_size = EFFECT_SIZE;

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::HIT));

	// �A�j���[�V������ݒ�
	SetAnim(15, 1, false, TYPE_U);

	return CObject3D_Anim::Init();
}

//==========================================
//  �I������
//==========================================
void CHitEffect::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CHitEffect::Update(void)
{
	CObject3D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CHitEffect::Draw(void)
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

	//�J�����O�𖳌���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CObject3D_Anim::Draw();

	//�J�����O��L����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

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
CHitEffect* CHitEffect::Create(const D3DXVECTOR3& pos)
{
	// �C���X�^���X����
	CHitEffect* pEffect = new CHitEffect;

	// NULL�`�F�b�N
	if (pEffect == nullptr) { return nullptr; }

	// �ʒu��ݒ�
	pEffect->m_pos = pos;

	// ����������
	pEffect->Init();

	return pEffect;
}
