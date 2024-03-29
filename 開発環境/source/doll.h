//==========================================
//
//  �}�l�L���N���X(doll.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _DOLL_H_
#define _DOLL_H_
#include "object_char.h"

//==========================================
//  �N���X��`
//==========================================
class CDoll : public CObject_Char
{
public:

	//�����o�֐�
	CDoll(int nPriority = 4); //�R���X�g���N�^
	~CDoll(); //�f�X�g���N�^

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Dash(void);

	//�ÓI�����o�֐�
	static CDoll* Create(D3DXVECTOR3 pos);

};

#endif
