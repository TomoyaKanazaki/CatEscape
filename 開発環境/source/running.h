//==========================================
//
//  マネキンクラス(running.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RUNNING_H_
#define _RUNNING_H_
#include "object_char.h"

//==========================================
//  クラス定義
//==========================================
class CRunning : public CObject_Char
{
public:

	//メンバ関数
	CRunning(int nPriority = 4); //コンストラクタ
	~CRunning(); //デストラクタ

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Dash(void);

	//静的メンバ関数
	static CRunning* Create();

private:

	// メンバ関数
	void Rotate();

	// メンバ変数
	D3DXVECTOR3 m_end; // 終了位置

};

#endif
