//==========================================
//
//  建物(build.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BUILD_H_
#define _BUILD_H_
#include "object_char.h"

//==========================================
//  クラス定義
//==========================================
class CBuild : public CObject_Char
{
public:

	//メンバ関数
	CBuild(int nPriority = 4);
	~CBuild();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CBuild* Create(void);
};

#endif
