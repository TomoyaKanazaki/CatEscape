//==========================================
//
//  3Dポリゴンのエフェクト(effect3D.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EFFECT_3D_H_
#define _EFFECT_3D_H_
#include "object3D.h"

//==========================================
//  クラス定義
//==========================================
class CEffect3D : public CObject3D
{
public:

	// メンバ関数
	CEffect3D(); // コンストラクタ
	~CEffect3D(); // デストラクタ

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CEffect3D* Create(D3DXVECTOR3 pos, bool BillBoard = false);

private:

};

#endif
