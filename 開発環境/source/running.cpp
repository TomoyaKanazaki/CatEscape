//==========================================
//
//  人形クラス(running.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "running.h"
#include "motion.h"
#include "scenemanager.h"
#include "manager.h"
#include "gametime.h"
#include "sound.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 LEFT_POS = D3DXVECTOR3(-2400.0f, 0.0f, 0.0f); // 左端
	const D3DXVECTOR3 RIGHT_POS = D3DXVECTOR3(2400.0f, 0.0f, 0.0f); // 右端
	const float PLAYER_SPEED = 250.0f; // プレイヤーの移動速度
}

//==========================================
//  コンストラクタ
//==========================================
CRunning::CRunning(int nPriority) : CObject_Char(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CRunning::~CRunning()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CRunning::Init(void)
{
	//タイプの設定
	SetType(TYPE_PLAYER);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	//初期化処理
	HRESULT hr = CObject_Char::Init();

	//モーション情報にモデルを渡す
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_WAIT);
	m_pMotion->Set(CMotion::PLAYER_WALK);

	// 移動用情報を設定
	if (CSceneManager::GetClear())
	{
		// 勝利時は左スタート
		m_pos = LEFT_POS;
		m_move = D3DXVECTOR3(PLAYER_SPEED, 0.0f, 0.0f);
	}
	else
	{
		// 敗北時は右スタート
		m_pos = RIGHT_POS;
		m_move = D3DXVECTOR3(-PLAYER_SPEED, 0.0f, 0.0f);
	}

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CRunning::Uninit(void)
{
	CObject_Char::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CRunning::Update(void)
{
	// 移動量を加算
	m_pos += m_move * CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// 方向
	Rotate();

	// 端位置を超えたら遷移する
	if (m_pos.x < LEFT_POS.x || m_pos.x > RIGHT_POS.x)
	{
		CManager::GetInstance()->GetInstance()->GetSceneManager()->SetNext(CSceneManager::TITLE);
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_END);
	}

	CObject_Char::Update();
}

//==========================================
//  描画処理
//==========================================
void CRunning::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  移動処理
//==========================================
void CRunning::Dash(void)
{
	//位置を保存
	D3DXVECTOR3 pos = m_pos;
	m_pos *= -1.0f;
}

//==========================================
//  生成処理
//==========================================
CRunning* CRunning::Create()
{
	//インスタンス生成
	CRunning* pDoll = new CRunning;

	//初期化処理
	pDoll->Init();

	return pDoll;
}

//==========================================
//  方向転換
//==========================================
void CRunning::Rotate()
{
	//ローカル変数宣言
	float fRotMove = m_rot.y; //現在の角度
	float fRotDest = 0.0f; //目標の角度
	float fRotDiff = 0.0f; //目標と現在の角度の差

	//右に進む時は右を向く
	if (m_move.x > 0.0f)
	{
		fRotDest = -D3DX_PI * 0.5f;
	}

	//左に進むときは左を向く
	if (m_move.x < 0.0f)
	{
		fRotDest = D3DX_PI * 0.5f;
	}

	//移動補正
	fRotDiff = fRotDest - fRotMove;	//目標までの移動方向の差分

	//角度の補正
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff += (-D3DX_PI * 2);
	}
	else if (fRotDiff <= -D3DX_PI)
	{
		fRotDiff += (D3DX_PI * 2);
	}

	//方向転換
	m_rot.y += fRotDiff * 0.2f;

	//角度の補正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += (-D3DX_PI * 2);
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += (D3DX_PI * 2);
	}
}
