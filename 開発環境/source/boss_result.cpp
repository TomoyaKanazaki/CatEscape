//==========================================
//
//  ボスクラス(boss.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss_result.h"
#include "model.h"
#include "motion.h"
#include "orbit.h"
#include "resultmanager.h"
#include "camera.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float POSR_DISTANCE = 100.0f; // カメラの注視点からの距離
}

//==========================================
//  コンストラクタ
//==========================================
CBossResult::CBossResult(int nPriority)
{
	m_pOrbit[0] = m_pOrbit[1] = nullptr;
}

//==========================================
//  デストラクタ
//==========================================
CBossResult::~CBossResult()
{
}

//==========================================
//  初期化処理
//==========================================
HRESULT CBossResult::Init(void)
{
	// タイプの設定
	SetType(TYPE_ENEMY);

	// 階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::ENEMY_BOSS);

	// 初期化
	HRESULT hr = CObject_Char::Init();

	// セットアップ
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::BOSS_POP);

	// 剣に軌跡を付ける
	if (m_pOrbit[0] == nullptr)
	{
		m_pOrbit[0] = COrbit::Create(m_ppModel[4], D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, -115.0f), 10);
		m_pOrbit[0]->SwitchDraw(false);
	}
	if (m_pOrbit[1] == nullptr)
	{
		m_pOrbit[1] = COrbit::Create(m_ppModel[5], D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, -115.0f), 10);
		m_pOrbit[1]->SwitchDraw(false);
	}

	// モーションを設定
	m_pMotion->Set(CMotion::BOSS_ATTACK);

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CBossResult::Uninit(void)
{
	// 軌跡の終了
	for (int i = 0; i < 2; ++i)
	{
		if (m_pOrbit[i] != nullptr)
		{
			m_pOrbit[i]->Uninit();
			m_pOrbit[i] = nullptr;
		}
	}

	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBossResult::Update(void)
{
	// 位置を変更
	m_pos = CResultManager::GetCamera()->GetPosR();
	m_pos.x += POSR_DISTANCE;

	// 軌跡
	for (int i = 0; i < 2; ++i)
	{
		if (m_pOrbit[i] != nullptr)
		{
			m_pOrbit[i]->SwitchDraw(true);
		}
	}

	// 左を向く
	m_rot.y = D3DX_PI * 0.5f;

	CEnemy::Update();
}

//==========================================
//  描画処理
//==========================================
void CBossResult::Draw(void)
{
	CEnemy::Draw();
}
