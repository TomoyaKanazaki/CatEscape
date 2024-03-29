//==========================================
//
//  �O�ՃN���X(orbit.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _ORBIT_H_
#define _ORBIT_H_
#include "object.h"

//==========================================
//  �O���錾
//==========================================
class CModel;
class CObject_Mesh;

//==========================================
//  �O�ՃN���X��`
//==========================================
class COrbit : public CObject
{
public:
	COrbit(int nPriority = 5); //�R���X�g���N�^
	~COrbit(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SwitchDraw(bool bDraw) { m_bDraw = bDraw; }// �`��̗L��

	void GetForemostLine(D3DXVECTOR3* pos0, D3DXVECTOR3* pos1);

	//�ÓI�����o�֐�
	static COrbit *Create(CModel *pParent, D3DXCOLOR col, D3DXVECTOR3 offset0, D3DXVECTOR3 offset1, int nLife);

private:

	struct OFFSET
	{
		D3DXVECTOR3 pos;
		D3DXCOLOR col;
		D3DXMATRIX mtxWorld;
	};

	//�����o�֐�
	void CalcOffset(void); //�I�t�Z�b�g�̌v�Z����

	//�����o�ϐ�
	CModel *m_parent; //�Ǐ]���郂�f��
	OFFSET m_offset[2]; //�I�t�Z�b�g���
	OFFSET m_WindArea; //�����͈�
	D3DXVECTOR3 m_posWind[2]; //��������ʒu
	D3DXCOLOR m_colDef; //�����J���[
	D3DXVECTOR3 *m_pVtxPos; //���_���W
	int m_nLife; //���ݎ���
	int m_nNumVtx; //���_��
	CObject_Mesh *m_pMesh; //���b�V��
	float m_fLength; //���苗��
	bool m_bDraw; // ���Ńt���O

};

#endif
