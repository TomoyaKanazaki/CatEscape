//==========================================
//
//  �{�X�N���X(boss.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "enemy.h"

//==========================================
//  �O���錾
//==========================================
class COrbit;

//==========================================
//  �N���X��`
//==========================================
class CBoss : public CEnemy
{
public:

	// �s�����
	enum ACTION
	{
		POP = 0, // �o�����
		MOVE, // �ړ����
		NEUTRAL, // �ҋ@���
		DEATH, // ���S���
		ATTACK, // �ʏ�U��
		DASH, // �ːi�U��
		BULLET, // �������U��
		RAIN, // �J�~�炵
		RUSH, // �Ƃǂ߂̘A��
		MAX
	};

	//�����o�֐�
	CBoss(int nPriority = 5);
	~CBoss();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	bool GetDeath() { return m_State == DEATH; }
	int GetState() { return (int)m_State; }

private:

	// �����o�֐�
	void Attacked() override;
	void Motion();
	void Move();
	void Rotate(); // �����]��
	void Neutral(); // �ҋ@���̎��̍s���𒊑I
	void AttackState(); // �U��
	void Shot(); // �������U��
	void Attack(); // �O�A�U��
	void Dash(); // �ːi�U��
	void Rain(); // �J�~�炵
	void Hit(); // �U������
	void MoveToPlayer(); // �v���C���[�Ɍ������Ĉړ����鏈��

	// �����o�ϐ�
	ACTION m_oldState; // �O����
	ACTION m_State; // �s�����
	float m_MoveTimer; // �ړ�����
	COrbit* m_pOrbit[2]; // ���̋O�Ճ|�C���^
	D3DXVECTOR3 m_TargetPos; // �ڕW�ʒu
	bool m_Wait; // �_�b�V���O�̑ҋ@�����t���O
	bool m_Dash; // �_�b�V�����t���O
	int m_nAttackKind; // �U���̎��
	bool m_bRain; // �J�~�炵�ǉ��t���O
	bool m_bRainWait; // �A���t���V�O�̈ړ������t���O
	int m_nBulletNum; // �e�̐�

};

#endif
