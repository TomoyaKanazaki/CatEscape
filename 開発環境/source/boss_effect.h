//==========================================
//
//  ボスの出現エフェクト(boss_effect.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_EFFECT_H_
#define _BOSS_EFFECT_H_
#include "object3D_Anim.h"

//==========================================
//  クラス定義
//==========================================
class CBossEffect : public CObject3D_Anim
{
public:

	// メンバ関数
	CBossEffect(int nPriority = 6);
	~CBossEffect();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ変数
	static CBossEffect* Create(const D3DXVECTOR3& pos);

private:

	// メンバ変数
	int m_TexIdx; // テクスチャインデックス

};

#endif
