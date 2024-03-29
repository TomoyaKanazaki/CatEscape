//==========================================
//
//  斬撃エフェクト(slash_effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SLASH_EFFECT_H_
#define _SLASH_EFFECT_H_
#include "object3D_Anim.h"

//==========================================
//  クラス定義
//==========================================
class CSlash_Effect : public CObject3D_Anim
{
public:

	//メンバ関数
	CSlash_Effect(int nPriority = 6);
	~CSlash_Effect();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CSlash_Effect* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXCOLOR& col);

private:

};

#endif
