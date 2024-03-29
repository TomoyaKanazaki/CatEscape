//==========================================
//
//  �l�`�N���X(running.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "running.h"
#include "motion.h"
#include "scenemanager.h"
#include "manager.h"
#include "gametime.h"
#include "sound.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 LEFT_POS = D3DXVECTOR3(-2400.0f, 0.0f, 0.0f); // ���[
	const D3DXVECTOR3 RIGHT_POS = D3DXVECTOR3(2400.0f, 0.0f, 0.0f); // �E�[
	const float PLAYER_SPEED = 250.0f; // �v���C���[�̈ړ����x
}

//==========================================
//  �R���X�g���N�^
//==========================================
CRunning::CRunning(int nPriority) : CObject_Char(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CRunning::~CRunning()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CRunning::Init(void)
{
	//�^�C�v�̐ݒ�
	SetType(TYPE_PLAYER);

	//�K�w�\�����𐶐�
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	//����������
	HRESULT hr = CObject_Char::Init();

	//���[�V�������Ƀ��f����n��
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_WAIT);
	m_pMotion->Set(CMotion::PLAYER_WALK);

	// �ړ��p����ݒ�
	if (CSceneManager::GetClear())
	{
		// �������͍��X�^�[�g
		m_pos = LEFT_POS;
		m_move = D3DXVECTOR3(PLAYER_SPEED, 0.0f, 0.0f);
	}
	else
	{
		// �s�k���͉E�X�^�[�g
		m_pos = RIGHT_POS;
		m_move = D3DXVECTOR3(-PLAYER_SPEED, 0.0f, 0.0f);
	}

	return hr;
}

//==========================================
//  �I������
//==========================================
void CRunning::Uninit(void)
{
	CObject_Char::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CRunning::Update(void)
{
	// �ړ��ʂ����Z
	m_pos += m_move * CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// ����
	Rotate();

	// �[�ʒu�𒴂�����J�ڂ���
	if (m_pos.x < LEFT_POS.x || m_pos.x > RIGHT_POS.x)
	{
		CManager::GetInstance()->GetInstance()->GetSceneManager()->SetNext(CSceneManager::TITLE);
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_END);
	}

	CObject_Char::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CRunning::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  �ړ�����
//==========================================
void CRunning::Dash(void)
{
	//�ʒu��ۑ�
	D3DXVECTOR3 pos = m_pos;
	m_pos *= -1.0f;
}

//==========================================
//  ��������
//==========================================
CRunning* CRunning::Create()
{
	//�C���X�^���X����
	CRunning* pDoll = new CRunning;

	//����������
	pDoll->Init();

	return pDoll;
}

//==========================================
//  �����]��
//==========================================
void CRunning::Rotate()
{
	//���[�J���ϐ��錾
	float fRotMove = m_rot.y; //���݂̊p�x
	float fRotDest = 0.0f; //�ڕW�̊p�x
	float fRotDiff = 0.0f; //�ڕW�ƌ��݂̊p�x�̍�

	//�E�ɐi�ގ��͉E������
	if (m_move.x > 0.0f)
	{
		fRotDest = -D3DX_PI * 0.5f;
	}

	//���ɐi�ނƂ��͍�������
	if (m_move.x < 0.0f)
	{
		fRotDest = D3DX_PI * 0.5f;
	}

	//�ړ��␳
	fRotDiff = fRotDest - fRotMove;	//�ڕW�܂ł̈ړ������̍���

	//�p�x�̕␳
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff += (-D3DX_PI * 2);
	}
	else if (fRotDiff <= -D3DX_PI)
	{
		fRotDiff += (D3DX_PI * 2);
	}

	//�����]��
	m_rot.y += fRotDiff * 0.2f;

	//�p�x�̕␳
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += (-D3DX_PI * 2);
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += (D3DX_PI * 2);
	}
}
