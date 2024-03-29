//==========================================
//
//  入力処理(input.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "Xinput.h"
#pragma comment(lib,"xinput.lib")

//==========================================
//  マクロ定義
//==========================================
#define NUM_KEY_MAX	(256) //キーの最大値

//==========================================
//  インプットクラス
//==========================================
class CInput
{
public:
	CInput(); //コンストラクタ
	virtual ~CInput(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
	
protected:

	//メンバ変数
	LPDIRECTINPUTDEVICE8 m_pDevice;

	//静的メンバ変数
	static LPDIRECTINPUT8 m_pInput;
};

//==========================================
//  キーボードクラス
//==========================================
class CKeyboard : public CInput
{
public:
	CKeyboard(); //コンストラクタ
	~CKeyboard(); //デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit(void);
	void Update(void);
	D3DXVECTOR3 GetWASD(void); //WASD入力のベクトル取得
	bool GetPress(int nKey); //プレス情報の取得
	bool GetTrigger(int nKey); //トリガー情報の取得

private:

	//メンバ変数
	BYTE m_aKeyState[NUM_KEY_MAX]; //全入力情報の保管
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //トリガー情報
};

//==========================================
//  マウスクラス
//==========================================
class CMouse : public CInput
{
public:
	typedef enum
	{
		BUTTON_LEFT = 0,
		BUTTON_RIGHT,
		BUTTON_WHEEL,
		BUTTON_SIDE1,
		BUTTON_SIDE2,
		BUTTON_MAX
	}BUTTON;

	CMouse(); //コンストラクタ
	~CMouse(); //デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	D3DXVECTOR2 GetCursor(void);
	bool GetPress(int nKey); //プレス情報の取得
	bool GetTrigger(int nKey); //トリガー情報の取得
	bool GetRelease(int nKey); //リリース情報の取得
	D3DXVECTOR3 GetMouseMove(void); //マウス移動量の取得
	bool GetMouseControll(void); //マウス操作の有無を取得

private:

	//メンバ変数
	DIMOUSESTATE2 m_MouseState; //全入力情報の保管
	DIMOUSESTATE2 m_MouseStateTrigger; //トリガー情報
	DIMOUSESTATE2 m_MouseStateRelease; //リリース情報
	bool m_bMouseMove; //マウス操作の有無
	HWND m_hWnd; //カーソル位置の取得に必要
};

//==========================================
//  ジョイパッドクラス
//==========================================
class CJoyPad : public CInput
{
public:
	typedef enum
	{
		BUTTON_UP = 0,
		BUTTON_DOWN,
		BUTTON_LEFT,
		BUTTON_RIGHT,
		BUTTON_START,
		BUTTON_BACK,
		BUTTON_L3,
		BUTTON_R3,
		BUTTON_LB,
		BUTTON_RB,
		BUTTON_LT,
		BUTTON_RT,
		BUTTON_A,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		STICK_LX,
		STICK_LY,
		STICK_RX,
		STICK_RY,
		BUTTON_MAX
	}JOYKEY;

	typedef enum
	{
		MINUS = 0,
		PLUS
	}Stick;

	//ジョイスティック方向
	typedef enum
	{
		STICK_UP = 180, //上方向
		STICK_DOWN = 0, //下方向
		STICK_RIGHT = 90, //右方向
		STICK_LEFT = -90, //左方向
		STICK_ALL = 360 // 全方向判定
	}JOYKEY_STICK;

	CJoyPad(); //コンストラクタ
	~CJoyPad(); //デストラクタ

	//メンバ関数
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	bool GetPress(JOYKEY Key);
	bool GetTrigger(JOYKEY Key);
	bool GetLTRT(JOYKEY key, int nPedal);
	D3DXVECTOR3 GetStickL(float Dead);
	D3DXVECTOR3 GetStickR(float Dead);
	bool GetStickTriggerL(int nDirection);
	bool GetStickTriggerR(int nDirection);
	void AddVibrationSpeed(WORD speed);
	void AddVibrationTimer(float time);

private:

	// メンバ関数
	bool KnockStickL(XINPUT_STATE JoyKey);
	bool KnockStickR(XINPUT_STATE JoyKey);
	void Vibration();

	//メンバ変数
	XINPUT_STATE m_JoyKeyState; //プレス情報
	XINPUT_STATE m_JoyKeyTrigger; //トリガー情報
	XINPUT_VIBRATION m_Vibration; //バイブ情報
	bool m_bVibration; //バイブ状態
	int m_nStickAngleL; // 左スティックの角度
	int m_nStickAngleR; // 右スティックの角度
	int m_nStickTriggerL; // 左スティックのトリガー
	int m_nStickTriggerR; // 右スティックのトリガー
	float m_VibrationTimer; //バイブの持続時間
	int m_nIdx; //ジョイパッドの通し番号

	//静的メンバ変数
	static int m_nNum; //ジョイパッドの接続数

};

#endif