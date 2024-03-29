//==========================================
//
//  ���[�V�����N���X(motion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MOTION_H_
#define _MOTION_H_

//==========================================
//  �O���錾
//==========================================
class CModel;

//==========================================
//  ���[�V�����N���X��`
//==========================================
class CMotion
{
public:

	//�萔��`
#define MAX_NUM (32) //�e��f�[�^�̍ő吔

	typedef enum
	{
		PLAYER_WAIT = 0, //�ҋ@���[�V����
		PLAYER_WALK, //���s���[�V����
		PLAYER_JUMP, //�W�����v���[�V����
		PLAYER_FALL, //�������[�V����
		PLAYER_IAI, //�������[�V����
		PLAYER_DEATH, //���S���[�V����
		LANTERN_WAIT, // �񓔂������ҋ@
		UMBRELLA_WAIT, // ���}�������ҋ@
		BOSS_POP, // �{�X�o��
		BOSS_WAIT, // �{�X�ҋ@
		BOSS_BULLET, // �������U��
		BOSS_ATTACK, // �ߋ����U��
		BOSS_DEATH, // ���S
		BOSS_DASH, // �ːi
		BLADE, // 
		MOTION_NONE
	}MOTION;

	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		D3DXVECTOR3 rot; //�p�x
	}KEY;

	typedef struct
	{
		int nFrame; //�t���[����
		KEY aKey[MAX_NUM]; //�L�[���
	}KEY_INFO;

	typedef struct
	{
		bool bLoop; //���[�v�̗L��
		int nNumKey; //�L�[��
		int nNumModel; //���f����
		KEY_INFO aKeyInfo[MAX_NUM]; //�L�[���
	}INFO;

	CMotion(); //�R���X�g���N�^
	~CMotion(); //�f�X�g���N�^

	//�����o�֐�
	void Update(void);
	void SetModel(CModel **ppModel, int nNum, MOTION type);
	void Set(MOTION type);
	bool GetFinish() { return m_bMotion; } // �����t���O
	
	//�ÓI�����o�֐�
	static void Load(void);

private:

	//�����o�ϐ�
	CModel **m_ppModel;
	INFO m_Info;
	KEY m_oldKey;
	KEY m_startKey[MAX_NUM];
	int m_nNumModel;
	int m_nCntFrame;
	int m_nCntKey;
	bool m_bMotion;

	//�ÓI�����o�ϐ�
	static INFO m_aInfo[MAX_NUM];
	static int m_nNumMotion;

};

#endif
