//==========================================
//
//  �I�u�W�F�N�g�L�����N�^�[(object_char.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_CHAR_H_
#define _OBJECT_CHAR_H_
#include "object.h"
#include "layer.h"

//==========================================
//  �O���錾
//==========================================
class CModel;
class CMotion;

//==========================================
//  �N���X��`
//==========================================
class CObject_Char : public CObject
{
public:

	//�����o�֐�
	CObject_Char(int nPriority = 4);
	~CObject_Char();

	//�����o�֐�
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	float GetHitLength(void) override { return m_HitLenght; }
	D3DXVECTOR3 GetCenterPos() override { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

protected:

	// �����o�֐�
	void ChangeColor(bool bChange) { m_bChangeCol = bChange; };
	void WhiteOut(bool bChange) { m_bWhiteOut = bChange; }
	void CalcHitLength(const D3DXVECTOR3& size); // ���苗���̌v�Z

	//�����o�ϐ�
	CModel** m_ppModel; //���f�����
	CLayer::LAYERDATA* m_pLayer; //�K�w�\�����
	CMotion* m_pMotion;
	D3DXCOLOR m_col;

private:

	//�����o�ϐ�
	D3DXMATRIX m_mtxWorld;
	bool m_bChangeCol;
	bool m_bWhiteOut;
	float m_HitLenght; // ���苗��

};

#endif
