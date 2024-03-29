//==========================================
//
//  体力表示(bosslife.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_LIFE_H_
#define _BOSS_LIFE_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CBossLife : public CObject2D
{
public:

	//メンバ関数
	CBossLife(int nPriority = 7);
	~CBossLife();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	bool GetDeath() { return m_bDead; }

	//静的メンバ関数
	static CBossLife* Create();

private:

	// メンバ関数
	void ClacSize();

	// メンバ変数
	D3DXVECTOR3 m_sizeDest; // 目標のサイズ
	float m_fLife; // 体力
	bool m_bDead; // 終了フラグ

};

#endif
