//==========================================
//
//  ���U�G�t�F�N�g(splash.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SPLASH_H_
#define _SPLASH_H_
#include "object3D_Anim.h"

//==========================================
//  �N���X��`
//==========================================
class CSplash : public CObject3D_Anim
{
public:

	//�����o�֐�
	CSplash(int nPriority = 6);
	~CSplash();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�֐�
	static CSplash* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,const D3DXVECTOR3& size, const D3DXCOLOR& col);

private:

};

#endif
