//==========================================
//
//  タイトルシーンのカメラ(camera_result.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_result.h"
#include "player.h"
#include "manager.h"
#include "input.h"
#include "resultmanager.h"
#include "running.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 POS_V = D3DXVECTOR3(0.0f, 0.0f, -350.0f); // 視点位置
	const D3DXVECTOR3 POS_R = D3DXVECTOR3(0.0f, 100.0f, 0.0f); // 注視点位置
	const float PLAYER_DISTANCE = 150.0f; // プレイヤーの後ろ方向距離
}

//==========================================
//  コンストラクタ
//==========================================
CCameraResult::CCameraResult()
{

}

//==========================================
//  デストラクタ
//==========================================
CCameraResult::~CCameraResult()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCameraResult::Init(void)
{
	return CCamera::Init();
}

//==========================================
//  更新処理
//==========================================
void CCameraResult::Update(void)
{
	Rotate();
	CCamera::Update();
}

//==========================================
//  回転
//==========================================
void CCameraResult::Rotate()
{
	//ローカル変数宣言
	D3DXVECTOR3 Pos = m_posR; //現在の位置
	D3DXVECTOR3 Dest = CResultManager::GetPlayer()->GetPos(); //目標の位置
	D3DXVECTOR3 Diff = {}; //目標と現在の位置の差
	D3DXVECTOR3 rot = CResultManager::GetPlayer()->GetRot(); //プレイヤーの方向
	float fDistance = -sinf(rot.y) * PLAYER_DISTANCE;

	//差分を調整
	Dest.x -= fDistance;

	//移動補正
	Diff = Dest - Pos;	//目標までの移動方向の差分

	//適用
	m_posR += Diff * 1.0f + POS_R;

	//視点を更新
	m_posV = m_posR + D3DXVECTOR3(0.0f, POS_V.y, POS_V.z);
}
