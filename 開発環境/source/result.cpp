//==========================================
//
//  ロゴ(result.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "scenemanager.h"
#include "resultmanager.h"
#include "camera.h"
#include "debugproc.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 RESULT_SIZE = D3DXVECTOR3(440.0f, 90.0f, 0.0f); // ポリゴンの大きさ
}

//==========================================
//  コンストラクタ
//==========================================
CResult::CResult(int nPriority)
{
}

//==========================================
//  デストラクタ
//==========================================
CResult::~CResult()
{
}

//==========================================
//  初期化処理
//==========================================
HRESULT CResult::Init(void)
{
	// テクスチャ割り当て
	if (CSceneManager::GetClear())
	{
		BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::CLEAR));
	}
	else
	{
		BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::OVER));
	}

	// サイズの設定
	m_size = RESULT_SIZE;

	// 位置を設定
	m_pos = CResultManager::GetCamera()->GetPosR();

	// ビルボードの設定
	SwitchBillboard(true);

	return CObject3D::Init();
}

//==========================================
//  終了処理
//==========================================
void CResult::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CResult::Update(void)
{
	// 位置を設定
	m_pos = CResultManager::GetCamera()->GetPosR();

	// デバッグ表示
	DebugProc::Print("\nポリゴン位置 : %f, %f\n\n", m_pos.x, m_pos.y);

	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CResult::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CObject3D::Draw();

	//Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//==========================================
//  生成処理
//==========================================
CResult* CResult::Create(void)
{
	// インスタンス生成
	CResult* pResult = new CResult;

	// 初期化処理
	pResult->Init();

	return pResult;
}
