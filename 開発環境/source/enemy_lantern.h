//==========================================
//
//  �񓔂�����(enemy_lantern.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_LANTERN_H_
#define _ENEMY_LANTERN_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy_Lantern : public CEnemy
{
public:

	// �����o�֐�
	CEnemy_Lantern();
	~CEnemy_Lantern();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

};

#endif
