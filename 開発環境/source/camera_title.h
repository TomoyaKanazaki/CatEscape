//==========================================
//
//  タイトルシーンのカメラ(camera_title.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_TITLE_H_
#define _CAMERA_TITLE_H_
#include "camera.h"

//==========================================
//  クラス定義
//==========================================
class CCameraTitle : public CCamera
{
public:

	//メンバ関数
	CCameraTitle();
	~CCameraTitle();

	HRESULT Init(void) override;
	void Update(void) override;

private:

};

#endif
