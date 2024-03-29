//==========================================
//
//  斬撃エフェクト(slash.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SLASH_H_
#define _SLASH_H_
#include "object3D_Anim.h"

//==========================================
//  クラス定義
//==========================================
class CSlash : public CObject3D_Anim
{
public:

	//メンバ関数
	CSlash(int nPriority = 6);
	~CSlash();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CSlash* Create(const D3DXVECTOR3 pos, const float rot);

private:

	// メンバ関数
	void Hit();

	// メンバ変数
	D3DXVECTOR3 m_posLeft; // ポリゴンの左端
	D3DXVECTOR3 m_posRight; // ポリゴンの右端

};

#endif
