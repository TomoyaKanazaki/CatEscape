//==========================================
//
//  入力処理(input.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <stdio.h>
#include "input.h"
#include "manager.h"
#include "debugproc.h"
#include "gametime.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;
int CJoyPad::m_nNum = 0;

//==========================================
//  マクロ定義
//==========================================
#define MOUSE_MOVE (0.001f) //マウスの倍率

//==========================================
//  定数定義
//==========================================
namespace
{
	const int STICK_TRIGGER_DEAD = 5000;
	const int STICK_INIT_VALUE = 1000;
}

//==========================================
//  コンストラクタ
//==========================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//==========================================
//  デストラクタ
//==========================================
CInput::~CInput()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND /*hWnd*/)
{
	//DirectInputオブジェクトの生成
	if (m_pInput == nullptr)
	{
		if (FAILED(DirectInput8Create
		(
			hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&m_pInput,
			NULL
		)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CInput::Uninit(void)
{
	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

	//入力デバイスの破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//==========================================
//  キーボード
//==========================================
//  コンストラクタ
//==========================================
CKeyboard::CKeyboard()
{
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = NULL;
		m_aKeyStateTrigger[nCnt] = NULL;
	}
}

//==========================================
//  デストラクタ
//==========================================
CKeyboard::~CKeyboard()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//オブジェクト生成
	CInput::Init(hInstance, hWnd);

	//入力デバイスの設定
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CKeyboard::Update(void)
{
	//ローカル変数宣言
	BYTE aKeyState[NUM_KEY_MAX]; //キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //キーボードのトリガー情報の保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //キーボードのプレス情報の保存
		}
	}
	else
	{
		m_pDevice->Acquire(); //キーボードのアクセス権
	}
}

//==========================================
//  WASD入力
//==========================================
D3DXVECTOR3 CKeyboard::GetWASD(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//W
	if (GetPress(DIK_W))
	{
		move.z += 1.0f;
	}

	//A
	if (GetPress(DIK_A))
	{
		move.x += -1.0f;
	}

	//S
	if (GetPress(DIK_S))
	{
		move.z += -1.0f;
	}

	//D
	if (GetPress(DIK_D))
	{
		move.x += 1.0f;
	}

	//ベクトルの正規化
	D3DXVec3Normalize(&move, &move);

	return move;
}

//==========================================
//  プレス情報の取得
//==========================================
bool CKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//==========================================
//  トリガー情報の取得
//==========================================
bool CKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//==========================================
//  マウス
//==========================================
//  コンストラクタ
//==========================================
CMouse::CMouse()
{
	m_MouseState = {};
	m_MouseStateTrigger = {};
}

//==========================================
//  デストラクタ
//==========================================
CMouse::~CMouse()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//変数を保存
	m_hWnd = hWnd;

	//オブジェクト生成
	CInput::Init(hInstance, hWnd);

	//入力デバイスの設定
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel
	(
		hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)
	)))
	{
		return E_FAIL;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; //相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// デバイスの設定に失敗
		return E_FAIL;
	}

	//マウスへのアクセス権を取得
	m_pDevice->Acquire();

	//マウスカーソルの消去
	ShowCursor(false);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CMouse::Update(void)
{
	//ローカル変数宣言
	DIMOUSESTATE2 mouse;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(mouse), &mouse)))
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			//トリガー情報の保存
			m_MouseStateTrigger.rgbButtons[nCnt] = (m_MouseState.rgbButtons[nCnt] ^ mouse.rgbButtons[nCnt]) & mouse.rgbButtons[nCnt];

			//リリース情報の保存
			m_MouseStateRelease.rgbButtons[nCnt] = (mouse.rgbButtons[nCnt] ^ m_MouseState.rgbButtons[nCnt]) & m_MouseState.rgbButtons[nCnt];
		}

		if (m_MouseState.lX != mouse.lX || m_MouseState.lY != mouse.lY)
		{
			m_bMouseMove = true;
		}
		else
		{
			m_bMouseMove = false;
		}

		//入力情報の保存
		m_MouseState = mouse;
	}
	else
	{
		m_pDevice->Acquire(); //マウスへのアクセス権
	}
}

//==========================================
//  スクリーン上におけるマウスの取得
//==========================================
D3DXVECTOR2 CMouse::GetCursor(void)
{
	//カーソル位置の取得
	POINT CursorPos;
	if (GetCursorPos(&CursorPos))
	{
		//基準値をスクリーンの中心に設定する
		CursorPos.x -= GetSystemMetrics(SM_CXSCREEN) / 2;
		CursorPos.y -= GetSystemMetrics(SM_CYSCREEN) / 2;

		//スクリーン座標をウィンドウ座標に変換する
		ScreenToClient(m_hWnd, &CursorPos);
	}

	//値を返す
	return D3DXVECTOR2((float)CursorPos.x, (float)CursorPos.y);
}

//==========================================
//  プレス情報
//==========================================
bool CMouse::GetPress(int nKey)
{
	return (m_MouseState.rgbButtons[nKey] & 0x80) != 0;
}

//==========================================
//  トリガー情報
//==========================================
bool CMouse::GetTrigger(int nKey)
{
	return (m_MouseStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}

//==========================================
//  リリース情報
//==========================================
bool CMouse::GetRelease(int nKey)
{
	return (m_MouseStateRelease.rgbButtons[nKey] & 0x80) ? true : false;
}

//==========================================
//  マウスの移動量取得
//==========================================
D3DXVECTOR3 CMouse::GetMouseMove(void)
{
	return D3DXVECTOR3(((float)m_MouseState.lX) * MOUSE_MOVE, ((float)m_MouseState.lY) * MOUSE_MOVE, 0.0f);
}

//==========================================
//  マウス操作の有無を取得
//==========================================
bool CMouse::GetMouseControll(void)
{
	return m_bMouseMove;
}

//==========================================
//  ジョイパッド
//==========================================
//  コンストラクタ
//==========================================
CJoyPad::CJoyPad()
{
	m_JoyKeyState = {};
	m_JoyKeyTrigger = {};
	m_Vibration = {};
	m_bVibration = false;
	m_VibrationTimer = 0;
	m_nIdx = m_nNum;

	//使用数を加算する
	m_nNum++;
}

//==========================================
//  デストラクタ
//==========================================
CJoyPad::~CJoyPad()
{
	//使用数を減算する
	m_nNum--;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CJoyPad::Init()
{
	//XInputのステートを設定(有効化)
	XInputEnable(true);

	//メモリクリア
	memset(&m_JoyKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_JoyKeyTrigger, 0, sizeof(XINPUT_STATE));
	memset(&m_Vibration, 0, sizeof(XINPUT_VIBRATION));

	if (XInputGetState(m_nIdx, &m_JoyKeyState) == ERROR_SUCCESS)
	{
		return S_OK;
	}

	return E_FAIL;
}

//==========================================
//  終了処理
//==========================================
void CJoyPad::Uninit(void)
{
	//XInputのステートを設定(無効化)
	XInputEnable(false);

	CInput::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CJoyPad::Update(void)
{
	//ローカル変数宣言
	XINPUT_STATE JoyKeyState; //ジョイパッド入力情報

	//スティックのトリガー情報をリセット
	m_nStickTriggerL = STICK_INIT_VALUE;
	m_nStickTriggerR = STICK_INIT_VALUE;

	//ジョイパッドの状態の取得
	if (XInputGetState(m_nIdx, &JoyKeyState) == ERROR_SUCCESS)
	{
		//トリガー情報を保存
		m_JoyKeyTrigger.Gamepad.wButtons
			= ~m_JoyKeyState.Gamepad.wButtons
			& JoyKeyState.Gamepad.wButtons;

		//スティックの角度を保存
		m_nStickAngleL = (int)D3DXToDegree(atan2f((float)JoyKeyState.Gamepad.sThumbLX, (float)JoyKeyState.Gamepad.sThumbLY));
		m_nStickAngleR = (int)D3DXToDegree(atan2f((float)JoyKeyState.Gamepad.sThumbRX, (float)JoyKeyState.Gamepad.sThumbRY));

		//スティックのトリガー情報を保存
		if (KnockStickL(JoyKeyState)) //左
		{
			m_nStickTriggerL = m_nStickAngleL;
		}
		if (KnockStickR(JoyKeyState)) //右
		{
			m_nStickTriggerR = m_nStickAngleR;
		}

		DebugProc::Print("\n\n%d\n\b", m_nStickAngleR);

		//プレス処理
		m_JoyKeyState = JoyKeyState;

		//バイブ制御
		Vibration();
	}
	else
	{
		Init();
	}
}

//==========================================
//  ジョイパッドのプレス情報の取得
//==========================================
bool CJoyPad::GetPress(JOYKEY Key)
{
	return (m_JoyKeyState.Gamepad.wButtons & (0x01 << Key)) != 0;
}

//==========================================
//  ジョイパッドのトリガー情報の取得
//==========================================
bool CJoyPad::GetTrigger(JOYKEY Key)
{
	return (m_JoyKeyTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}

//==========================================
//  ジョイパッドのLT/RTのプレス
//==========================================
bool CJoyPad::GetLTRT(JOYKEY key, int Pedal)
{
	//ローカル変数
	int nKeep = 0;

	switch (key)
	{
	case BUTTON_LT:
		nKeep = (int)m_JoyKeyState.Gamepad.bLeftTrigger;
		break;
	case BUTTON_RT:
		nKeep = (int)m_JoyKeyState.Gamepad.bRightTrigger;
		break;
	default:
		break;
	}

	//変数を返す
	if (nKeep >= Pedal)
	{
		return true;
	}
	return false;
}

//==========================================
//  ジョイパッドのLスティック情報(D3DXVECTOR3)
//==========================================
D3DXVECTOR3 CJoyPad::GetStickL(float Dead)
{
	//ローカル変数宣言
	D3DXVECTOR3 Stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Stick.x = (float)m_JoyKeyState.Gamepad.sThumbLX / SHRT_MAX;
	if (fabsf(Stick.x) < Dead)
	{
		Stick.x = 0.0f;
	}

	Stick.z = (float)m_JoyKeyState.Gamepad.sThumbLY / SHRT_MAX;
	if (fabsf(Stick.z) < Dead)
	{
		Stick.z = 0.0f;
	}

	return Stick;
}

//==========================================
//  ジョイパッドのRスティック情報(D3DXVECTOR3)
//==========================================
D3DXVECTOR3 CJoyPad::GetStickR(float Dead)
{
	//ローカル変数宣言
	D3DXVECTOR3 Stick = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Stick.x = (float)m_JoyKeyState.Gamepad.sThumbRX / SHRT_MAX;
	if (fabsf(Stick.x) < Dead)
	{
		Stick.x = 0.0f;
	}

	Stick.z = (float)m_JoyKeyState.Gamepad.sThumbRY / SHRT_MAX;
	if (fabsf(Stick.z) < Dead)
	{
		Stick.z = 0.0f;
	}

	return Stick;
}

//==========================================
//  スティックの入力判定
//==========================================
bool CJoyPad::KnockStickL(XINPUT_STATE JoyKey) //左
{
	//ローカル変数宣言
	bool bJudgment = false;

	//前回入力の判定
	if (fabsf(m_JoyKeyState.Gamepad.sThumbLX) <= STICK_TRIGGER_DEAD && fabsf(m_JoyKeyState.Gamepad.sThumbLY) <= STICK_TRIGGER_DEAD)
	{
		//今回入力の判定
		if (fabsf(JoyKey.Gamepad.sThumbLX) >= STICK_TRIGGER_DEAD || fabsf(JoyKey.Gamepad.sThumbLY) >= STICK_TRIGGER_DEAD)
		{
			bJudgment = true;
		}
	}

	//変数を返す
	return bJudgment;
}

bool CJoyPad::KnockStickR(XINPUT_STATE JoyKey) //右
{
	//ローカル変数宣言
	bool bJudgment = false;

	//前回入力の判定
	if (fabsf(m_JoyKeyState.Gamepad.sThumbRX) <= STICK_TRIGGER_DEAD && fabsf(m_JoyKeyState.Gamepad.sThumbRY) <= STICK_TRIGGER_DEAD)
	{
		//今回入力の判定
		if (fabsf(JoyKey.Gamepad.sThumbRX) >= STICK_TRIGGER_DEAD || fabsf(JoyKey.Gamepad.sThumbRY) >= STICK_TRIGGER_DEAD)
		{
			bJudgment = true;
		}
	}

	//変数を返す
	return bJudgment;
}

//==========================================
//  バイブ処理
//==========================================
void CJoyPad::Vibration()
{
	if (m_bVibration)
	{
		//バイブ時間の更新
		m_VibrationTimer -= CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

		//バイブ状態のリセット
		if (m_VibrationTimer <= 0.0f)
		{
			m_VibrationTimer = 0.0f;
			m_bVibration = false;
		}
	}
	else
	{
		memset(&m_Vibration, 0, sizeof(XINPUT_VIBRATION));
	}

	//バイブ情報をジョイパッドに送信
	XInputSetState(m_nIdx, &m_Vibration);
}

//==========================================
//  スティックのトリガー取得
//==========================================
bool CJoyPad::GetStickTriggerL(int nDirection) //左
{
	// 全判定の場合
	if (nDirection == STICK_ALL)
	{
		// 初期化された値じゃない場合
		if (m_nStickTriggerL == STICK_INIT_VALUE)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return abs(m_nStickTriggerL - nDirection) < 45 ? true : false;
}

bool CJoyPad::GetStickTriggerR(int nDirection) //右
{
	// 全判定の場合
	if (nDirection == STICK_ALL)
	{
		// 初期化された値じゃない場合
		if (m_nStickTriggerR == STICK_INIT_VALUE)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return abs(m_nStickTriggerR - nDirection) < 45 ? true : false;
}

//==========================================
//  バイブ速度の加算
//==========================================
void CJoyPad::AddVibrationSpeed(WORD speed)
{
	// 最大値をオーバーしないサイズに丸める
	if (m_Vibration.wLeftMotorSpeed + speed > USHRT_MAX)
	{
		m_Vibration.wLeftMotorSpeed = USHRT_MAX;
	}
	else
	{
		m_Vibration.wLeftMotorSpeed += speed;
	}
	if (m_Vibration.wRightMotorSpeed + speed > USHRT_MAX)
	{
		m_Vibration.wRightMotorSpeed = USHRT_MAX;
	}
	else
	{
		m_Vibration.wRightMotorSpeed += speed;
	}

	//バイブ情報の値を補正する
	if (m_Vibration.wLeftMotorSpeed < 0)
	{
		m_Vibration.wLeftMotorSpeed = 0;
	}
	if (m_Vibration.wRightMotorSpeed < 0)
	{
		m_Vibration.wRightMotorSpeed = 0;
	}
}

//==========================================
//  バイブ時間の加算
//==========================================
void CJoyPad::AddVibrationTimer(float time)
{
	// マイナスの値を加算させない
	if (time < 0.0f) { return; }

	// 加算
	m_VibrationTimer += time;

	// バイブフラグをオン
	m_bVibration = true;
}
