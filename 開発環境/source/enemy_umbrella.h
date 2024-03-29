//==========================================
//
//  唐笠お化け(enemy_umbrella.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_UMBRELLA_H_
#define _ENEMY_UMBRELLA_H_
#include "enemy.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy_Umbrella : public CEnemy
{
public:

	// メンバ関数
	CEnemy_Umbrella();
	~CEnemy_Umbrella();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	// メンバ関数
	void RotationLoop(); // 回り続ける
	void Move(); // 移動
	bool CalcDistancePlayer(); // プレイヤーとの距離を測る

	// メンバ変数
	D3DXVECTOR3 m_posDefault; // 初期位置
	float m_fMoveTime; // 移動している時間
	bool m_bLook; // プレイヤー発見フラグ

};

#endif
