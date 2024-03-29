//==========================================
//
//  ���}������(enemy_umbrella.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_UMBRELLA_H_
#define _ENEMY_UMBRELLA_H_
#include "enemy.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemy_Umbrella : public CEnemy
{
public:

	// �����o�֐�
	CEnemy_Umbrella();
	~CEnemy_Umbrella();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	// �����o�֐�
	void RotationLoop(); // ��葱����
	void Move(); // �ړ�
	bool CalcDistancePlayer(); // �v���C���[�Ƃ̋����𑪂�

	// �����o�ϐ�
	D3DXVECTOR3 m_posDefault; // �����ʒu
	float m_fMoveTime; // �ړ����Ă��鎞��
	bool m_bLook; // �v���C���[�����t���O

};

#endif
