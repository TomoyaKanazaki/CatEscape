//==========================================
//
//  �^�C�g���̃��S(title.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CTitle : public CObject3D
{
public:

	//�����o�֐�
	CTitle(int nPriority = 7);
	~CTitle();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void CutTitle(void);

	//�ÓI�����o�֐�
	static CTitle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

};

#endif
