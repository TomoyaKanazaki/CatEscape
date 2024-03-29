//==========================================
//
//  斬撃エフェクト(slash.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "slash.h"
#include "manager.h"
#include "renderer.h"
#include "gametime.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "slash_effect.h"
#include "splash.h"
#include "hit_effect.h"
#include "gamemanager.h"
#include "camera.h"
#include "input.h"
#include "camera_game.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 SLASH_SIZE = D3DXVECTOR3(800.0f, 5.0f, 0.0f); // ポリゴンサイズ
	const float CLEAR_TIME = 4.0f; // 1 / n 秒
	const float MIN_COLOR = 0.5f; // 色の下限
	const D3DXCOLOR EFFECT_COLOR[3] = { D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f) }; // エフェクトカラー
	const D3DXVECTOR3 EFFECT_SCALE = D3DXVECTOR3(0.5f, 10.0f, 0.0f); // エフェクトのスケール
}

//==========================================
//  コンストラクタ
//==========================================
CSlash::CSlash(int nPriority) : CObject3D_Anim(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CSlash::~CSlash()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CSlash::Init(void)
{
	// サイズを設定
	m_size = SLASH_SIZE;

	// ポリゴンの左端の座標を算出
	m_posLeft.x = m_pos.x + (cosf(m_rot.z) * (m_size.x * 0.5f));
	m_posLeft.y = m_pos.y + (sinf(m_rot.z) * (m_size.x * 0.5f));

	// ポリゴンの右端の座標を算出
	m_posRight.x = m_pos.x - (cosf(m_rot.z) * (m_size.x * 0.5f));
	m_posRight.y = m_pos.y - (sinf(m_rot.z) * (m_size.x * 0.5f));

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::EFFECT));

	// 色の設定
	m_col.r = 0.0f;
	m_col.g = ((float)rand() / (float)RAND_MAX) * (1.0f - MIN_COLOR) + MIN_COLOR;
	m_col.b = ((float)rand() / (float)RAND_MAX);

	// アニメーションを設定
	SetAnim(28, 2, false, TYPE_U);

	// 攻撃判定
	Hit();

	// エフェクトの発生
	for (int i = 0; i < 3; ++i)
	{
		CSlash_Effect::Create(m_pos, m_rot, EFFECT_COLOR[i]);
	}
	CSplash::Create(m_pos, m_rot, D3DXVECTOR3(m_size.x, m_size.y * EFFECT_SCALE.y, EFFECT_SCALE.z), m_col);

	// 初期化
	return CObject3D_Anim::Init();
}

//==========================================
//  終了処理
//==========================================
void CSlash::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CSlash::Update(void)
{
	// 完全に透過していた場合終了する
	if (m_col.a <= 0.0f)
	{
		Uninit();
		return;
	}

	// 不透明度を下げる
	m_col.a -= CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat() * 2.0f;

	// 更新する
	CObject3D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CSlash::Draw(void)
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

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//描画
	CObject3D_Anim::Draw();

	//アルファブレンディングの設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

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
CSlash* CSlash::Create(const D3DXVECTOR3 pos, const float rot)
{
	// インスタンス生成
	CSlash* pSlash = new CSlash;

	// NULLチェック
	if (pSlash == nullptr) { return nullptr; }

	// 値の設定
	pSlash->m_pos = pos;
	pSlash->m_rot.z = rot;

	// 初期化処理
	pSlash->Init();

	// 値を返す
	return pSlash;
}

//==========================================
//  敵との当たり判定
//==========================================
void CSlash::Hit()
{
	//当たり判定の生成
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//先頭のアドレスを取得
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject* pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_ENEMY) //敵の場合
			{
				if (pObj->GetObjState() == CObject::NORMAL) // 通常状態の場合
				{
					// 目標点を取得する
					D3DXVECTOR3 pos = pObj->GetCenterPos();

					if (CGameManager::GetCamera()->OnScreen(pos)) // 画面内の場合
					{
						// 始点から終点までのベクトルを求める
						D3DXVECTOR3 vecLine = m_posRight - m_posLeft;

						// 始点から目標点までのベクトルを求める
						D3DXVECTOR3 vecToPos = pos - m_posLeft;

						// 各ベクトルの大きさを求める
						float lengthLine = sqrtf((vecLine.x * vecLine.x) + (vecLine.y * vecLine.y));
						float lengthToPos = sqrtf((vecToPos.x * vecToPos.x) + (vecToPos.y * vecToPos.y));

						// 媒介変数tを求める
						float t = (lengthLine * lengthToPos) / (lengthLine * lengthLine);

						// 線分の判定
						if (0.0f <= t && t <= 1.0f)
						{
							// 目標点から直線に垂線を下した時の交点を求める
							D3DXVECTOR3 posCross = m_posLeft + (t * vecLine);

							// 交点から目標点までのベクトルを求める
							D3DXVECTOR3 vecToCross = pos - posCross;

							// 判定距離の比較
							if (pObj->GetHitLength() * pObj->GetHitLength() >= (vecToCross.x * vecToCross.x) + (vecToCross.y * vecToCross.y))
							{
								// 当たっていた時の演出系処理
								CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SLICE);
								pObj->SetState(CObject::ATTACKED);
								CHitEffect::Create((posCross + pos) * 0.5f);

								// バイブレーションの設定
								CManager::GetInstance()->GetJoyPad()->AddVibrationSpeed(USHRT_MAX);
								CManager::GetInstance()->GetJoyPad()->AddVibrationTimer(0.1f);

								// 画面揺れの設定
								CGameManager::GetCamera()->AddQuake(D3DXVECTOR3(1.0f, 1.0f, 0.0f), 0.05f);

								// ヒットストップ
								if (CManager::GetInstance()->GetGameTime()->GetTime() >= 0.0f)
								{
									CManager::GetInstance()->GetGameTime()->SetScaling(0.001f, 0.1f);
								}
								else
								{
									CManager::GetInstance()->GetGameTime()->AddTime(0.1f);
								}
							}
						}
					}
				}
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}
}
