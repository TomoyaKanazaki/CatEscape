//==========================================
//
//  �̗͕\���̊Ǘ��N���X(enemylifemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemylifemanager.h"
#include "manager.h"
#include "gamemanager.h"
#include "player.h"
#include "texture.h"
#include "enemylife.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 FRAME_SIZE = D3DXVECTOR3(600.0f, 100.0f, 0.0f);
	const D3DXVECTOR3 FRAME_POS = D3DXVECTOR3(FLOAT_SCREEN_WIDTH - 300.0f, 50.0f, 0.0f);
}

//==========================================
//  �R���X�g���N�^
//==========================================
CEnemyLifeManager::CEnemyLifeManager(int nPriority) : CObject2D(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CEnemyLifeManager::~CEnemyLifeManager()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CEnemyLifeManager::Init(void)
{
	// �T�C�Y��ݒ�
	m_size = FRAME_SIZE;

	// �ʒu��ݒ�
	m_pos = FRAME_POS;

	// ������ݒ�
	m_rot.z = D3DX_PI;

	// ������
	HRESULT hr = CObject2D::Init();

	// �F��ݒ�
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ENEMY_FRAME));

	// �̗͕\��
	for (int i = 0; i < 5; ++i)
	{
		CEnemyLife::Create();
	}

	return hr;
}

//==========================================
//  �I������
//==========================================
void CEnemyLifeManager::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CEnemyLifeManager::Update(void)
{
	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CEnemyLifeManager::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CEnemyLifeManager* CEnemyLifeManager::Create()
{
	// �C���X�^���X����
	CEnemyLifeManager* pLife = new CEnemyLifeManager;

	// ����������
	pLife->Init();

	return pLife;
}
