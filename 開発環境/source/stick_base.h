//==========================================
//
//  スティックぐりぐりUI(stick_base.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _STICK_BASEE_H_
#define _STICK_BASEE_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CBase : public CObject2D
{
public:

	//メンバ関数
	CBase(int nPriority = 6);
	~CBase();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CBase* Create(const D3DXVECTOR3& pos);

private:

};

#endif
