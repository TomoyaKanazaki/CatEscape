//==========================================
//
//  ゲーム内時間計測のクラス(gametime.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAMETIME_H_
#define _GAMETIME_H_

//==========================================
//  クラス定義
//==========================================
class CGameTime
{
public:

	//メンバ関数
	CGameTime();
	~CGameTime();

	void Init(void);
	void Uninit(void);
	void Update(void);

	int GetDeltaTimeInt(void) { return m_nDeltaTime * m_fScale; }
	float GetDeltaTimeFloat(void) { return m_fDelta * m_fScale; }
	void AddScaling(float scale, float keep);
	void AddScale(float scale);
	void AddTime(float keep);
	void SetScaling(float scale, float keep);
	void SetScale(float scale);
	void SetTime(float keep);
	float GetScale() { return m_fScale; }
	float GetTime() { return m_fScaleTime; }

private:

	// メンバ関数
	void Scaling();

	//メンバ変数
	int m_nCurrentTime; //現在時間
	int m_nOldTime; //前回時間
	int m_nDeltaTime; //現在時間 - 前回時間
	float m_fDelta; //1秒間における経過時間の割合
	float m_fScale; // 経過時間倍率
	float m_fScaleTime; // 倍率適用時間

};

#endif
