//==========================================
//
//  �a���G�t�F�N�g(slash.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "slash.h"
#include "manager.h"
#include "renderer.h"
#include "gametime.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "slash_effect.h"
#include "splash.h"
#include "hit_effect.h"
#include "gamemanager.h"
#include "camera.h"
#include "input.h"
#include "camera_game.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 SLASH_SIZE = D3DXVECTOR3(800.0f, 5.0f, 0.0f); // �|���S���T�C�Y
	const float CLEAR_TIME = 4.0f; // 1 / n �b
	const float MIN_COLOR = 0.5f; // �F�̉���
	const D3DXCOLOR EFFECT_COLOR[3] = { D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f) }; // �G�t�F�N�g�J���[
	const D3DXVECTOR3 EFFECT_SCALE = D3DXVECTOR3(0.5f, 10.0f, 0.0f); // �G�t�F�N�g�̃X�P�[��
}

//==========================================
//  �R���X�g���N�^
//==========================================
CSlash::CSlash(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CSlash::~CSlash()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CSlash::Init(void)
{
	// �T�C�Y��ݒ�
	m_size = SLASH_SIZE;

	// �|���S���̍��[�̍��W���Z�o
	m_posLeft.x = m_pos.x + (cosf(m_rot.z) * (m_size.x * 0.5f));
	m_posLeft.y = m_pos.y + (sinf(m_rot.z) * (m_size.x * 0.5f));

	// �|���S���̉E�[�̍��W���Z�o
	m_posRight.x = m_pos.x - (cosf(m_rot.z) * (m_size.x * 0.5f));
	m_posRight.y = m_pos.y - (sinf(m_rot.z) * (m_size.x * 0.5f));

	// �e�N�X�`�����蓖��
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::EFFECT));

	// �F�̐ݒ�
	m_col.r = 0.0f;
	m_col.g = ((float)rand() / (float)RAND_MAX) * (1.0f - MIN_COLOR) + MIN_COLOR;
	m_col.b = ((float)rand() / (float)RAND_MAX);

	// �A�j���[�V������ݒ�
	SetAnim(28, 2, false, TYPE_U);

	// �U������
	Hit();

	// �G�t�F�N�g�̔���
	for (int i = 0; i < 3; ++i)
	{
		CSlash_Effect::Create(m_pos, m_rot, EFFECT_COLOR[i]);
	}
	CSplash::Create(m_pos, m_rot, D3DXVECTOR3(m_size.x, m_size.y * EFFECT_SCALE.y, EFFECT_SCALE.z), m_col);

	// ������
	return CObject3D_Anim::Init();
}

//==========================================
//  �I������
//==========================================
void CSlash::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CSlash::Update(void)
{
	// ���S�ɓ��߂��Ă����ꍇ�I������
	if (m_col.a <= 0.0f)
	{
		Uninit();
		return;
	}

	// �s�����x��������
	m_col.a -= CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat() * 2.0f;

	// �X�V����
	CObject3D_Anim::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CSlash::Draw(void)
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

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�`��
	CObject3D_Anim::Draw();

	//�A���t�@�u�����f�B���O�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

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
CSlash* CSlash::Create(const D3DXVECTOR3 pos, const float rot)
{
	// �C���X�^���X����
	CSlash* pSlash = new CSlash;

	// NULL�`�F�b�N
	if (pSlash == nullptr) { return nullptr; }

	// �l�̐ݒ�
	pSlash->m_pos = pos;
	pSlash->m_rot.z = rot;

	// ����������
	pSlash->Init();

	// �l��Ԃ�
	return pSlash;
}

//==========================================
//  �G�Ƃ̓����蔻��
//==========================================
void CSlash::Hit()
{
	//�����蔻��̐���
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//�擪�̃A�h���X���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//���̃A�h���X��ۑ�
			CObject* pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_ENEMY) //�G�̏ꍇ
			{
				if (pObj->GetObjState() == CObject::NORMAL) // �ʏ��Ԃ̏ꍇ
				{
					// �ڕW�_���擾����
					D3DXVECTOR3 pos = pObj->GetCenterPos();

					if (CGameManager::GetCamera()->OnScreen(pos)) // ��ʓ��̏ꍇ
					{
						// �n�_����I�_�܂ł̃x�N�g�������߂�
						D3DXVECTOR3 vecLine = m_posRight - m_posLeft;

						// �n�_����ڕW�_�܂ł̃x�N�g�������߂�
						D3DXVECTOR3 vecToPos = pos - m_posLeft;

						// �e�x�N�g���̑傫�������߂�
						float lengthLine = sqrtf((vecLine.x * vecLine.x) + (vecLine.y * vecLine.y));
						float lengthToPos = sqrtf((vecToPos.x * vecToPos.x) + (vecToPos.y * vecToPos.y));

						// �}��ϐ�t�����߂�
						float t = (lengthLine * lengthToPos) / (lengthLine * lengthLine);

						// �����̔���
						if (0.0f <= t && t <= 1.0f)
						{
							// �ڕW�_���璼���ɐ��������������̌�_�����߂�
							D3DXVECTOR3 posCross = m_posLeft + (t * vecLine);

							// ��_����ڕW�_�܂ł̃x�N�g�������߂�
							D3DXVECTOR3 vecToCross = pos - posCross;

							// ���苗���̔�r
							if (pObj->GetHitLength() * pObj->GetHitLength() >= (vecToCross.x * vecToCross.x) + (vecToCross.y * vecToCross.y))
							{
								// �������Ă������̉��o�n����
								CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SLICE);
								pObj->SetState(CObject::ATTACKED);
								CHitEffect::Create((posCross + pos) * 0.5f);

								// �o�C�u���[�V�����̐ݒ�
								CManager::GetInstance()->GetJoyPad()->AddVibrationSpeed(USHRT_MAX);
								CManager::GetInstance()->GetJoyPad()->AddVibrationTimer(0.1f);

								// ��ʗh��̐ݒ�
								CGameManager::GetCamera()->AddQuake(D3DXVECTOR3(1.0f, 1.0f, 0.0f), 0.05f);

								// �q�b�g�X�g�b�v
								if (CManager::GetInstance()->GetGameTime()->GetTime() >= 0.0f)
								{
									CManager::GetInstance()->GetGameTime()->SetScaling(0.001f, 0.1f);
								}
								else
								{
									CManager::GetInstance()->GetGameTime()->AddTime(0.1f);
								}
							}
						}
					}
				}
			}

			//���̃A�h���X�ɂ��炷
			pObj = pNext;
		}
	}
}
