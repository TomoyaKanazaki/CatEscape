//==========================================
//
//  �̗͕\��(bosslife.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BOSS_LIFE_H_
#define _BOSS_LIFE_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CBossLife : public CObject2D
{
public:

	//�����o�֐�
	CBossLife(int nPriority = 7);
	~CBossLife();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	bool GetDeath() { return m_bDead; }

	//�ÓI�����o�֐�
	static CBossLife* Create();

private:

	// �����o�֐�
	void ClacSize();

	// �����o�ϐ�
	D3DXVECTOR3 m_sizeDest; // �ڕW�̃T�C�Y
	float m_fLife; // �̗�
	bool m_bDead; // �I���t���O

};

#endif
