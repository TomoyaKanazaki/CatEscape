//==========================================
//
//  �a��ꂽ�|���S��(cut.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "cut.h"
#include "cut_polygon.h"

//==========================================
//  �ÓI�����o�ϐ��錾
//==========================================
const float CCut::m_fSpeed = 3.0f;

//==========================================
//  �R���X�g���N�^
//==========================================
CCut::CCut()
{
	tex = nullptr;
	m_nPattern = 1;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CCut::~CCut()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCut::Init(void)
{
	//��������|���S���̈ړ�����������
	D3DXVECTOR3 move;
	while (1)
	{
		//��������
		move = D3DXVECTOR3((float)rand(), (float)rand(), 0.0f);

		//���K��
		D3DXVec3Normalize(&move, &move);

		if (move.y != 0.0f)
		{
			break;
		}
	}

	//����������W������
	D3DXVECTOR3 posUp = m_pos, posDawn = m_pos;
	posUp.y += m_size.y * 0.25f;
	posDawn.y -= m_size.y * 0.25f;

	//��������|���S���̃T�C�Y
	D3DXVECTOR3 size = D3DXVECTOR3(m_size.x, m_size.y * 0.5f, m_size.z);

	//�|���S���𐶐�����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (move.y > 0.0f)
		{
			CCutPolygon::Create(posUp, size, move, tex, m_nPattern);
		}
		if (move.y < 0.0f)
		{
			CCutPolygon::Create(posDawn, size, move, tex, m_nPattern);
		}
		move *= -1.0f;
	}

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CCut::Uninit(void)
{
	//�������g�̔j��
	Release();
}

//==========================================
//  �X�V����
//==========================================
void CCut::Update(void)
{
	Uninit();
}

//==========================================
//  �`�揈��
//==========================================
void CCut::Draw(void)
{

}

//==========================================
//  ��������
//==========================================
CCut* CCut::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex, int nPattern)
{
	//�C���X�^���X����
	CCut* pCut = new CCut;

	//�l��ݒ�
	pCut->m_pos = pos;
	pCut->m_size = size;
	pCut->tex = tex;
	pCut->m_nPattern = nPattern;

	//����������
	pCut->Init();

	return pCut;
}
