//==========================================
//
//  床(field.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CFeild::CFeild(int nPriority) : CObject_Mesh(nPriority)
{
	m_type = MAX;
}

//==========================================
//  デストラクタ
//==========================================
CFeild::~CFeild()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CFeild::Init(void)
{
	return CObject_Mesh::Init();
}

//==========================================
//  終了処理
//==========================================
void CFeild::Uninit(void)
{
	CObject_Mesh::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CFeild::Update(void)
{
	//テクスチャ座標を更新
	if (m_type == WATER)
	{
		D3DXVECTOR2 tex = D3DXVECTOR2(0.003f, 0.0f);
		AddTexPos(tex);
	}

	CObject_Mesh::Update();
}

//==========================================
//  描画処理
//==========================================
void CFeild::Draw(void)
{
	CObject_Mesh::Draw();
}

//==========================================
//  生成処理
//==========================================
CFeild* CFeild::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, D3DXVECTOR2 uv, type type)
{
	//インスタンス生成
	CFeild* pField = NULL;

	//NULLチェック
	if (pField == NULL)
	{
		//メモリを確保
		pField = new CFeild;
	}

	if (pField == NULL)
	{
		return NULL;
	}

	//分割数を設定
	pField->m_Mesh.nNumMesh_U = (int)uv.x;
	pField->m_Mesh.nNumMesh_V = (int)uv.y;
	pField->m_pos = pos;
	pField->m_size = size;
	pField->m_rot = rot;
	pField->m_type = type;

	//初期化
	pField->Init();

	//テクスチャの割り当て
	switch (type)
	{
	case WATER:
		pField->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::WATER));
		break;
	case SOIL:
		pField->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::FIELD));
		break;
	}

	//ポインタを返す
	return pField;
}
