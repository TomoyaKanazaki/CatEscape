//==========================================
//
//  ���e�N���X(blade.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BLADE_H_
#define _BLADE_H_
#include "object_char.h"

//==========================================
//  �O���錾
//==========================================
class COrbit;

//==========================================
//  �N���X��`
//==========================================
class CBlade : public CObject_Char
{
public:

	// �����o�֐�
	CBlade(int nPriority = 6);
	~CBlade();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�֐�
	static CBlade* Create(const D3DXVECTOR3& pos);

private:

	// �����o�֐�
	void SetMove(); // �ړ��ʂ̐ݒ�
	void Hit(); // �����蔻��

	// �����o�ϐ�
	float m_rotation;
	float m_Time;
	COrbit* m_pOrbit;

};

#endif
