//==========================================
//
//  3D�|���S���̃G�t�F�N�g(effect3D.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _EFFECT_3D_H_
#define _EFFECT_3D_H_
#include "object3D.h"

//==========================================
//  �N���X��`
//==========================================
class CEffect3D : public CObject3D
{
public:

	// �����o�֐�
	CEffect3D(); // �R���X�g���N�^
	~CEffect3D(); // �f�X�g���N�^

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�֐�
	static CEffect3D* Create(D3DXVECTOR3 pos, bool BillBoard = false);

private:

};

#endif
