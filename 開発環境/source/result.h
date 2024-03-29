//==========================================
//
//  ���U���g���b�Z�[�W(result.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CResult : public CObject3D
{
public:

	//�����o�֐�
	CResult(int nPriority = 7);
	~CResult();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CResult* Create();

private:

};

#endif
