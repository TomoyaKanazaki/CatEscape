//==========================================
//
//  ��(field.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "object_mesh.h"

//==========================================
//  �N���X��`
//==========================================
class CFeild : public CObject_Mesh
{
public:

	enum type
	{
		WATER = 0, //��
		SOIL, //�y
		MAX
	};

	//�����o�֐�
	CFeild(int nPriority = 0);
	~CFeild();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	//�ÓI�����o�֐�
	static CFeild* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR2 uv, type type);

private: 

	//�����o�ϐ�
	type m_type;

};

#endif
