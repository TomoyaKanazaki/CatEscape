//==========================================
//
//  �a��ꂽ�|���S��(cut.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CUT_H_
#define _CUT_H_
#include "object.h"

//==========================================
//  �N���X��`
//==========================================
class CCut : public CObject
{
public:

	//�����o�֐�
	CCut();
	~CCut();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CCut* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex, int nPattern = 1);

private:

	//�����o�ϐ�
	LPDIRECT3DTEXTURE9 tex;
	int m_nPattern;

	//�萔��`
	static const float m_fSpeed;
};

#endif
