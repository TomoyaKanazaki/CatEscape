//==========================================
//
//  タイトルシーンのカメラ(camera_title.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera_title.h"
#include "player.h"
#include "manager.h"
#include "input.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 POS_V = D3DXVECTOR3(0.0f, 100.0f, -350.0f); // 視点位置
	const D3DXVECTOR3 POS_R = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 注視点位置
}

//==========================================
//  コンストラクタ
//==========================================
CCameraTitle::CCameraTitle()
{

}

//==========================================
//  デストラクタ
//==========================================
CCameraTitle::~CCameraTitle()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCameraTitle::Init(void)
{
	// 位置を設定
	m_posV = POS_V;
	m_posR = POS_R;

	return CCamera::Init();
}

//==========================================
//  更新処理
//==========================================
void CCameraTitle::Update(void)
{
	CCamera::Update();
}
