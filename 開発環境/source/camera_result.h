//==========================================
//
//  タイトルシーンのカメラ(camera_result.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_RESULT_H_
#define _CAMERA_RESULT_H_
#include "camera.h"

//==========================================
//  クラス定義
//==========================================
class CCameraResult : public CCamera
{
public:

	//メンバ関数
	CCameraResult();
	~CCameraResult();

	HRESULT Init(void) override;
	void Update(void) override;

private:

	// メンバ関数
	void Rotate();

};

#endif
