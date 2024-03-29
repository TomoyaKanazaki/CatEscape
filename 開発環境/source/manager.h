//==========================================
//
//  マネージャクラス(manager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//==========================================
//  マクロ定義
//==========================================
#define MAX_PLAYER (4) //プレイヤーの最大数

//==========================================
//  前方宣言
//==========================================
class CRenderer;
class CKeyboard;
class CMouse;
class CJoyPad;
class CSound;
class CTexture;
class CSceneManager;
class CGameTime;

//==========================================
//  マネージャクラス定義
//==========================================
class CManager
{
public:

	//定数
#define SCREEN_WIDTH (1280) //スクリーンの幅
#define SCREEN_HEIGHT (720) //スクリーンの高さ
#define CENTER_WIDTH (SCREEN_WIDTH / 2) //スクリーン中心座標のY座標
#define CENTER_HEIGHT (SCREEN_HEIGHT / 2) //スクリーン中心座標のX座標
#define FLOAT_SCREEN_WIDTH (1280.0f) //スクリーンの幅(float版)
#define FLOAT_SCREEN_HEIGHT (720.0f) //スクリーンの高さ(float版)
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "斬捨御免"

	CManager(); //コンストラクタ
	~CManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CRenderer* GetRenderer(void) { return m_pRenderer; }
	CKeyboard* GetKeyboard(void) { return m_pKeyboard; }
	CMouse* GetMouse(void) { return m_pMouse; }
	CJoyPad* GetJoyPad(void) { return m_pJoyPad; }
	CSound* GetSound(void) { return m_pSound; }
	CTexture* GetTexture(void) { return m_pTexture; }
	CSceneManager* GetSceneManager(void) { return m_pSceneManager; }
	CGameTime* GetGameTime(void) { return m_pGameTime; }
	int GetFPS(void) { return m_nFPS; }
	void SetFPS(int nFPS) { m_nFPS = nFPS; }

	//静的メンバ関数
	static CManager* GetInstance(void);
	static HRESULT Release(void);
	static HWND GetWindowHandle(void) { return m_Wnd; }

private:

	//メンバ変数
	HINSTANCE m_Instance; 
	BOOL m_Window;
	CRenderer* m_pRenderer;
	CKeyboard* m_pKeyboard;
	CMouse* m_pMouse;
	CJoyPad* m_pJoyPad;
	CSound* m_pSound;
	CTexture* m_pTexture;
	CSceneManager* m_pSceneManager;
	CGameTime* m_pGameTime;
	int m_nFPS;

	//静的メンバ変数
	static CManager* m_pManager;
	static HWND m_Wnd;

};

#endif
