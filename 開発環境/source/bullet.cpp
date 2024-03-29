//==========================================
//
//  �e�N���X(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "gamemanager.h"
#include "player.h"
#include "gametime.h"
#include "explosion.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 BULLET_SIZE = D3DXVECTOR3(150.0f, 150.0f, 200.0f); // �T�C�Y
	const float POS_ERROR = 10.0f; // �ڕW�n�_�Ƃ̌덷���e�͈�
	const float MOVE_SPEED = 300.0f; // �e��
	const float HIT_LENGTH = 50.0f; // �����蔻�苗��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CBullet::CBullet(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CBullet::~CBullet()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CBullet::Init(void)
{
	// �T�C�Y��ݒ�
	m_size = BULLET_SIZE;

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::BULLET));

	// �F�̕ύX
	m_col.r = 0.5f;
	m_col.g = 0.0f;

	// �A�j���[�V������ݒ�
	SetAnim(60, 1, true, TYPE_U);

	// �ڕW�n�_��ݒ�
	m_target = CGameManager::GetPlayer()->GetCenterPos();

	return CObject3D_Anim::Init();
}

//==========================================
//  �I������
//==========================================
void CBullet::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CBullet::Update(void)
{
	// �f���^�^�C���̎擾
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// �ړ��ʂ̐ݒ�
	SetMove();

	// �ړ��ʂ̓K�p
	m_pos += m_move;

	// �U������
	Hit();

	CObject3D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CBullet::Draw(void)
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
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);\

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
CBullet* CBullet::Create(const D3DXVECTOR3& pos)
{
	// �C���X�^���X����
	CBullet* pBullet = new CBullet;

	// NULL�`�F�b�N
	if (pBullet == nullptr) { return nullptr; }

	// �ʒu��ݒ�
	pBullet->m_pos = pos;

	// ����������
	pBullet->Init();

	return pBullet;
}

//==========================================
//  �ړ��ʂ̐ݒ�
//==========================================
void CBullet::SetMove()
{
	// �ڕW�ʒu�ƌ��݈ʒu�����ԃx�N�g�����쐬����
	D3DXVECTOR3 vec = m_target - m_pos;

	// �j��
	if (POS_ERROR * POS_ERROR >= vec.x * vec.x + vec.y * vec.y)
	{
		CExplosion::Create(m_pos);
		Uninit();
	}

	// �ړ��ʂ�ڕW�ʒu�Ɍ�����
	vec *= m_fDeltaTime;

	// �ړ��ʂ�K�p
	m_move = vec;
}

//==========================================
//  �����蔻��
//==========================================
void CBullet::Hit()
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

		// ���g���I������
		CExplosion::Create(m_pos);
		Uninit();
	}
}
