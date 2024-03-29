//==========================================
//
//  スティックぐりぐりUI(stick.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _STICK_H_
#define _STICK_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CStick : public CObject2D
{
public:

	//メンバ関数
	CStick(int nPriority = 7);
	~CStick();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CStick* Create();

private:

};

#endif
