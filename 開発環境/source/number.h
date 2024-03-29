//==========================================
//
//  ナンバークラス(number.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "object2D.h"

//==========================================
//  ナンバークラス定義
//==========================================
class CNumber : CObject2D
{
public:
	CNumber(int nPriority = 5); //コンストラクタ
	~CNumber(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetNum(const int nNumber) { m_nNumber = nNumber; }

	//静的メンバ関数
	static CNumber *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nNumber);

private:

	//メンバ変数
	int m_nNumber; //表示する値

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture;

};

#endif
