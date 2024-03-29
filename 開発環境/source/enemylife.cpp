//==========================================
//
//  �̗͕\��(enemylife.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemylife.h"
#include "manager.h"
#include "gamemanager.h"
#include "enemymanager.h"
#include "manager.h"
#include "enemy.h"
#include "texture.h"
#include "renderer.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 LIFE_SIZE = D3DXVECTOR3(100.0f, 80.0f, 0.0f);
	const D3DXVECTOR3 LIFE_RIGHT_POS = D3DXVECTOR3(FLOAT_SCREEN_WIDTH - 30.0f, 50.0f, 0.0f);
	const float LIFE_SCALE = 20.0f; // ���g���\���̗̗͂�
	const float SAB_SCALE = 0.1f; // �T�C�Y�̌����{��
}

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
int CEnemyLife::m_nNum = 0; // �̗�

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyLife::CEnemyLife(int nPriority) : CObject2D(nPriority),
m_nIdx(m_nNum)
{
	++m_nNum;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyLife::~CEnemyLife()
{
	--m_nNum;
}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyLife::Init(void)
{
	// �T�C�Y��ݒ�
	m_size = LIFE_SIZE;

	// �ʒu��ݒ�
	m_pos = LIFE_RIGHT_POS;
	m_pos.x -= LIFE_SIZE.x * m_nIdx;

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::FLAME));

	return CObject2D::Init();
}

//==========================================
//  �I������
//==========================================
void CEnemyLife::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyLife::Update(void)
{
	// 0�����������폜
	if (m_size.x <= 0.0f)
	{
		Uninit();
		return;
	}

	// �傫���̍X�V
	ClacSize();

	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemyLife::Draw(void)
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
CEnemyLife* CEnemyLife::Create()
{
	// �C���X�^���X����
	CEnemyLife* pLife = new CEnemyLife;

	// ����������
	pLife->Init();

	return pLife;
}

//==========================================
//  �傫���̌v�Z����
//==========================================
void CEnemyLife::ClacSize()
{
	// �{�X�̃��C�t���擾
	float fLife = CGameManager::GetEnemy()->GetBoss()->GetLife();

	// �{�X�̗̑͂��玩�g�̖ڕW�T�C�Y���Z�o����
	fLife -= LIFE_SCALE * m_nIdx;
	if (fLife > LIFE_SCALE)
	{
		fLife = LIFE_SCALE;
	}
	fLife /= LIFE_SCALE;

	// �ڕW�T�C�Y��K�p����
	m_sizeDest = LIFE_SIZE * fLife;

	// �ڕW�T�C�Y�ƌ��݂̃T�C�Y�̍������Z�o
	D3DXVECTOR3 diff = m_sizeDest - m_size;

	// ���� * �{�����T�C�Y������������
	m_size += diff * SAB_SCALE;
}
