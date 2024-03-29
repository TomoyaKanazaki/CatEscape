//==========================================
//
//  カメラクラス(camera.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "debugproc.h"
#include "gamemanager.h"

//==========================================
//  コンストラクタ
//==========================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_diff = D3DXVECTOR3(0.0f, R_HEIGHT, CAMERA_DISTANCE);
	m_fFov = DEFAULT_FAV;
	m_bDebug = false;
}

//==========================================
//  デストラクタ
//==========================================
CCamera::~CCamera()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCamera::Init(void)
{
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CCamera::Uninit(void)
{

}

//==========================================
//  更新処理
//==========================================
void CCamera::Update(void)
{
	DebugProc::Print("視点 : ( %f, %f, %f )\n", m_posV.x, m_posV.y, m_posV.z);
	DebugProc::Print("注視点 : ( %f, %f, %f )\n", m_posR.x, m_posR.y, m_posR.z);
}

//==========================================
//  設定処理
//==========================================
void CCamera::SetCamera(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成

	D3DXMatrixPerspectiveFovLH
	(
		&m_mtxProjection,
		D3DXToRadian(m_fFov),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		50000.0f
	);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスを計算
	CreateViewMatrix();

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//==========================================
//  ビューマトリックスの生成
//==========================================
D3DXMATRIX CCamera::CreateViewMatrix(void)
{
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスを作成
	D3DXMatrixLookAtLH
	(
		&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU
	);

	return m_mtxView;
}

//==========================================
//  一人称視点の操作
//==========================================
void CCamera::FirstPerson(void)
{
	//視点の値を更新
	m_rot.x += CManager::GetInstance()->GetInstance()->GetMouse()->GetMouseMove().x;
	m_rot.z += CManager::GetInstance()->GetInstance()->GetMouse()->GetMouseMove().y;

	//角度の補正
	if (m_rot.z > MAX_ROT)
	{
		m_rot.z = MAX_ROT;
	}
	if (m_rot.z < MIN_ROT)
	{
		m_rot.z = MIN_ROT;
	}
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}

	//角度を更新
	m_posR.x = m_posV.x + (sinf(m_rot.z) * cosf(m_rot.x)) * -CAMERA_DISTANCE;
	m_posR.y = m_posV.y + cosf(m_rot.z) * -CAMERA_DISTANCE;
	m_posR.z = m_posV.z - (sinf(m_rot.z) * sinf(m_rot.x)) * -CAMERA_DISTANCE;
}

//==========================================
//  三人称視点の操作
//==========================================
void CCamera::ThirdPerson(void)
{
	//注視点を更新
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	//視点の値を更新
	m_rot.y += CManager::GetInstance()->GetInstance()->GetMouse()->GetMouseMove().x;

	//角度の補正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	//視点を更新
	m_posV.x = posPlayer.x + (sinf(m_rot.y) * -CAMERA_DISTANCE);
	m_posV.y = posPlayer.y + R_HEIGHT;
	m_posV.z = posPlayer.z + (cosf(m_rot.y) * -CAMERA_DISTANCE);

	//注視点を更新
	m_posR.x = posPlayer.x - (sinf(m_rot.y) * -CAMERA_DISTANCE);
	m_posR.y = posPlayer.y;
	m_posR.z = posPlayer.z - (cosf(m_rot.y) * -CAMERA_DISTANCE);
}

//==========================================
//  移動
//==========================================
void CCamera::Move(void)
{
	//プレイヤーの座標を取得
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetPos();

	//プレイヤーにカメラを追従させる
	m_posV = pos;
	m_posR = pos;

	//プレイヤーからカメラを離す
	m_posV += m_diff;
	m_posR -= m_diff;
	m_posR.y = pos.y;
}

//==========================================
//  スクリーン内の判定
//==========================================
bool CCamera::OnScreen(const D3DXVECTOR3 pos) const
{
	// 返り値用の変数
	bool bIn = false;

	// スクリーン座標の取得
	D3DXVECTOR3 screenPos = WorldToScreen(pos);

	// 判定
	if (screenPos.x >= 0.0f && screenPos.x <= SCREEN_WIDTH &&
		screenPos.y >= 0.0f && screenPos.y <= SCREEN_HEIGHT &&
		screenPos.z < 1.0f)
	{
		bIn = true;
	}

	// 返す
	return bIn;
}

//==========================================
//  ワールド座標をスクリーン座標に変換
//==========================================
D3DXVECTOR3 CCamera::WorldToScreen(const D3DXVECTOR3& posWorld) const
{
	//ビューポートの設定
	D3DVIEWPORT9 vp = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f };

	//計算用変数宣言
	D3DXMATRIX mtxWorld; //ワールドマトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//スクリーン座標を算出
	D3DXVECTOR3 screenPos;
	D3DXVec3Project
	(
		&screenPos,
		&posWorld,
		&vp,
		&m_mtxProjection,
		&m_mtxView,
		&mtxWorld
	);

	// スクリーン座標
	return screenPos;
}

//==========================================
//  スクリーン座標をワールド座標に変換
//==========================================
//D3DXVECTOR3 CCamera::ScreenToWorld(const D3DXVECTOR3& posScreen) const
//{
//	// 変数宣言
//	D3DXVECTOR3 posWorld; // ワールド座標
//	float fZ;  // 射影空間でのZ値（0～1）
//	D3DXMATRIX mtxViewInv; // ビューマトリックスの逆
//	D3DXMATRIX mtxProjectionInv; // プロジェクションマトリックスの逆
//	D3DXMATRIX VP;
//	D3DXMATRIX InvViewport;
//	D3DXMatrixInverse(&mtxViewInv, NULL, &m_mtxView);
//	D3DXMatrixInverse(&mtxProjectionInv, NULL, &m_mtxProjection);
//	D3DXMatrixIdentity(&VP);
//	VP._11 = SCREEN_WIDTH * 0.5f;
//	VP._22 = -SCREEN_HEIGHT * 0.5f;
//	VP._41 = SCREEN_WIDTH * 0.5f;
//	VP._42 = SCREEN_HEIGHT * 0.5f;
//	D3DXMatrixInverse(&InvViewport, NULL, &VP);
//
//	// 逆変換
//	D3DXMATRIX tmp = InvViewport * mtxProjectionInv * mtxViewInv;
//	D3DXVec3TransformCoord(&posWorld, &D3DXVECTOR3(posScreen.x, posScreen.y, fZ), &tmp);
//
//	return posWorld;
//}
