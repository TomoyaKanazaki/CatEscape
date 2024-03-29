//==========================================
//
//  �^�C�g���V�[���̃J����(camera_result.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_result.h"
#include "player.h"
#include "manager.h"
#include "input.h"
#include "resultmanager.h"
#include "running.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 POS_V = D3DXVECTOR3(0.0f, 0.0f, -350.0f); // ���_�ʒu
	const D3DXVECTOR3 POS_R = D3DXVECTOR3(0.0f, 100.0f, 0.0f); // �����_�ʒu
	const float PLAYER_DISTANCE = 150.0f; // �v���C���[�̌���������
}

//==========================================
//  �R���X�g���N�^
//==========================================
CCameraResult::CCameraResult()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CCameraResult::~CCameraResult()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCameraResult::Init(void)
{
	return CCamera::Init();
}

//==========================================
//  �X�V����
//==========================================
void CCameraResult::Update(void)
{
	Rotate();
	CCamera::Update();
}

//==========================================
//  ��]
//==========================================
void CCameraResult::Rotate()
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 Pos = m_posR; //���݂̈ʒu
	D3DXVECTOR3 Dest = CResultManager::GetPlayer()->GetPos(); //�ڕW�̈ʒu
	D3DXVECTOR3 Diff = {}; //�ڕW�ƌ��݂̈ʒu�̍�
	D3DXVECTOR3 rot = CResultManager::GetPlayer()->GetRot(); //�v���C���[�̕���
	float fDistance = -sinf(rot.y) * PLAYER_DISTANCE;

	//�����𒲐�
	Dest.x -= fDistance;

	//�ړ��␳
	Diff = Dest - Pos;	//�ڕW�܂ł̈ړ������̍���

	//�K�p
	m_posR += Diff * 1.0f + POS_R;

	//���_���X�V
	m_posV = m_posR + D3DXVECTOR3(0.0f, POS_V.y, POS_V.z);
}
