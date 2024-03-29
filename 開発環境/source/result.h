//==========================================
//
//  リザルトメッセージ(result.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CResult : public CObject3D
{
public:

	//メンバ関数
	CResult(int nPriority = 7);
	~CResult();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CResult* Create();

private:

};

#endif
