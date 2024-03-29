//==========================================
//
//  マネキンクラス(doll.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _DOLL_H_
#define _DOLL_H_
#include "object_char.h"

//==========================================
//  クラス定義
//==========================================
class CDoll : public CObject_Char
{
public:

	//メンバ関数
	CDoll(int nPriority = 4); //コンストラクタ
	~CDoll(); //デストラクタ

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Dash(void);

	//静的メンバ関数
	static CDoll* Create(D3DXVECTOR3 pos);

};

#endif
