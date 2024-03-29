//==========================================
//
//  �{�X�N���X(boss_result.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_RESULT_H_
#define _BOSS_RESULT_H_
#include "enemy.h"

//==========================================
//  �O���錾
//==========================================
class COrbit;

//==========================================
//  �N���X��`
//==========================================
class CBossResult : public CEnemy
{
public:

	//�����o�֐�
	CBossResult(int nPriority = 5);
	~CBossResult();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	// �����o�ϐ�
	COrbit* m_pOrbit[2]; // ���̋O�Ճ|�C���^

};

#endif
