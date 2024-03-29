//==========================================
//
//  体力表示の管理クラス(lifemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LIFE_MANAGER_H_
#define _LIFE_MANAGER_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CLifeManager : public CObject2D
{
public:

	//メンバ関数
	CLifeManager(int nPriority = 7);
	~CLifeManager();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CLifeManager* Create();

private:

};

#endif
