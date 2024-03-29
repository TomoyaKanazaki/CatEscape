//==========================================
//
//  ���S(result.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "scenemanager.h"
#include "resultmanager.h"
#include "camera.h"
#include "debugproc.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 RESULT_SIZE = D3DXVECTOR3(440.0f, 90.0f, 0.0f); // �|���S���̑傫��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CResult::CResult(int nPriority)
{
}

//==========================================
//  �f�X�g���N�^
//==========================================
CResult::~CResult()
{
}

//==========================================
//  ����������
//==========================================
HRESULT CResult::Init(void)
{
	// �e�N�X�`�����蓖��
	if (CSceneManager::GetClear())
	{
		BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::CLEAR));
	}
	else
	{
		BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::OVER));
	}

	// �T�C�Y�̐ݒ�
	m_size = RESULT_SIZE;

	// �ʒu��ݒ�
	m_pos = CResultManager::GetCamera()->GetPosR();

	// �r���{�[�h�̐ݒ�
	SwitchBillboard(true);

	return CObject3D::Init();
}

//==========================================
//  �I������
//==========================================
void CResult::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CResult::Update(void)
{
	// �ʒu��ݒ�
	m_pos = CResultManager::GetCamera()->GetPosR();

	// �f�o�b�O�\��
	DebugProc::Print("\n�|���S���ʒu : %f, %f\n\n", m_pos.x, m_pos.y);

	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CResult::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CObject3D::Draw();

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//==========================================
//  ��������
//==========================================
CResult* CResult::Create(void)
{
	// �C���X�^���X����
	CResult* pResult = new CResult;

	// ����������
	pResult->Init();

	return pResult;
}
