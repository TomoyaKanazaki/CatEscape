//==========================================
//
//  �̗͕\���̊Ǘ��N���X(lifemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LIFE_MANAGER_H_
#define _LIFE_MANAGER_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CLifeManager : public CObject2D
{
public:

	//�����o�֐�
	CLifeManager(int nPriority = 7);
	~CLifeManager();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CLifeManager* Create();

private:

};

#endif
