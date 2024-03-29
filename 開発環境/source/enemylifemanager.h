//==========================================
//
//  体力表示の管理クラス(enemylifemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_LIFE_MANAGER_H_
#define _ENEMY_LIFE_MANAGER_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CEnemyLifeManager : public CObject2D
{
public:

	//メンバ関数
	CEnemyLifeManager(int nPriority = 7);
	~CEnemyLifeManager();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CEnemyLifeManager* Create();

private:

};

#endif
