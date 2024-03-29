//==========================================
//
//  ロゴ(logo.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LOGO_H_
#define _LOGO_H_
#include "object2D.h"
#include "texture.h"

//==========================================
//  クラス定義
//==========================================
class CLogo : public CObject2D
{
public:

	//メンバ関数
	CLogo(int nPriority = 7);
	~CLogo();

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//静的メンバ関数
	static CLogo* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::TEXTURE tex);

private:

};

#endif
