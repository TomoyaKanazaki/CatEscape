//==========================================
//
//  �v���C���[�N���X(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "object_char.h"

//==========================================
//  �O���錾
//==========================================
class COrbit;

//==========================================
//  �v���C���[�N���X�̒�`
//==========================================
class CPlayer : public CObject_Char
{
public:

	//��Ԓ�`
	enum State
	{
		NEUTRAL = 0, // �ҋ@���
		WALK, // ���s���
		JUMP, // �W�����v���
		FALL, // �������
		IAI, // �������
		DEATH, // ���S���
		RUSH, // �A�����
		MAX
	};

	CPlayer(int nPriority = 4); //�R���X�g���N�^
	~CPlayer(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetCenterPos(void) override { return m_CenterPos; }
	bool GetDeath(void) { return m_State == DEATH ? true : false; }
	State GetState(void) { return m_State; }
	bool GetDash() const { return m_bDash; }
	float GetHitLength() const { return m_fHitLength; }
	void Attacked(); // �_���[�W���󂯂����̏���
	int GetLife() { return m_nLife; }
	void SetRand(bool rand) { m_bRand = rand; m_bDoubleJump = !rand; }

	//�ÓI�����o�֐�
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//�����o�֐�
	void Motion();
	void Limit();
	void Move();
	void Rotate();
	void Jump();
	void Gravity();
	void Damage();
	void Attack();
	void Dash();
	void Hit();

	//�����o�ϐ�
	D3DXVECTOR3 m_CenterPos; //���S���W
	D3DXVECTOR3 m_posStart; // �U���̃X�^�[�g�n�_
	float m_fDashAngle;
	bool m_bRand;
	bool m_bDoubleJump;
	bool m_bDash;
	D3DXMATERIAL *m_pDefMat;
	State m_State;
	State m_oldState;
	float m_fStateCounter; // ��ԑJ�ڂ��Ǘ�����^�C�}�[
	float m_AttackCoolTime; // �U���̃N�[���^�C��
	int m_AttackCounter; // �A���ōU��������
	bool m_bAttack; // �U���\�t���O
	COrbit* m_pOrbit;
	int m_nLife; // �̗�
	bool m_bDamage; // �_���[�W�t���O
	float m_fDamageCounter; // �_���[�W��Ԃ̃J�E���^
	float m_fHitLength; // �q�b�g�͈�

	//���f�����
	D3DXVECTOR3 m_oldposModel;

};

#endif
