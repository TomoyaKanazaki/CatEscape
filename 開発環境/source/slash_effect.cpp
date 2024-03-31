//==========================================
//
//  �a���G�t�F�N�g(slash_effect.cpp)
//  Author : Chaba
//
//==========================================
#include "slash_effect.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "gametime.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const int NUM_TEXTURE = 1; // �a���G�t�F�N�g�̃e�N�X�`����
	const int MIN_SIZE = 100; // �傫���̉����l
	const int MAX_SIZE = 200; // �傫���̏���l
	const float CLEAR_TIME = 5.0f; // 1 / n �b�ŏ�����
	const float ALPHA = 0.7f; // �����x
}

//==========================================
//  �R���X�g���N�^
//==========================================
CSlash_Effect::CSlash_Effect(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CSlash_Effect::~CSlash_Effect()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CSlash_Effect::Init(void)
{
	m_size = D3DXVECTOR3(MAX_SIZE, MAX_SIZE, MAX_SIZE);

	D3DXVECTOR3 rot;
	rot.x = (float)(rand() % 629 - 314) * 0.01f;
	rot.y = (float)(rand() % 629 - 314) * 0.01f;
	rot.z = (float)(rand() % 629 - 314) * 0.01f;
	m_rot.x = rot.x;
	m_rot.y = rot.y;
	m_rot.z = rot.z;

	// �����x�ݒ�
	m_col.a = ALPHA;

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::SLASH));

	// �A�j���[�V������ݒ�
	SetAnim(12, 2, false, TYPE_U);

	// ������
	return CObject3D_Anim::Init();
}

//==========================================
//  �I������
//==========================================
void CSlash_Effect::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CSlash_Effect::Update(void)
{
	// �X�V����
	CObject3D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CSlash_Effect::Draw(void)
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
CSlash_Effect* CSlash_Effect::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXCOLOR& col)
{
	// �C���X�^���X����
	CSlash_Effect* pSlash = new CSlash_Effect;

	// NULL�`�F�b�N
	if (pSlash == nullptr) { return nullptr; }

	// �l�̐ݒ�
	pSlash->m_pos = pos;
	pSlash->m_rot = rot;
	pSlash->m_col = col;

	// ����������
	pSlash->Init();

	// �l��Ԃ�
	return pSlash;
}
