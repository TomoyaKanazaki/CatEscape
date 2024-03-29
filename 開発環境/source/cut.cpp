//==========================================
//
//  斬られたポリゴン(cut.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "cut.h"
#include "cut_polygon.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CCut::m_fSpeed = 3.0f;

//==========================================
//  コンストラクタ
//==========================================
CCut::CCut()
{
	tex = nullptr;
	m_nPattern = 1;
}

//==========================================
//  デストラクタ
//==========================================
CCut::~CCut()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCut::Init(void)
{
	//生成するポリゴンの移動方向を決定
	D3DXVECTOR3 move;
	while (1)
	{
		//乱数生成
		move = D3DXVECTOR3((float)rand(), (float)rand(), 0.0f);

		//正規化
		D3DXVec3Normalize(&move, &move);

		if (move.y != 0.0f)
		{
			break;
		}
	}

	//生成する座標を決定
	D3DXVECTOR3 posUp = m_pos, posDawn = m_pos;
	posUp.y += m_size.y * 0.25f;
	posDawn.y -= m_size.y * 0.25f;

	//生成するポリゴンのサイズ
	D3DXVECTOR3 size = D3DXVECTOR3(m_size.x, m_size.y * 0.5f, m_size.z);

	//ポリゴンを生成する
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (move.y > 0.0f)
		{
			CCutPolygon::Create(posUp, size, move, tex, m_nPattern);
		}
		if (move.y < 0.0f)
		{
			CCutPolygon::Create(posDawn, size, move, tex, m_nPattern);
		}
		move *= -1.0f;
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CCut::Uninit(void)
{
	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CCut::Update(void)
{
	Uninit();
}

//==========================================
//  描画処理
//==========================================
void CCut::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CCut* CCut::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex, int nPattern)
{
	//インスタンス生成
	CCut* pCut = new CCut;

	//値を設定
	pCut->m_pos = pos;
	pCut->m_size = size;
	pCut->tex = tex;
	pCut->m_nPattern = nPattern;

	//初期化処理
	pCut->Init();

	return pCut;
}
