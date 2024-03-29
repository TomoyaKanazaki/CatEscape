//==========================================
//
//  �̗͕\���̊Ǘ��N���X(enemylifemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ENEMY_LIFE_MANAGER_H_
#define _ENEMY_LIFE_MANAGER_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CEnemyLifeManager : public CObject2D
{
public:

	//�����o�֐�
	CEnemyLifeManager(int nPriority = 7);
	~CEnemyLifeManager();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CEnemyLifeManager* Create();

private:

};

#endif
