//==========================================
//
//  爆発クラス(explosion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "object3D_Anim.h"

//==========================================
//  クラス定義
//==========================================
class CExplosion : public CObject3D_Anim
{
public:

	// メンバ関数
	CExplosion(int nPriority = 6);
	~CExplosion();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CExplosion* Create(const D3DXVECTOR3& pos);

private:

	// メンバ関数
	void Hit(); // 当たり判定

};

#endif
