//==========================================
//
//  ナンバークラス(number.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//==========================================
//  コンストラクタ
//==========================================
CNumber::CNumber(int nPriority) : CObject2D(nPriority)
{
	m_nNumber = 0;
}

//==========================================
//  デストラクタ
//==========================================
CNumber::~CNumber()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CNumber::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	//タイプの設定
	SetType(TYPE_NUMBER);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CNumber::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CNumber::Update(void)
{
	//ローカル変数宣言
	D3DXVECTOR2 min, max;

	//表示する値にテクスチャ座標を合わせる
	min = D3DXVECTOR2(m_nNumber * 0.1f, 0.0f);
	max = D3DXVECTOR2(min.x + 0.1f, 1.0f);

	//テクスチャ座標を割り当てる
	SetTex(min, max);
}

//==========================================
//  描画処理
//==========================================
void CNumber::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CNumber * CNumber::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot, int nNumber)
{
	//インスタンス生成
	CNumber *pNumber = NULL;

	//NULLチェック
	if (pNumber == NULL)
	{
		//メモリを確保
		pNumber = new CNumber;
	}

	//値を割り当てる
	pNumber->m_nNumber = nNumber;
	pNumber->m_pos = pos;
	pNumber->m_size = size;
	pNumber->m_rot = rot;

	//初期化
	if (pNumber != NULL)
	{
		pNumber->Init();
	}

	//テクスチャを割り当てる
	pNumber->BindTexture(CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::NUMBER));

	//ポインタを返す
	return pNumber;
}
