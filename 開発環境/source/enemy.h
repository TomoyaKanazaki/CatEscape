//==========================================
//
//  �G�N���X(enemy.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "object_char.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy : public CObject_Char
{
public:

	//�񋓌^��`
	enum TYPE
	{
		LANTERN = 0, // �񓔂�����
		UMBRELLA, // ���}������
		BOSS, // �{�X
		RESULT, // ���U���g�p�̃{�X
		MAX,
		NONE
	};

	//�����o�֐�
	CEnemy(int nPriority = 5);
	~CEnemy();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	float GetLife() { return m_fLife; } // �̗͂̎擾
	virtual int GetState() { return -1; }
	D3DXVECTOR3 GetCenterPos() override { return m_posCenter; }

	//�ÓI�����o�֐�
	static CEnemy* Create(D3DXVECTOR3 pos, CEnemy::TYPE type);
	static float GetDamage() { return m_AllDamage; } // �󂯂��_���[�W�̎擾
	static void ResetDamage() { m_AllDamage = 0.0f; } // �󂯂��_���[�W�̃��Z�b�g

protected:

	//�����o�֐�
	void RotateToMove(); // �ړ�����������
	void RotateToPlayer(); // �v���C���[������
	virtual void Attacked(); // �팂���̏���

	// �����o�ϐ�
	float m_fLife; // �̗�
	float m_fInvincible; // ���G����
	D3DXVECTOR3 m_posCenter; // �����ڂ̒��S

	// �ÓI�����o�ϐ�
	static float m_AllDamage; // �󂯂��_���[�W

private:

	//�����o�ϐ�
	CEnemy::TYPE m_type;

};

#endif
