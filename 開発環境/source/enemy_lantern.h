//==========================================
//
//  提灯お化け(enemy_lantern.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_LANTERN_H_
#define _ENEMY_LANTERN_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy_Lantern : public CEnemy
{
public:

	// メンバ関数
	CEnemy_Lantern();
	~CEnemy_Lantern();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

};

#endif
