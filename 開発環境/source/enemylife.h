//==========================================
//
//  �̗͕\��(enemylife.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_LIFE_H_
#define _ENEMY_LIFE_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemyLife : public CObject2D
{
public:

	//�����o�֐�
	CEnemyLife(int nPriority = 7);
	~CEnemyLife();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CEnemyLife* Create();

private:

	// �����o�֐�
	void ClacSize();

	// �����o�ϐ�
	int m_nIdx; // �̗͔ԍ�
	D3DXVECTOR3 m_sizeDest; // �ڕW�̃T�C�Y

	// �ÓI�����o�ϐ�
	static int m_nNum; // ������

};

#endif
