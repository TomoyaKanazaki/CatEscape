//==========================================
//
//  プレイヤークラス(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "object_char.h"

//==========================================
//  前方宣言
//==========================================
class COrbit;

//==========================================
//  プレイヤークラスの定義
//==========================================
class CPlayer : public CObject_Char
{
public:

	//状態定義
	enum State
	{
		NEUTRAL = 0, // 待機状態
		WALK, // 歩行状態
		JUMP, // ジャンプ状態
		FALL, // 落下状態
		IAI, // 居合状態
		DEATH, // 死亡状態
		RUSH, // 連撃状態
		MAX
	};

	CPlayer(int nPriority = 4); //コンストラクタ
	~CPlayer(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetCenterPos(void) override { return m_CenterPos; }
	bool GetDeath(void) { return m_State == DEATH ? true : false; }
	State GetState(void) { return m_State; }
	bool GetDash() const { return m_bDash; }
	float GetHitLength() const { return m_fHitLength; }
	void Attacked(); // ダメージを受けた時の処理
	int GetLife() { return m_nLife; }
	void SetRand(bool rand) { m_bRand = rand; m_bDoubleJump = !rand; }

	//静的メンバ関数
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//メンバ関数
	void Motion();
	void Limit();
	void Move();
	void Rotate();
	void Jump();
	void Gravity();
	void Damage();
	void Attack();
	void Dash();
	void Hit();

	//メンバ変数
	D3DXVECTOR3 m_CenterPos; //中心座標
	D3DXVECTOR3 m_posStart; // 攻撃のスタート地点
	float m_fDashAngle;
	bool m_bRand;
	bool m_bDoubleJump;
	bool m_bDash;
	D3DXMATERIAL *m_pDefMat;
	State m_State;
	State m_oldState;
	float m_fStateCounter; // 状態遷移を管理するタイマー
	float m_AttackCoolTime; // 攻撃のクールタイム
	int m_AttackCounter; // 連続で攻撃した回数
	bool m_bAttack; // 攻撃可能フラグ
	COrbit* m_pOrbit;
	int m_nLife; // 体力
	bool m_bDamage; // ダメージフラグ
	float m_fDamageCounter; // ダメージ状態のカウンタ
	float m_fHitLength; // ヒット範囲

	//モデル情報
	D3DXVECTOR3 m_oldposModel;

};

#endif
