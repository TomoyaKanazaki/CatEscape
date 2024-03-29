//==========================================
//
//  画面遷移管理クラス(scenemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

//==========================================
//  前方宣言
//==========================================
class CScene;
class CFade;
class CCamera;

//==========================================
//  画面遷移クラス定義
//==========================================
class CSceneManager
{
public:
	enum SCENE
	{
		NONE = 0,
		TITLE,
		GAME,
		RESULT,
		RANKING,
		MAX
	};

	CSceneManager(); //コンストラクタ
	~CSceneManager(); //デストラクタ

	//メンバ関数
	void Init(SCENE newsecene);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool SetNext(SCENE next);

	//静的メンバ関数
	static CScene *GetScene(void) { return m_pScene; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CSceneManager *Create(SCENE scene = TITLE);
	static bool GetClear(void) { return m_bClear; }
	static void SetClear(bool bClear) { m_bClear = bClear; }

private:

	//メンバ変数
	SCENE m_Scene; //現在のゲームモード
	SCENE m_Next; //次のゲームモード
	CFade *m_pFade; //フェードのポインタ

	//静的メンバ変数
	static CScene *m_pScene; //シーンのポインタ
	static CCamera *m_pCamera; //カメラのポインタ
	static bool m_bClear; //クリアフラグ

};

#endif
