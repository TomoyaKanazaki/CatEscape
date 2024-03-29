//==========================================
//
//  背景クラス(bg.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BG_H_
#define _BG_H_
#include "object_mesh.h"

//==========================================
//  クラス定義
//==========================================
class CBg : public CObject_Mesh
{
public:
	
	//メンバ関数
	CBg(int nPriority = 1);
	~CBg();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//静的メンバ関数
	static CBg* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumPorygon);

private:

};

#endif
