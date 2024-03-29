//==========================================
//
//  �A���G�t�F�N�g(rush_effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RUSH_EFFECT_H_
#define _RUSH_EFFECT_H_
#include "object2D_Anim.h"

//==========================================
//  �N���X��`
//==========================================
class CRush : public CObject2D_Anim
{
public:

	// �����o�֐�
	CRush(int nPriority = 7);
	~CRush();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// �ÓI�����o�֐�
	static CRush* Create();

private:

};

#endif
