//==========================================
//
//  �I�u�W�F�N�g�N���X(object.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//==========================================
//  �}�N����`
//==========================================
#define PRIORITY_NUM (8) //�D�揇�ʂ̍ő吔

//==========================================
//  �I�u�W�F�N�g�N���X����
//==========================================
class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0, //�s�g�p
		TYPE_PLAYER, //�v���C���[
		TYPE_ENEMY, //�G
		TYPE_BOSS, //�{�X
		TYPE_BG, //�w�i
		TYPE_MAP, //�n�`
		TYPE_NUMBER, //����
		TYPE_FIELD, //��
		TYPE_FADE, //�t�F�[�h
		TYPE_ORBIT, //�O��
		METHOD_MAX
	}TYPE;

	enum STATE
	{
		NORMAL = 0, //�ʏ���
		ATTACKED, // �팂���
		INVINCIBLE, // ���G���
		MAX
	};

	CObject(int nPriority = 3); //�R���X�g���N�^
	virtual ~CObject(); //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	CObject *GetNext(void) { return m_pNext; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetOldPos(void) { return m_oldPos; }
	D3DXVECTOR3 GetOldRot(void) { return m_oldRot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	TYPE GetType(void) { return m_type; }
	STATE GetObjState(void) { return m_ObjState; }
	bool GetMap(void) { return m_bMap; }
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }
	void SetSize(const D3DXVECTOR3& size) { m_size = size; }
	void SetType(TYPE type) { m_type = type; }
	void SetMap(void) { m_bMap = true; }
	void SetState(STATE state) { m_ObjState = state; }

	// ���w���̔��o�p
	virtual float GetHitLength() { return 0.0f; }
	virtual D3DXVECTOR3 GetCenterPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

	//�ÓI�����o�֐�
	static CObject *GetTop(int nPriority) { return m_apTop[nPriority]; }
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static int GetNum(void) { return m_nNumObject; }

protected:

	//�����o�֐�
	bool OnScreen(void);
	void Release(void);
	void SetDeath(const bool frag) { m_bDeath = frag; }

	//�����o�ϐ�
	D3DXVECTOR3 m_pos; //�I�u�W�F�N�g�̒��S���W
	D3DXVECTOR3 m_rot; //�I�u�W�F�N�g�̌���
	D3DXVECTOR3 m_move; //�I�u�W�F�N�g�̈ړ���
	D3DXVECTOR3 m_size; //�I�u�W�F�N�g�̃T�C�Y
	D3DXVECTOR3 m_oldPos; //�I�u�W�F�N�g�̑O����W
	D3DXVECTOR3 m_oldRot; //�I�u�W�F�N�g�̑O��p�x
	float m_fDeltaTime; //�O��̍X�V���炩����������
	STATE m_ObjState; //���

private:

	//�����o�ϐ�
	CObject *m_pNext; //���̃I�u�W�F�N�g�̃|�C���^
	CObject *m_pPrev; //�O�̃I�u�W�F�N�g�̃|�C���^
	int m_nPriority; //�`��D�揇��
	TYPE m_type; //���
	bool m_bDeath; //���S�t���O
	bool m_bMap; //�}�b�v�Ɋ֌W����I�u�W�F�N�g���ۂ�

	//�ÓI�����o�ϐ�
	static int m_nNumObject; //�I�u�W�F�N�g�̑���
	static CObject *m_apTop[PRIORITY_NUM]; //�擪�I�u�W�F�N�g�̃|�C���^�z��
	static CObject *m_apCur[PRIORITY_NUM]; //�Ō���I�u�W�F�N�g�̃|�C���^�z��

};

#endif
