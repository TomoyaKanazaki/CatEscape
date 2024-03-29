//==========================================
//
//  体力表示(enemylife.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_LIFE_H_
#define _ENEMY_LIFE_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CEnemyLife : public CObject2D
{
public:

	//メンバ関数
	CEnemyLife(int nPriority = 7);
	~CEnemyLife();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CEnemyLife* Create();

private:

	// メンバ関数
	void ClacSize();

	// メンバ変数
	int m_nIdx; // 体力番号
	D3DXVECTOR3 m_sizeDest; // 目標のサイズ

	// 静的メンバ変数
	static int m_nNum; // 生成数

};

#endif
