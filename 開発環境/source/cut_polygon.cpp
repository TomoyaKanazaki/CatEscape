//==========================================
//
//  �a��ꂽ�|���S��(cut_polygon.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "cut_polygon.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"

//==========================================
//  �R���X�g���N�^
//==========================================
CCutPolygon::CCutPolygon(int nPriority) : CObject3D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nPattern = 1;
}

//==========================================
//  �f�X�g���N�^
//==========================================
CCutPolygon::~CCutPolygon()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCutPolygon::Init(void)
{
	//������
	HRESULT hr = CObject3D::Init();

	//X���W�̐ݒ�
	float fPattern = 1.0f / (float)m_nPattern;

	//�e�N�X�`�����W�̐ݒ�
	if (m_move.y > 0.0f)
	{
		SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(fPattern, 0.5f));
	}
	if (m_move.y < 0.0f)
	{
		SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(fPattern, 1.0f));
	}

	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SLASH);

	return hr;
}

//==========================================
//  �I������
//==========================================
void CCutPolygon::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CCutPolygon::Update(void)
{
	//�ړ�
	m_pos += m_move;

	//�����ɂ��ړ��̒�~
	//m_move.x += (0.0f - m_move.x) * 0.1f;

	//�����x��������
	D3DXCOLOR col = GetCol();
	col.a += (0.0f - col.a) * 0.1f;
	SetCol(col);

	//�����x0�ŏ���
	if (col.a <= 0.0f)
	{
		Uninit();
		return;
	}

	CObject3D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CCutPolygon::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CObject3D::Draw();

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  ��������
//==========================================
CCutPolygon* CCutPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, LPDIRECT3DTEXTURE9 tex, int nPattern)
{
	//�C���X�^���X����
	CCutPolygon* pCut = new CCutPolygon;

	//�l��ݒ�
	pCut->m_pos = pos;
	pCut->m_size = size;
	pCut->m_move = move;
	pCut->m_nPattern = nPattern;

	//����������
	pCut->Init();

	//�e�N�X�`�����蓖��
	pCut->BindTexture(tex);

	return pCut;
}
