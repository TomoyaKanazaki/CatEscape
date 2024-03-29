//==========================================
//
//  �^�C�g���V�[���̃J����(camera_title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_title.h"
#include "player.h"
#include "manager.h"
#include "input.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 POS_V = D3DXVECTOR3(0.0f, 100.0f, -350.0f); // ���_�ʒu
	const D3DXVECTOR3 POS_R = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // �����_�ʒu
}

//==========================================
//  �R���X�g���N�^
//==========================================
CCameraTitle::CCameraTitle()
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CCameraTitle::~CCameraTitle()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCameraTitle::Init(void)
{
	// �ʒu��ݒ�
	m_posV = POS_V;
	m_posR = POS_R;

	return CCamera::Init();
}

//==========================================
//  �X�V����
//==========================================
void CCameraTitle::Update(void)
{
	CCamera::Update();
}
