//==========================================
//
//  ���f���N���X(model.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MODEL_H_
#define _MODEL_H_

//==========================================
//  �}�N����`
//==========================================
#define MAX_MODEL (64) //���f���̍ő吔

//==========================================
//  ���f���N���X��`
//==========================================
class CModel
{
public:
	//���f���\���̒�`
	typedef struct
	{
		LPDIRECT3DTEXTURE9 *pTexture; //�}�e���A���Ɏg�p����e�N�X�`��
		LPD3DXMESH pMesh; //���_���
		LPD3DXBUFFER pBuffMat; //�}�e���A���o�b�t�@
		DWORD dwNumMat; //�}�e���A����
		D3DXMATRIX mtxWorld; //���[���h�}�g���b�N�X
	}MODEL;

	CModel(); //�R���X�g���N�^
	~CModel(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTransform(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot) { m_pos += pos; m_rot = rot; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCol(const D3DXCOLOR& col) { m_ChangeMat.Diffuse = col; }
	CModel *GetParent(void) { return m_pParent; }
	D3DXMATRIX GetMtx(void) { return m_Info.mtxWorld; }
	D3DXCOLOR GetCol(void) const { return m_ChangeMat.Diffuse; }
	void ChangeCol(bool bValue = false) { m_bChangeCol = bValue; }
	void ResetMaterial(); // �ύX��}�e���A���̏�����

	//�ÓI�����o�֐�
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nModelID, CModel *m_pParent = NULL);
	static HRESULT Load(void);
	static void UnLoad(void);
	static bool GetLoadState(void) { return m_bLoad; }
	static int GetNum(void) { return m_nNum; }

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	MODEL m_Info;
	CModel *m_pParent; //�e���f���ւ̃|�C���^
	int m_nSelfID;
	D3DMATERIAL9 m_ChangeMat; // �ύX��̐F

	//�ÓI�����o�ϐ�
	static int m_nNumAll; 
	static MODEL m_Model[MAX_MODEL];
	static char m_sFilePass[MAX_MODEL][128];
	static bool m_bLoad;
	static int m_nNum;
	bool m_bChangeCol; // �F�ύX�t���O

};

#endif
