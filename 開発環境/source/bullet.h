//==========================================
//
//  弾クラス(bullet.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "object3D_Anim.h"

//==========================================
//  クラス定義
//==========================================
class CBullet : public CObject3D_Anim
{
public:

	// メンバ関数
	CBullet(int nPriority = 6);
	~CBullet();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CBullet* Create(const D3DXVECTOR3& pos);

private:

	// メンバ関数
	void SetMove(); // 移動量の設定
	void Hit(); // 当たり判定

	// メンバ変数
	D3DXVECTOR3 m_target; // 着弾目標地点

};

#endif
