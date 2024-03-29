//==========================================
//
//  ゲームマネージャクラス(gamemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include "scene.h"

//==========================================
//  前方宣言
//==========================================
class CPlayer;
class CCamera;
class CLight;
class CEnemyManager;
class CBossLife;

//==========================================
//  ゲームマネージャクラス定義
//==========================================
class CGameManager : public CScene
{
public:

	//ゲーム状態
	enum State
	{
		STATE_START = 0, //ゲーム開始
		STATE_NORMAL, //通常状態
		STATE_BOSS, // ボス戦状態
		STATE_RUSH, // 連撃状態
		STATE_END, //ゲーム終了
		MAX,
		NONE
	};

	//ゲーム進行
	enum Progress
	{
		START = 0,
		TUTORIAL_ENEMY, //敵を発見
		TUTORIAL_ARROW, //敵を向いて
		TUTORIAL_DASH, //斬ってみて
		END
	};

	CGameManager(); //コンストラクタ
	~CGameManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static State GetState(void) { return m_State; }
	static State GetOldState(void) { return m_oldState; }
	static CEnemyManager* GetEnemy() { return m_pEnemy; }

private:

	// メンバ関数
	void TaskTutorial(); // チュートリアルの処理
	void TaskState(); // 状態管理

	//メンバ変数
	float m_fTimer; // 状態遷移用タイマー

	//静的メンバ変数
	static const float m_fDashTime;
	static CPlayer* m_pPlayer;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static State m_State; //ゲームの状態
	static State m_oldState; //前フレームでのゲームの状態
	static Progress m_Progress; //進行状況
	static CEnemyManager* m_pEnemy;
	static CBossLife* m_pLife;

};

#endif
