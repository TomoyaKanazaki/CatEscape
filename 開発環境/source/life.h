//==========================================
//
//  �̗͕\��(life.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LIFE_H_
#define _LIFE_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CLife : public CObject2D
{
public:

	//�����o�֐�
	CLife(int nPriority = 7);
	~CLife();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CLife* Create();

private:

	// �����o�ϐ�
	int m_nIdx; // �̗͔ԍ�

	// �ÓI�����o�ϐ�
	static int m_nNum; // ������

};

#endif
