//==========================================
//
//  �{�X�o���G�t�F�N�g(boss_effect.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss_effect.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 EFFECT_SIZE = D3DXVECTOR3(500.0f, 500.0f, 500.0f); // �G�t�F�N�g�̑傫��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CBossEffect::CBossEffect(int nPriority) : CObject3D_Anim(nPriority),
m_TexIdx(0)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CBossEffect::~CBossEffect()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBossEffect::Init(void)
{
	// �T�C�Y��ݒ�
	m_size = EFFECT_SIZE;

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::BOSS1));

	// �A�j���[�V������ݒ�
	SetAnim(8, 3, false, TYPE_U);

	return CObject3D_Anim::Init();
}

//==========================================
//  �I������
//==========================================
void CBossEffect::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBossEffect::Update(void)
{
	CObject3D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBossEffect::Draw(void)
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

	CObject3D_Anim::Draw();

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
CBossEffect* CBossEffect::Create(const D3DXVECTOR3& pos)
{
	// �C���X�^���X����
	CBossEffect* pEffect = new CBossEffect;

	// NULL�`�F�b�N
	if (pEffect == nullptr) { return nullptr; }

	// �l��ݒ�
	pEffect->m_pos = pos;

	// ����������
	pEffect->Init();

	return pEffect;
}
