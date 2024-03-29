//==========================================
//
//  ロゴ(logo.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "logo.h"
#include "manager.h"

//==========================================
//  コンストラクタ
//==========================================
CLogo::CLogo(int nPriority) : CObject2D(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CLogo::~CLogo()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CLogo::Init(void)
{
	return CObject2D::Init();
}

//==========================================
//  終了処理
//==========================================
void CLogo::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CLogo::Update(void)
{
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CLogo::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CLogo* CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::TEXTURE tex)
{
	//変数宣言
	CLogo* pLogo = nullptr;

	//メモリを確保
	pLogo = new CLogo;

	//値を保存
	pLogo->m_pos = pos;
	pLogo->m_size = size;

	//初期化
	pLogo->Init();

	//テクスチャを割り当て
	pLogo->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(tex));

	return nullptr;
}
