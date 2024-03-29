//==========================================
//
//  ヒット時のエフェクト(hit_effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _HIT_EFFECT_H_
#define _HIT_EFFECT_H_
#include "object3D_Anim.h"

//==========================================
//  クラス定義
//==========================================
class CHitEffect : public CObject3D_Anim
{
public:

	// メンバ関数
	CHitEffect(int nPriority = 6);
	~CHitEffect();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CHitEffect* Create(const D3DXVECTOR3& pos);

private:

};

#endif
