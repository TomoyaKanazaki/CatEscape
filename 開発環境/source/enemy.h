//==========================================
//
//  敵クラス(enemy.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "object_char.h"

//==========================================
//  クラス定義
//==========================================
class CEnemy : public CObject_Char
{
public:

	//列挙型定義
	enum TYPE
	{
		LANTERN = 0, // 提灯お化け
		UMBRELLA, // 唐笠お化け
		BOSS, // ボス
		RESULT, // リザルト用のボス
		MAX,
		NONE
	};

	//メンバ関数
	CEnemy(int nPriority = 5);
	~CEnemy();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	float GetLife() { return m_fLife; } // 体力の取得
	virtual int GetState() { return -1; }
	D3DXVECTOR3 GetCenterPos() override { return m_posCenter; }

	//静的メンバ関数
	static CEnemy* Create(D3DXVECTOR3 pos, CEnemy::TYPE type);
	static float GetDamage() { return m_AllDamage; } // 受けたダメージの取得
	static void ResetDamage() { m_AllDamage = 0.0f; } // 受けたダメージのリセット

protected:

	//メンバ関数
	void RotateToMove(); // 移動方向を向く
	void RotateToPlayer(); // プレイヤーを向く
	virtual void Attacked(); // 被撃時の処理

	// メンバ変数
	float m_fLife; // 体力
	float m_fInvincible; // 無敵時間
	D3DXVECTOR3 m_posCenter; // 見た目の中心

	// 静的メンバ変数
	static float m_AllDamage; // 受けたダメージ

private:

	//メンバ変数
	CEnemy::TYPE m_type;

};

#endif
