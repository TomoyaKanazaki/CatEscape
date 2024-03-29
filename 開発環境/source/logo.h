//==========================================
//
//  ���S(logo.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LOGO_H_
#define _LOGO_H_
#include "object2D.h"
#include "texture.h"

//==========================================
//  �N���X��`
//==========================================
class CLogo : public CObject2D
{
public:

	//�����o�֐�
	CLogo(int nPriority = 7);
	~CLogo();

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CLogo* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::TEXTURE tex);

private:

};

#endif
