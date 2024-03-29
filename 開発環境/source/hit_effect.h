//==========================================
//
//  �q�b�g���̃G�t�F�N�g(hit_effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _HIT_EFFECT_H_
#define _HIT_EFFECT_H_
#include "object3D_Anim.h"

//==========================================
//  �N���X��`
//==========================================
class CHitEffect : public CObject3D_Anim
{
public:

	// �����o�֐�
	CHitEffect(int nPriority = 6);
	~CHitEffect();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�֐�
	static CHitEffect* Create(const D3DXVECTOR3& pos);

private:

};

#endif
