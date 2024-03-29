//==========================================
//
//  �a���G�t�F�N�g(slash_effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SLASH_EFFECT_H_
#define _SLASH_EFFECT_H_
#include "object3D_Anim.h"

//==========================================
//  �N���X��`
//==========================================
class CSlash_Effect : public CObject3D_Anim
{
public:

	//�����o�֐�
	CSlash_Effect(int nPriority = 6);
	~CSlash_Effect();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�֐�
	static CSlash_Effect* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXCOLOR& col);

private:

};

#endif
