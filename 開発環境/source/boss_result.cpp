//==========================================
//
//  �{�X�N���X(boss.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss_result.h"
#include "model.h"
#include "motion.h"
#include "orbit.h"
#include "resultmanager.h"
#include "camera.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float POSR_DISTANCE = 100.0f; // �J�����̒����_����̋���
}

//==========================================
//  �R���X�g���N�^
//==========================================
CBossResult::CBossResult(int nPriority)
{
	m_pOrbit[0] = m_pOrbit[1] = nullptr;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CBossResult::~CBossResult()
{
}

//==========================================
//  ����������
//==========================================
HRESULT CBossResult::Init(void)
{
	// �^�C�v�̐ݒ�
	SetType(TYPE_ENEMY);

	// �K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::ENEMY_BOSS);

	// ������
	HRESULT hr = CObject_Char::Init();

	// �Z�b�g�A�b�v
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::BOSS_POP);

	// ���ɋO�Ղ�t����
	if (m_pOrbit[0] == nullptr)
	{
		m_pOrbit[0] = COrbit::Create(m_ppModel[4], D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, -115.0f), 10);
		m_pOrbit[0]->SwitchDraw(false);
	}
	if (m_pOrbit[1] == nullptr)
	{
		m_pOrbit[1] = COrbit::Create(m_ppModel[5], D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, -115.0f), 10);
		m_pOrbit[1]->SwitchDraw(false);
	}

	// ���[�V������ݒ�
	m_pMotion->Set(CMotion::BOSS_ATTACK);

	return hr;
}

//==========================================
//  �I������
//==========================================
void CBossResult::Uninit(void)
{
	// �O�Ղ̏I��
	for (int i = 0; i < 2; ++i)
	{
		if (m_pOrbit[i] != nullptr)
		{
			m_pOrbit[i]->Uninit();
			m_pOrbit[i] = nullptr;
		}
	}

	CEnemy::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBossResult::Update(void)
{
	// �ʒu��ύX
	m_pos = CResultManager::GetCamera()->GetPosR();
	m_pos.x += POSR_DISTANCE;

	// �O��
	for (int i = 0; i < 2; ++i)
	{
		if (m_pOrbit[i] != nullptr)
		{
			m_pOrbit[i]->SwitchDraw(true);
		}
	}

	// ��������
	m_rot.y = D3DX_PI * 0.5f;

	CEnemy::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBossResult::Draw(void)
{
	CEnemy::Draw();
}
