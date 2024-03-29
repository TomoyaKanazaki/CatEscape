//==========================================
//
//  体力表示(enemylife.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemylife.h"
#include "manager.h"
#include "gamemanager.h"
#include "enemymanager.h"
#include "manager.h"
#include "enemy.h"
#include "texture.h"
#include "renderer.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 LIFE_SIZE = D3DXVECTOR3(100.0f, 80.0f, 0.0f);
	const D3DXVECTOR3 LIFE_RIGHT_POS = D3DXVECTOR3(FLOAT_SCREEN_WIDTH - 30.0f, 50.0f, 0.0f);
	const float LIFE_SCALE = 20.0f; // 自身が表す体力の量
	const float SAB_SCALE = 0.1f; // サイズの減少倍率
}

//==========================================
//  静的メンバ変数宣言
//==========================================
int CEnemyLife::m_nNum = 0; // 体力

//==========================================
//  コンストラクタ
//==========================================
CEnemyLife::CEnemyLife(int nPriority) : CObject2D(nPriority),
m_nIdx(m_nNum)
{
	++m_nNum;
}

//==========================================
//  デストラクタ
//==========================================
CEnemyLife::~CEnemyLife()
{
	--m_nNum;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemyLife::Init(void)
{
	// サイズを設定
	m_size = LIFE_SIZE;

	// 位置を設定
	m_pos = LIFE_RIGHT_POS;
	m_pos.x -= LIFE_SIZE.x * m_nIdx;

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::FLAME));

	return CObject2D::Init();
}

//==========================================
//  終了処理
//==========================================
void CEnemyLife::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemyLife::Update(void)
{
	// 0を下回ったら削除
	if (m_size.x <= 0.0f)
	{
		Uninit();
		return;
	}

	// 大きさの更新
	ClacSize();

	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemyLife::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//描画
	CObject2D::Draw();

	//アルファブレンディングの設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  生成処理
//==========================================
CEnemyLife* CEnemyLife::Create()
{
	// インスタンス生成
	CEnemyLife* pLife = new CEnemyLife;

	// 初期化処理
	pLife->Init();

	return pLife;
}

//==========================================
//  大きさの計算処理
//==========================================
void CEnemyLife::ClacSize()
{
	// ボスのライフを取得
	float fLife = CGameManager::GetEnemy()->GetBoss()->GetLife();

	// ボスの体力から自身の目標サイズを算出する
	fLife -= LIFE_SCALE * m_nIdx;
	if (fLife > LIFE_SCALE)
	{
		fLife = LIFE_SCALE;
	}
	fLife /= LIFE_SCALE;

	// 目標サイズを適用する
	m_sizeDest = LIFE_SIZE * fLife;

	// 目標サイズと現在のサイズの差分を算出
	D3DXVECTOR3 diff = m_sizeDest - m_size;

	// 差分 * 倍率分サイズを小さくする
	m_size += diff * SAB_SCALE;
}
