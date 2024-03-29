//==========================================
//
//  弾クラス(bullet.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "gamemanager.h"
#include "player.h"
#include "gametime.h"
#include "explosion.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 BULLET_SIZE = D3DXVECTOR3(150.0f, 150.0f, 200.0f); // サイズ
	const float POS_ERROR = 10.0f; // 目標地点との誤差許容範囲
	const float MOVE_SPEED = 300.0f; // 弾速
	const float HIT_LENGTH = 50.0f; // 当たり判定距離
}

//==========================================
//  コンストラクタ
//==========================================
CBullet::CBullet(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CBullet::~CBullet()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBullet::Init(void)
{
	// サイズを設定
	m_size = BULLET_SIZE;

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::BULLET));

	// 色の変更
	m_col.r = 0.5f;
	m_col.g = 0.0f;

	// アニメーションを設定
	SetAnim(60, 1, true, TYPE_U);

	// 目標地点を設定
	m_target = CGameManager::GetPlayer()->GetCenterPos();

	return CObject3D_Anim::Init();
}

//==========================================
//  終了処理
//==========================================
void CBullet::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBullet::Update(void)
{
	// デルタタイムの取得
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// 移動量の設定
	SetMove();

	// 移動量の適用
	m_pos += m_move;

	// 攻撃判定
	Hit();

	CObject3D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CBullet::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);\

	CObject3D_Anim::Draw();

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CBullet* CBullet::Create(const D3DXVECTOR3& pos)
{
	// インスタンス生成
	CBullet* pBullet = new CBullet;

	// NULLチェック
	if (pBullet == nullptr) { return nullptr; }

	// 位置を設定
	pBullet->m_pos = pos;

	// 初期化処理
	pBullet->Init();

	return pBullet;
}

//==========================================
//  移動量の設定
//==========================================
void CBullet::SetMove()
{
	// 目標位置と現在位置を結ぶベクトルを作成する
	D3DXVECTOR3 vec = m_target - m_pos;

	// 破棄
	if (POS_ERROR * POS_ERROR >= vec.x * vec.x + vec.y * vec.y)
	{
		CExplosion::Create(m_pos);
		Uninit();
	}

	// 移動量を目標位置に向ける
	vec *= m_fDeltaTime;

	// 移動量を適用
	m_move = vec;
}

//==========================================
//  当たり判定
//==========================================
void CBullet::Hit()
{
	// プレイヤーの位置を取得
	D3DXVECTOR3 pos = CGameManager::GetPlayer()->GetCenterPos();

	// プレイヤーまでのベクトルを算出
	D3DXVECTOR3 vec = pos - m_pos;

	// 攻撃範囲内ならヒットする
	if (vec.x * vec.x + vec.y * vec.y < HIT_LENGTH * HIT_LENGTH)
	{
		// ヒット時の処理を呼ぶ
		CGameManager::GetPlayer()->Attacked();

		// 自身も終了する
		CExplosion::Create(m_pos);
		Uninit();
	}
}
