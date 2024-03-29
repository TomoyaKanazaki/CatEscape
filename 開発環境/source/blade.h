//==========================================
//
//  刀弾クラス(blade.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BLADE_H_
#define _BLADE_H_
#include "object_char.h"

//==========================================
//  前方宣言
//==========================================
class COrbit;

//==========================================
//  クラス定義
//==========================================
class CBlade : public CObject_Char
{
public:

	// メンバ関数
	CBlade(int nPriority = 6);
	~CBlade();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CBlade* Create(const D3DXVECTOR3& pos);

private:

	// メンバ関数
	void SetMove(); // 移動量の設定
	void Hit(); // 当たり判定

	// メンバ変数
	float m_rotation;
	float m_Time;
	COrbit* m_pOrbit;

};

#endif
