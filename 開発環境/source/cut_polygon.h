//==========================================
//
//  �a��ꂽ�|���S��(cut_polygon.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CUT_POLYGON_H_
#define _CUT_POLYGON_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CCutPolygon : public CObject3D
{
public:

	//�����o�֐�
	CCutPolygon(int nPriority = 7);
	~CCutPolygon();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//�ÓI�����o�֐�
	static CCutPolygon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, LPDIRECT3DTEXTURE9 tex, int nPattern = 1);

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_move;
	int m_nPattern;

};

#endif
