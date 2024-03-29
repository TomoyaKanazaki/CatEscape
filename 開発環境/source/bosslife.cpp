//==========================================
//
//  体力表示(bosslife.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bosslife.h"
#include "manager.h"
#include "gamemanager.h"
#include "enemymanager.h"
#include "manager.h"
#include "enemy.h"
#include "texture.h"
#include "renderer.h"
#include "input.h"
#include "rush_effect.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 LIFE_SIZE = D3DXVECTOR3(500.0f, 400.0f, 0.0f);
	const D3DXVECTOR3 LIFE_POS = D3DXVECTOR3(FLOAT_SCREEN_WIDTH - LIFE_SIZE.x * 0.5f, FLOAT_SCREEN_HEIGHT - LIFE_SIZE.y * 0.5f, 0.0f);
	const float MAX_LIFE = 30.0f; // 自身が表す体力の量
	const float SAB_SCALE = 0.1f; // サイズの減少倍率
}

//==========================================
//  コンストラクタ
//==========================================
CBossLife::CBossLife(int nPriority) : CObject2D(nPriority),
m_fLife(30.0f),
m_bDead(false)
{
}

//==========================================
//  デストラクタ
//==========================================
CBossLife::~CBossLife()
{
}

//==========================================
//  初期化処理
//==========================================
HRESULT CBossLife::Init(void)
{
	// サイズを設定
	m_size = LIFE_SIZE;

	// 位置を設定
	m_pos = LIFE_POS;

	// 初期化処理
	HRESULT hr = CObject2D::Init();

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::FLAME));

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CBossLife::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBossLife::Update(void)
{
	// 0を下回ったらフラグ
	if (m_fLife <= 0.0f)
	{
		m_bDead = true;
		return;
	}

	// ダメージ受ける
	if (CManager::GetInstance()->GetJoyPad()->GetStickTriggerR(CJoyPad::STICK_ALL))
	{
		m_fLife -= 1.0f;
	}

	// 演出を呼ぶ
	if (m_fLife <= 0.0f)
	{
		CRush::Create();
	}

	// 大きさの更新
	ClacSize();

	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CBossLife::Draw(void)
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
CBossLife* CBossLife::Create()
{
	// インスタンス生成
	CBossLife* pLife = new CBossLife;

	// 初期化処理
	pLife->Init();

	return pLife;
}

//==========================================
//  大きさの計算処理
//==========================================
void CBossLife::ClacSize()
{
	// 目標サイズを適用する
	m_sizeDest = LIFE_SIZE * (m_fLife / MAX_LIFE);

	// 目標サイズと現在のサイズの差分を算出
	D3DXVECTOR3 diff = m_sizeDest - m_size;

	// 差分 * 倍率分サイズを小さくする
	m_size += diff * SAB_SCALE;
}
