//==========================================
//
//  �}�l�[�W���N���X(manager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//==========================================
//  �}�N����`
//==========================================
#define MAX_PLAYER (4) //�v���C���[�̍ő吔

//==========================================
//  �O���錾
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
//  �}�l�[�W���N���X��`
//==========================================
class CManager
{
public:

	//�萔
#define SCREEN_WIDTH (1280) //�X�N���[���̕�
#define SCREEN_HEIGHT (720) //�X�N���[���̍���
#define CENTER_WIDTH (SCREEN_WIDTH / 2) //�X�N���[�����S���W��Y���W
#define CENTER_HEIGHT (SCREEN_HEIGHT / 2) //�X�N���[�����S���W��X���W
#define FLOAT_SCREEN_WIDTH (1280.0f) //�X�N���[���̕�(float��)
#define FLOAT_SCREEN_HEIGHT (720.0f) //�X�N���[���̍���(float��)
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "�a�̌��"

	CManager(); //�R���X�g���N�^
	~CManager(); //�f�X�g���N�^

	//�����o�֐�
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

	//�ÓI�����o�֐�
	static CManager* GetInstance(void);
	static HRESULT Release(void);
	static HWND GetWindowHandle(void) { return m_Wnd; }

private:

	//�����o�ϐ�
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

	//�ÓI�����o�ϐ�
	static CManager* m_pManager;
	static HWND m_Wnd;

};

#endif
