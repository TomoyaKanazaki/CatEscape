//==========================================
//
//  ���͏���(input.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "Xinput.h"
#pragma comment(lib,"xinput.lib")

//==========================================
//  �}�N����`
//==========================================
#define NUM_KEY_MAX	(256) //�L�[�̍ő�l

//==========================================
//  �C���v�b�g�N���X
//==========================================
class CInput
{
public:
	CInput(); //�R���X�g���N�^
	virtual ~CInput(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
	
protected:

	//�����o�ϐ�
	LPDIRECTINPUTDEVICE8 m_pDevice;

	//�ÓI�����o�ϐ�
	static LPDIRECTINPUT8 m_pInput;
};

//==========================================
//  �L�[�{�[�h�N���X
//==========================================
class CKeyboard : public CInput
{
public:
	CKeyboard(); //�R���X�g���N�^
	~CKeyboard(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit(void);
	void Update(void);
	D3DXVECTOR3 GetWASD(void); //WASD���͂̃x�N�g���擾
	bool GetPress(int nKey); //�v���X���̎擾
	bool GetTrigger(int nKey); //�g���K�[���̎擾

private:

	//�����o�ϐ�
	BYTE m_aKeyState[NUM_KEY_MAX]; //�S���͏��̕ۊ�
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //�g���K�[���
};

//==========================================
//  �}�E�X�N���X
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

	CMouse(); //�R���X�g���N�^
	~CMouse(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	D3DXVECTOR2 GetCursor(void);
	bool GetPress(int nKey); //�v���X���̎擾
	bool GetTrigger(int nKey); //�g���K�[���̎擾
	bool GetRelease(int nKey); //�����[�X���̎擾
	D3DXVECTOR3 GetMouseMove(void); //�}�E�X�ړ��ʂ̎擾
	bool GetMouseControll(void); //�}�E�X����̗L�����擾

private:

	//�����o�ϐ�
	DIMOUSESTATE2 m_MouseState; //�S���͏��̕ۊ�
	DIMOUSESTATE2 m_MouseStateTrigger; //�g���K�[���
	DIMOUSESTATE2 m_MouseStateRelease; //�����[�X���
	bool m_bMouseMove; //�}�E�X����̗L��
	HWND m_hWnd; //�J�[�\���ʒu�̎擾�ɕK�v
};

//==========================================
//  �W���C�p�b�h�N���X
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

	//�W���C�X�e�B�b�N����
	typedef enum
	{
		STICK_UP = 180, //�����
		STICK_DOWN = 0, //������
		STICK_RIGHT = 90, //�E����
		STICK_LEFT = -90, //������
		STICK_ALL = 360 // �S��������
	}JOYKEY_STICK;

	CJoyPad(); //�R���X�g���N�^
	~CJoyPad(); //�f�X�g���N�^

	//�����o�֐�
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

	// �����o�֐�
	bool KnockStickL(XINPUT_STATE JoyKey);
	bool KnockStickR(XINPUT_STATE JoyKey);
	void Vibration();

	//�����o�ϐ�
	XINPUT_STATE m_JoyKeyState; //�v���X���
	XINPUT_STATE m_JoyKeyTrigger; //�g���K�[���
	XINPUT_VIBRATION m_Vibration; //�o�C�u���
	bool m_bVibration; //�o�C�u���
	int m_nStickAngleL; // ���X�e�B�b�N�̊p�x
	int m_nStickAngleR; // �E�X�e�B�b�N�̊p�x
	int m_nStickTriggerL; // ���X�e�B�b�N�̃g���K�[
	int m_nStickTriggerR; // �E�X�e�B�b�N�̃g���K�[
	float m_VibrationTimer; //�o�C�u�̎�������
	int m_nIdx; //�W���C�p�b�h�̒ʂ��ԍ�

	//�ÓI�����o�ϐ�
	static int m_nNum; //�W���C�p�b�h�̐ڑ���

};

#endif