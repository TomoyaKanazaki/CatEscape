//==========================================
//
//  �^�C�g���V�[���̃J����(camera_result.h)
//  Author : Chaba
//
//==========================================
#ifndef _CAMERA_RESULT_H_
#define _CAMERA_RESULT_H_
#include "camera.h"

//==========================================
//  �N���X��`
//==========================================
class CCameraResult : public CCamera
{
public:

	//�����o�֐�
	CCameraResult();
	~CCameraResult();

	HRESULT Init(void) override;
	void Update(void) override;

private:

	// �����o�֐�
	void Rotate();

};

#endif
