//==========================================
//
//  �^�C�g���V�[���̃J����(camera_title.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_TITLE_H_
#define _CAMERA_TITLE_H_
#include "camera.h"

//==========================================
//  �N���X��`
//==========================================
class CCameraTitle : public CCamera
{
public:

	//�����o�֐�
	CCameraTitle();
	~CCameraTitle();

	HRESULT Init(void) override;
	void Update(void) override;

private:

};

#endif
