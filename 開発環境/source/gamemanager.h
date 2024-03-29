//==========================================
//
//  �Q�[���}�l�[�W���N���X(gamemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include "scene.h"

//==========================================
//  �O���錾
//==========================================
class CPlayer;
class CCamera;
class CLight;
class CEnemyManager;
class CBossLife;

//==========================================
//  �Q�[���}�l�[�W���N���X��`
//==========================================
class CGameManager : public CScene
{
public:

	//�Q�[�����
	enum State
	{
		STATE_START = 0, //�Q�[���J�n
		STATE_NORMAL, //�ʏ���
		STATE_BOSS, // �{�X����
		STATE_RUSH, // �A�����
		STATE_END, //�Q�[���I��
		MAX,
		NONE
	};

	//�Q�[���i�s
	enum Progress
	{
		START = 0,
		TUTORIAL_ENEMY, //�G�𔭌�
		TUTORIAL_ARROW, //�G��������
		TUTORIAL_DASH, //�a���Ă݂�
		END
	};

	CGameManager(); //�R���X�g���N�^
	~CGameManager(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static State GetState(void) { return m_State; }
	static State GetOldState(void) { return m_oldState; }
	static CEnemyManager* GetEnemy() { return m_pEnemy; }

private:

	// �����o�֐�
	void TaskTutorial(); // �`���[�g���A���̏���
	void TaskState(); // ��ԊǗ�

	//�����o�ϐ�
	float m_fTimer; // ��ԑJ�ڗp�^�C�}�[

	//�ÓI�����o�ϐ�
	static const float m_fDashTime;
	static CPlayer* m_pPlayer;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static State m_State; //�Q�[���̏��
	static State m_oldState; //�O�t���[���ł̃Q�[���̏��
	static Progress m_Progress; //�i�s��
	static CEnemyManager* m_pEnemy;
	static CBossLife* m_pLife;

};

#endif
