//==========================================
//
//  床(field.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "object_mesh.h"

//==========================================
//  クラス定義
//==========================================
class CFeild : public CObject_Mesh
{
public:

	enum type
	{
		WATER = 0, //水
		SOIL, //土
		MAX
	};

	//メンバ関数
	CFeild(int nPriority = 0);
	~CFeild();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	//静的メンバ関数
	static CFeild* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR2 uv, type type);

private: 

	//メンバ変数
	type m_type;

};

#endif
