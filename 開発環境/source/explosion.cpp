//==========================================
//
//  弾クラス(explosion.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "gamemanager.h"
#include "player.h"
#include "gametime.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 EXPLOSION_SIZE = D3DXVECTOR3(150.0f, 150.0f, 200.0f); // サイズ
	const float MOVE_SPEED = 300.0f; // 弾速
	const float HIT_LENGTH = 50.0f; // 当たり判定距離
}

//==========================================
//  コンストラクタ
//==========================================
CExplosion::CExplosion(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CExplosion::~CExplosion()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CExplosion::Init(void)
{
	// サイズを設定
	m_size = EXPLOSION_SIZE;

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::EXPLOSION));

	// アニメーションを設定
	SetAnim(10, 2, false, TYPE_U);

	return CObject3D_Anim::Init();
}

//==========================================
//  終了処理
//==========================================
void CExplosion::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CExplosion::Update(void)
{
	// 当たり判定
	Hit();

	CObject3D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CExplosion::Draw(void)
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
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

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
CExplosion* CExplosion::Create(const D3DXVECTOR3& pos)
{
	// インスタンス生成
	CExplosion* pExplosion = new CExplosion;

	// NULLチェック
	if (pExplosion == nullptr) { return nullptr; }

	// 位置を設定
	pExplosion->m_pos = pos;

	// 初期化処理
	pExplosion->Init();

	return pExplosion;
}

//==========================================
//  当たり判定
//==========================================
void CExplosion::Hit()
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
	}
}
