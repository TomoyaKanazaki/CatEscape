//==========================================
//
//  �I�u�W�F�N�g�L�����N�^�[(object_char.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object_char.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "model.h"
#include "motion.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CObject_Char::CObject_Char(int nPriority) : CObject(nPriority),
m_bChangeCol(false),
m_HitLenght(0.0f)
{
	m_ppModel = NULL;
	m_pLayer = NULL;
	m_pMotion = NULL;
	m_mtxWorld = {};
}

//==========================================
//  �f�X�g���N�^
//==========================================
CObject_Char::~CObject_Char()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CObject_Char::Init(void)
{
	//���f���p�̃������̊m��
	if (m_ppModel == NULL)
	{
		m_ppModel = new CModel* [m_pLayer->nNumModel];
	}

	//�K�v�ȃ��f���𐶐�
	for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
	{
		//��ɂ���
		m_ppModel[nCnt] = NULL;

		//�e�����݂��Ȃ��ꍇ
		if (m_pLayer->pParentID[nCnt] == -1)
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt]);
		}
		else
		{
			m_ppModel[nCnt] = CModel::Create(m_pLayer->pPos[nCnt], m_pLayer->pRot[nCnt], m_pLayer->pModelID[nCnt], m_ppModel[m_pLayer->pParentID[nCnt]]);
		}
	}

	//���[�V�������̐���
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CObject_Char::Uninit(void)
{
	//���f���̃|�C���^��j��
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Uninit();
				m_ppModel[nCnt] = NULL;
			}
		}
		delete[] m_ppModel;
		m_ppModel = NULL;
	}

	//���[�V�����̃|�C���^��j��
	if (m_pMotion != NULL)
	{
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CObject_Char::Update(void)
{
	// �F�̐ݒ�
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->SetCol(m_col);
				m_ppModel[nCnt]->ChangeCol(m_bChangeCol);
			}
		}
	}

	//���[�V�������X�V����
	if (m_pMotion != NULL)
	{
		m_pMotion->Update();
	}
}

//==========================================
//  �`�揈��
//==========================================
void CObject_Char::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetInstance()->GetRenderer()->GetDevice();

	//���[�J���ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_bWhiteOut)
	{
		//�A���t�@�e�X�g�̗L����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// �e���f����`�悷��
	if (m_ppModel != NULL)
	{
		for (int nCnt = 0; nCnt < m_pLayer->nNumModel; nCnt++)
		{
			if (m_ppModel[nCnt] != NULL)
			{
				m_ppModel[nCnt]->Draw();
			}
		}
	}

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
//  ���苗���̌v�Z
//==========================================
void CObject_Char::CalcHitLength(const D3DXVECTOR3& size)
{
	m_HitLenght = sqrtf(size.x * size.x + size.y + size.y);
}
