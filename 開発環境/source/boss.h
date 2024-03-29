//==========================================
//
//  ボスクラス(boss.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "enemy.h"

//==========================================
//  前方宣言
//==========================================
class COrbit;

//==========================================
//  クラス定義
//==========================================
class CBoss : public CEnemy
{
public:

	// 行動状態
	enum ACTION
	{
		POP = 0, // 出現状態
		MOVE, // 移動状態
		NEUTRAL, // 待機状態
		DEATH, // 死亡状態
		ATTACK, // 通常攻撃
		DASH, // 突進攻撃
		BULLET, // 遠距離攻撃
		RAIN, // 雨降らし
		RUSH, // とどめの連撃
		MAX
	};

	//メンバ関数
	CBoss(int nPriority = 5);
	~CBoss();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	bool GetDeath() { return m_State == DEATH; }
	int GetState() { return (int)m_State; }

private:

	// メンバ関数
	void Attacked() override;
	void Motion();
	void Move();
	void Rotate(); // 方向転換
	void Neutral(); // 待機中の次の行動を抽選
	void AttackState(); // 攻撃
	void Shot(); // 遠距離攻撃
	void Attack(); // 三連攻撃
	void Dash(); // 突進攻撃
	void Rain(); // 雨降らし
	void Hit(); // 攻撃判定
	void MoveToPlayer(); // プレイヤーに向かって移動する処理

	// メンバ変数
	ACTION m_oldState; // 前回状態
	ACTION m_State; // 行動状態
	float m_MoveTimer; // 移動時間
	COrbit* m_pOrbit[2]; // 剣の軌跡ポインタ
	D3DXVECTOR3 m_TargetPos; // 目標位置
	bool m_Wait; // ダッシュ前の待機完了フラグ
	bool m_Dash; // ダッシュ中フラグ
	int m_nAttackKind; // 攻撃の種類
	bool m_bRain; // 雨降らし追加フラグ
	bool m_bRainWait; // アメフラシ前の移動完了フラグ
	int m_nBulletNum; // 弾の数

};

#endif
