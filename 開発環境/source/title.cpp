//==========================================
//
//  タイトルのロゴ(title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "cut.h"

//==========================================
//  コンストラクタ
//==========================================
CTitle::CTitle(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CTitle::~CTitle()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTitle::Init(void)
{
	return CObject3D::Init();
}

//==========================================
//  終了処理
//==========================================
void CTitle::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTitle::Update(void)
{
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CTitle::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//カリングをオフ
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//描画
	CObject3D::Draw();

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//カリングをオン
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//==========================================
//  ポリゴンを斬る
//==========================================
void CTitle::CutTitle(void)
{
	CCut::Create(m_pos, m_size, m_pTexture);
	Uninit();
}

//==========================================
//  生成処理
//==========================================
CTitle* CTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンス生成
	CTitle *pTitle = new CTitle;

	//値を設定
	pTitle->m_pos = pos;
	pTitle->m_size = size;

	//初期化処理
	pTitle->Init();

	//テクスチャ割り当て
	pTitle->BindTexture(CManager::GetInstance()->GetTexture()->GetAddress(CTexture::TITLE));

	return pTitle;
}
