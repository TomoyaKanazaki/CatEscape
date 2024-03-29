//==========================================
//
//  �X�e�B�b�N���肮��UI(stick.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _STICK_H_
#define _STICK_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CStick : public CObject2D
{
public:

	//�����o�֐�
	CStick(int nPriority = 7);
	~CStick();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CStick* Create();

private:

};

#endif
