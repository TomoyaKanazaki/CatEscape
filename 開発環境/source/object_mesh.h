//==========================================
//
//  メッシュオブジェクトクラス(object_mesh.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_MESH_H_
#define _OBJECT_MESH_H_
#include "object.h"

//==========================================
//  メッシュオブジェクトクラス定義
//==========================================
class CObject_Mesh : public CObject
{
public:

	enum TexPatern
	{
		NORMAL = 0, //繋がる
		LOOP, //連続
		MAX
	};

	typedef struct
	{
		int nNumMesh; //総分割数(プリミティブ数)
		int nNumMesh_U; //横の分割数
		int nNumMesh_V; //縦の分割数
		int nNumVtx; //総頂点数
		int nNumVtx_U; //横の頂点数
		int nNumVtx_V; //縦の頂点数
		int nNumIdx; //総インデックス数
	}MeshData; //頂点情報系の構造体

	CObject_Mesh(int nPriority = 5); //コンストラクタ
	~CObject_Mesh(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	bool OnMesh(const D3DXVECTOR3 pos);
	bool OnMesh(const D3DXVECTOR3 pos, const D3DXVECTOR3 oldpos, D3DXVECTOR3 *pVecLine, D3DXVECTOR3 *pVecToPos);
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	void SetVtxPos(const D3DXVECTOR3 pos, const int nIdx);
	void SetColor(D3DXCOLOR col);
	void SetPatern(TexPatern patern) { m_Patern = patern; }
	void AddTexPos(D3DXVECTOR2 texpos);
	void SetOrbit(bool bOrbit) { m_bOrbit = bOrbit; }

	//静的メンバ関数
	static CObject_Mesh *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR2 uv);

protected:

	//メンバ変数
	MeshData m_Mesh; //メッシュ情報

private:

	//メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; //インデックスバッファ
	LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャ情報
	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
	D3DXCOLOR m_Color;
	TexPatern m_Patern;
	bool m_bOrbit; // 軌跡フラグ

	//メンバ関数
	void SetVtx(void);
	void SetIdx(void);
	void CalcData(void);
	bool CheckOnMesh(const D3DXVECTOR3 &posJudge, const D3DXVECTOR3 &posStart, const D3DXVECTOR3 &posEnd) const;

};

#endif
