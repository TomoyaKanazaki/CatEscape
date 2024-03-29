//==========================================
//
//  �X�e�B�b�N���肮��UI(stick_base.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _STICK_BASEE_H_
#define _STICK_BASEE_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CBase : public CObject2D
{
public:

	//�����o�֐�
	CBase(int nPriority = 6);
	~CBase();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CBase* Create(const D3DXVECTOR3& pos);

private:

};

#endif
