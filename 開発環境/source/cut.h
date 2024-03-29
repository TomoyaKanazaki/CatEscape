//==========================================
//
//  斬られたポリゴン(cut.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CUT_H_
#define _CUT_H_
#include "object.h"

//==========================================
//  クラス定義
//==========================================
class CCut : public CObject
{
public:

	//メンバ関数
	CCut();
	~CCut();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//静的メンバ関数
	static CCut* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex, int nPattern = 1);

private:

	//メンバ変数
	LPDIRECT3DTEXTURE9 tex;
	int m_nPattern;

	//定数定義
	static const float m_fSpeed;
};

#endif
