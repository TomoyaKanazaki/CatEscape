//==========================================
//
//  �J�����N���X(camera.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "debugproc.h"
#include "gamemanager.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_diff = D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);
	m_fFov = DEFAULT_FAV;
	m_bDebug = false;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CCamera::~CCamera()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCamera::Init(void)
{
	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CCamera::Uninit(void)
{

}

//==========================================
//  �X�V����
//==========================================
void CCamera::Update(void)
{
	DebugProc::Print("���_ : ( %f, %f, %f )\n", m_posV.x, m_posV.y, m_posV.z);
	DebugProc::Print("�����_ : ( %f, %f, %f )\n", m_posR.x, m_posR.y, m_posR.z);
}

//==========================================
//  �ݒ菈��
//==========================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬

	D3DXMatrixPerspectiveFovLH
	(
		&m_mtxProjection,
		D3DXToRadian(m_fFov),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		50000.0f
	);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X���v�Z
	CreateViewMatrix();

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//==========================================
//  �r���[�}�g���b�N�X�̐���
//==========================================
D3DXMATRIX CCamera::CreateViewMatrix(void)
{
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH
	(
		&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU
	);

	return m_mtxView;
}

//==========================================
//  ��l�̎��_�̑���
//==========================================
void CCamera::FirstPerson(void)
{
	//���_�̒l���X�V
	m_rot.x += CManager::GetInstance()->GetInstance()->GetMouse()->GetMouseMove().x;
	m_rot.z += CManager::GetInstance()->GetInstance()->GetMouse()->GetMouseMove().y;

	//�p�x�̕␳
	if (m_rot.z > MAX_ROT)
	{
		m_rot.z = MAX_ROT;
	}
	if (m_rot.z < MIN_ROT)
	{
		m_rot.z = MIN_ROT;
	}
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	//�p�x���X�V
	m_posR.x = m_posV.x + (sinf(m_rot.z) * cosf(m_rot.x)) * -CAMERA_DISTANCE;
	m_posR.y = m_posV.y + cosf(m_rot.z) * -CAMERA_DISTANCE;
	m_posR.z = m_posV.z - (sinf(m_rot.z) * sinf(m_rot.x)) * -CAMERA_DISTANCE;
}

//==========================================
//  �O�l�̎��_�̑���
//==========================================
void CCamera::ThirdPerson(void)
{
	//�����_���X�V
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//���_�̒l���X�V
	m_rot.y += CManager::GetInstance()->GetInstance()->GetMouse()->GetMouseMove().x;

	//�p�x�̕␳
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	//���_���X�V
	m_posV.x = posPlayer.x + (sinf(m_rot.y) * -CAMERA_DISTANCE);
	m_posV.y = posPlayer.y + R_HEIGHT;
	m_posV.z = posPlayer.z + (cosf(m_rot.y) * -CAMERA_DISTANCE);

	//�����_���X�V
	m_posR.x = posPlayer.x - (sinf(m_rot.y) * -CAMERA_DISTANCE);
	m_posR.y = posPlayer.y;
	m_posR.z = posPlayer.z - (cosf(m_rot.y) * -CAMERA_DISTANCE);
}

//==========================================
//  �ړ�
//==========================================
void CCamera::Move(void)
{
	//�v���C���[�̍��W���擾
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//�v���C���[�ɃJ������Ǐ]������
	m_posV = pos;
	m_posR = pos;

	//�v���C���[����J�����𗣂�
	m_posV += m_diff;
	m_posR -= m_diff;
	m_posR.y = pos.y;
}

//==========================================
//  �X�N���[�����̔���
//==========================================
bool CCamera::OnScreen(const D3DXVECTOR3 pos) const
{
	// �Ԃ�l�p�̕ϐ�
	bool bIn = false;

	// �X�N���[�����W�̎擾
	D3DXVECTOR3 screenPos = WorldToScreen(pos);

	// ����
	if (screenPos.x >= 0.0f && screenPos.x <= SCREEN_WIDTH &&
		screenPos.y >= 0.0f && screenPos.y <= SCREEN_HEIGHT &&
		screenPos.z < 1.0f)
	{
		bIn = true;
	}

	// �Ԃ�
	return bIn;
}

//==========================================
//  ���[���h���W���X�N���[�����W�ɕϊ�
//==========================================
D3DXVECTOR3 CCamera::WorldToScreen(const D3DXVECTOR3& posWorld) const
{
	//�r���[�|�[�g�̐ݒ�
	D3DVIEWPORT9 vp = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f };

	//�v�Z�p�ϐ��錾
	D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�X�N���[�����W���Z�o
	D3DXVECTOR3 screenPos;
	D3DXVec3Project
	(
		&screenPos,
		&posWorld,
		&vp,
		&m_mtxProjection,
		&m_mtxView,
		&mtxWorld
	);

	// �X�N���[�����W
	return screenPos;
}

//==========================================
//  �X�N���[�����W�����[���h���W�ɕϊ�
//==========================================
//D3DXVECTOR3 CCamera::ScreenToWorld(const D3DXVECTOR3& posScreen) const
//{
//	// �ϐ��錾
//	D3DXVECTOR3 posWorld; // ���[���h���W
//	float fZ;  // �ˉe��Ԃł�Z�l�i0�`1�j
//	D3DXMATRIX mtxViewInv; // �r���[�}�g���b�N�X�̋t
//	D3DXMATRIX mtxProjectionInv; // �v���W�F�N�V�����}�g���b�N�X�̋t
//	D3DXMATRIX VP;
//	D3DXMATRIX InvViewport;
//	D3DXMatrixInverse(&mtxViewInv, NULL, &m_mtxView);
//	D3DXMatrixInverse(&mtxProjectionInv, NULL, &m_mtxProjection);
//	D3DXMatrixIdentity(&VP);
//	VP._11 = SCREEN_WIDTH * 0.5f;
//	VP._22 = -SCREEN_HEIGHT * 0.5f;
//	VP._41 = SCREEN_WIDTH * 0.5f;
//	VP._42 = SCREEN_HEIGHT * 0.5f;
//	D3DXMatrixInverse(&InvViewport, NULL, &VP);
//
//	// �t�ϊ�
//	D3DXMATRIX tmp = InvViewport * mtxProjectionInv * mtxViewInv;
//	D3DXVec3TransformCoord(&posWorld, &D3DXVECTOR3(posScreen.x, posScreen.y, fZ), &tmp);
//
//	return posWorld;
//}
