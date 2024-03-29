//==========================================
//
//  ����(build.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BUILD_H_
#define _BUILD_H_
#include "object_char.h"

//==========================================
//  �N���X��`
//==========================================
class CBuild : public CObject_Char
{
public:

	//�����o�֐�
	CBuild(int nPriority = 4);
	~CBuild();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CBuild* Create(void);
};

#endif
