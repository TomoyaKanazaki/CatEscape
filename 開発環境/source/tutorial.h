//==========================================
//
//  操作方法(tutorial.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CTutorial : public CObject2D
{
public:

	//メンバ関数
	CTutorial(int nPriority = 7);
	~CTutorial();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CTutorial* Create();

private:

	// 静的メンバ変数
	static int m_nIdx;
};

#endif
