//==========================================
//
//  ライトクラス(light.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//==========================================
//  マクロ定義
//==========================================
#define NUM_LIGHT (3) //ライトの数

//==========================================
//  ライトクラス定義
//==========================================
class CLight
{
public:
	CLight(); //コンストラクタ
	~CLight(); //デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

	//メンバ変数
	D3DLIGHT9 m_Light[NUM_LIGHT]; //ライト情報

};

#endif
