//==========================================
//
//  連撃エフェクト(rush_effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RUSH_EFFECT_H_
#define _RUSH_EFFECT_H_
#include "object2D_Anim.h"

//==========================================
//  クラス定義
//==========================================
class CRush : public CObject2D_Anim
{
public:

	// メンバ関数
	CRush(int nPriority = 7);
	~CRush();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// 静的メンバ関数
	static CRush* Create();

private:

};

#endif
