//==========================================
//
//  モデルクラス(model.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MODEL_H_
#define _MODEL_H_

//==========================================
//  マクロ定義
//==========================================
#define MAX_MODEL (64) //モデルの最大数

//==========================================
//  モデルクラス定義
//==========================================
class CModel
{
public:
	//モデル構造体定義
	typedef struct
	{
		LPDIRECT3DTEXTURE9 *pTexture; //マテリアルに使用するテクスチャ
		LPD3DXMESH pMesh; //頂点情報
		LPD3DXBUFFER pBuffMat; //マテリアルバッファ
		DWORD dwNumMat; //マテリアル数
		D3DXMATRIX mtxWorld; //ワールドマトリックス
	}MODEL;

	CModel(); //コンストラクタ
	~CModel(); //デストラクタ

	//メンバ関数
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
	void ResetMaterial(); // 変更後マテリアルの初期化

	//静的メンバ関数
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nModelID, CModel *m_pParent = NULL);
	static HRESULT Load(void);
	static void UnLoad(void);
	static bool GetLoadState(void) { return m_bLoad; }
	static int GetNum(void) { return m_nNum; }

private:

	//メンバ変数
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	MODEL m_Info;
	CModel *m_pParent; //親モデルへのポインタ
	int m_nSelfID;
	D3DMATERIAL9 m_ChangeMat; // 変更後の色

	//静的メンバ変数
	static int m_nNumAll; 
	static MODEL m_Model[MAX_MODEL];
	static char m_sFilePass[MAX_MODEL][128];
	static bool m_bLoad;
	static int m_nNum;
	bool m_bChangeCol; // 色変更フラグ

};

#endif
