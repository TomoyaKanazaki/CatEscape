//==========================================
//
//  �̗͕\��(bosslife.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bosslife.h"
#include "manager.h"
#include "gamemanager.h"
#include "enemymanager.h"
#include "manager.h"
#include "enemy.h"
#include "texture.h"
#include "renderer.h"
#include "input.h"
#include "rush_effect.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 LIFE_SIZE = D3DXVECTOR3(500.0f, 400.0f, 0.0f);
	const D3DXVECTOR3 LIFE_POS = D3DXVECTOR3(FLOAT_SCREEN_WIDTH - LIFE_SIZE.x * 0.5f, FLOAT_SCREEN_HEIGHT - LIFE_SIZE.y * 0.5f, 0.0f);
	const float MAX_LIFE = 30.0f; // ���g���\���̗̗͂�
	const float SAB_SCALE = 0.1f; // �T�C�Y�̌����{��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CBossLife::CBossLife(int nPriority) : CObject2D(nPriority),
m_fLife(30.0f),
m_bDead(false)
{
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBossLife::~CBossLife()
{
}

//==========================================
//  ����������
//==========================================
HRESULT CBossLife::Init(void)
{
	// �T�C�Y��ݒ�
	m_size = LIFE_SIZE;

	// �ʒu��ݒ�
	m_pos = LIFE_POS;

	// ����������
	HRESULT hr = CObject2D::Init();

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::FLAME));

	return hr;
}

//==========================================
//  �I������
//==========================================
void CBossLife::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBossLife::Update(void)
{
	// 0�����������t���O
	if (m_fLife <= 0.0f)
	{
		m_bDead = true;
		return;
	}

	// �_���[�W�󂯂�
	if (CManager::GetInstance()->GetJoyPad()->GetStickTriggerR(CJoyPad::STICK_ALL))
	{
		m_fLife -= 1.0f;
	}

	// ���o���Ă�
	if (m_fLife <= 0.0f)
	{
		CRush::Create();
	}

	// �傫���̍X�V
	ClacSize();

	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBossLife::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`��
	CObject2D::Draw();

	//�A���t�@�u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  ��������
//==========================================
CBossLife* CBossLife::Create()
{
	// �C���X�^���X����
	CBossLife* pLife = new CBossLife;

	// ����������
	pLife->Init();

	return pLife;
}

//==========================================
//  �傫���̌v�Z����
//==========================================
void CBossLife::ClacSize()
{
	// �ڕW�T�C�Y��K�p����
	m_sizeDest = LIFE_SIZE * (m_fLife / MAX_LIFE);

	// �ڕW�T�C�Y�ƌ��݂̃T�C�Y�̍������Z�o
	D3DXVECTOR3 diff = m_sizeDest - m_size;

	// ���� * �{�����T�C�Y������������
	m_size += diff * SAB_SCALE;
}
