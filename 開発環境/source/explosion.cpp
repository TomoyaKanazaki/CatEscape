//==========================================
//
//  �e�N���X(explosion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "gamemanager.h"
#include "player.h"
#include "gametime.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 EXPLOSION_SIZE = D3DXVECTOR3(150.0f, 150.0f, 200.0f); // �T�C�Y
	const float MOVE_SPEED = 300.0f; // �e��
	const float HIT_LENGTH = 50.0f; // �����蔻�苗��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CExplosion::CExplosion(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CExplosion::~CExplosion()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CExplosion::Init(void)
{
	// �T�C�Y��ݒ�
	m_size = EXPLOSION_SIZE;

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::EXPLOSION));

	// �A�j���[�V������ݒ�
	SetAnim(10, 2, false, TYPE_U);

	return CObject3D_Anim::Init();
}

//==========================================
//  �I������
//==========================================
void CExplosion::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CExplosion::Update(void)
{
	// �����蔻��
	Hit();

	CObject3D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CExplosion::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	CObject3D_Anim::Draw();

	//�A���t�@�e�X�g�̖�����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  ��������
//==========================================
CExplosion* CExplosion::Create(const D3DXVECTOR3& pos)
{
	// �C���X�^���X����
	CExplosion* pExplosion = new CExplosion;

	// NULL�`�F�b�N
	if (pExplosion == nullptr) { return nullptr; }

	// �ʒu��ݒ�
	pExplosion->m_pos = pos;

	// ����������
	pExplosion->Init();

	return pExplosion;
}

//==========================================
//  �����蔻��
//==========================================
void CExplosion::Hit()
{
	// �v���C���[�̈ʒu���擾
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetCenterPos();

	// �v���C���[�܂ł̃x�N�g�����Z�o
	D3DXVECTOR3 vec = pos - m_pos;

	// �U���͈͓��Ȃ�q�b�g����
	if (vec.x * vec.x + vec.y * vec.y < HIT_LENGTH * HIT_LENGTH)
	{
		// �q�b�g���̏������Ă�
		CGameManager::GetPlayer()->Attacked();
	}
}
