//==========================================
//
//  タイトルのロゴ(title.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CTitle : public CObject3D
{
public:

	//メンバ関数
	CTitle(int nPriority = 7);
	~CTitle();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void CutTitle(void);

	//静的メンバ関数
	static CTitle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

};

#endif
