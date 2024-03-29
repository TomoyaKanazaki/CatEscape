//==========================================
//
//  �e�N���X(bullet.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "object3D_Anim.h"

//==========================================
//  �N���X��`
//==========================================
class CBullet : public CObject3D_Anim
{
public:

	// �����o�֐�
	CBullet(int nPriority = 6);
	~CBullet();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// �ÓI�����o�֐�
	static CBullet* Create(const D3DXVECTOR3& pos);

private:

	// �����o�֐�
	void SetMove(); // �ړ��ʂ̐ݒ�
	void Hit(); // �����蔻��

	// �����o�ϐ�
	D3DXVECTOR3 m_target; // ���e�ڕW�n�_

};

#endif
