//==========================================
//
//  ボスクラス(boss_result.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_RESULT_H_
#define _BOSS_RESULT_H_
#include "enemy.h"

//==========================================
//  前方宣言
//==========================================
class COrbit;

//==========================================
//  クラス定義
//==========================================
class CBossResult : public CEnemy
{
public:

	//メンバ関数
	CBossResult(int nPriority = 5);
	~CBossResult();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	// メンバ変数
	COrbit* m_pOrbit[2]; // 剣の軌跡ポインタ

};

#endif
