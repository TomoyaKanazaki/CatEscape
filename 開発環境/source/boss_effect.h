//==========================================
//
//  �{�X�̏o���G�t�F�N�g(boss_effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_EFFECT_H_
#define _BOSS_EFFECT_H_
#include "object3D_Anim.h"

//==========================================
//  �N���X��`
//==========================================
class CBossEffect : public CObject3D_Anim
{
public:

	// �����o�֐�
	CBossEffect(int nPriority = 6);
	~CBossEffect();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�ϐ�
	static CBossEffect* Create(const D3DXVECTOR3& pos);

private:

	// �����o�ϐ�
	int m_TexIdx; // �e�N�X�`���C���f�b�N�X

};

#endif
