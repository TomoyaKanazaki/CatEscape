//==========================================
//
//  体力表示(life.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LIFE_H_
#define _LIFE_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CLife : public CObject2D
{
public:

	//メンバ関数
	CLife(int nPriority = 7);
	~CLife();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CLife* Create();

private:

	// メンバ変数
	int m_nIdx; // 体力番号

	// 静的メンバ変数
	static int m_nNum; // 生成数

};

#endif
