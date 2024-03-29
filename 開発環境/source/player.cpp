//==========================================
//
//  プレイヤークラス(player.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <windows.h>
#include "player.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "sound.h"
#include "debugproc.h"
#include "camera.h"
#include "model.h"
#include "motion.h"
#include "layer.h"
#include "gamemanager.h"
#include "camera.h"
#include "gametime.h"
#include "effect3D.h"
#include "orbit.h"
#include "slash.h"
#include "enemy.h"
#include "slash_effect.h"
#include "lifemanager.h"
#include "enemymanager.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float HIT_LENGTH = 25.0f; // 敵との接触に使う判定の大きさ
	const float ATTACK_SPEED = 1000.0f; // 攻撃時の移動速度
	const float ATTACK_TIME = 0.2f; // 攻撃に使用する時間
	const float PLAYER_SPEED = 350.0f; //プレイヤーの移動速度
	const float PLAYER_HEIGHT = 40.0f; //プレイヤーの高さ
	const float DASH_DISTANCE = 200.0f; //ダッシュの移動距離
	const float HIT_RANGE = 2020.0f; //ヒットする範囲
	const float JUMP_MOVE = 600.0f; //ジャンプ力
	const float GRAVITY = 1500.0f; //重力
	const int MAX_ATTACK_COUNT = 3; // 連続攻撃の最大数
	const float ATTACK_COOL_TIME = 0.2f; // 攻撃のクールタイム
	const float LIMIT_HEIGHT_NORMAL = 300.0f; // 道中の上昇限界
	const float LIMIT_HEIGHT_BOSS = 380.0f; // ボス戦中の上昇限界
	const float LIMIT_WIDTH_BOSS = 1350.0f; // ボス戦中の移動限界
	const int MAX_LIFE = 10; // 体力上限
	const float DAMAGE_TIME = 0.8f;
	const float DAMAGE_SPEED = 0.3f; // ダメージ状態中の移動倍率
	const D3DXCOLOR SLASH_COLOR = D3DXCOLOR(0.1f, 1.0f, 0.1f, 1.0f);
	const D3DXVECTOR3 ENEMY_DISTANCE = D3DXVECTOR3(-60.0f, -20.0f, 0.0f);
}

//==========================================
//  コンストラクタ
//==========================================
CPlayer::CPlayer(int nPriority) : CObject_Char(nPriority),
m_fStateCounter(0.0f),
m_AttackCoolTime(ATTACK_COOL_TIME),
m_AttackCounter(0),
m_bAttack(true),
m_posStart(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
m_pOrbit(nullptr),
m_nLife(MAX_LIFE),
m_bDamage(false),
m_fDamageCounter(0.0f),
m_fHitLength(HIT_LENGTH),
m_bDoubleJump(false)
{
	m_CenterPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDashAngle = 0.0f;
	m_bRand = true;
	m_bDash = false;
	m_oldposModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_State = NEUTRAL;
	m_oldState = NEUTRAL;
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
}

//==========================================
//  デストラクタ
//==========================================
CPlayer::~CPlayer()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CPlayer::Init(void)
{
	//タイプの設定
	SetType(TYPE_PLAYER);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	HRESULT hr = CObject_Char::Init();

	//モーション情報にモデルを渡す
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_WAIT);

	//中心座標を設定
	m_CenterPos = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	// 軌跡の生成
	if (m_pOrbit == nullptr)
	{
		m_pOrbit = COrbit::Create(m_ppModel[14], D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 30.0f, 3.0f), 6);
		m_pOrbit->SwitchDraw(false);
	}

	// 体力を表示
	CLifeManager::Create();

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CPlayer::Uninit(void)
{
	// 軌跡の終了
	if (m_pOrbit != nullptr)
	{
		m_pOrbit->Uninit();
		m_pOrbit = nullptr;
	}

	CObject_Char::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CPlayer::Update(void)
{
	// 前回座標に保存
	m_oldPos = m_pos;
	m_oldposModel = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	DebugProc::Print("プレイヤー位置 : ( %f, %f, %f )\n", m_pos.x, m_pos.y, m_pos.z);

	// 経過時間を取得する
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// 中心座標を設定
	m_CenterPos = D3DXVECTOR3(m_ppModel[3]->GetMtx()._41, m_ppModel[3]->GetMtx()._42, m_ppModel[3]->GetMtx()._43);

	// 留めを刺すとき
	if (CGameManager::GetState() == CGameManager::STATE_RUSH || CGameManager::GetState() == CGameManager::STATE_END)
	{
		// ラッシュ状態
		m_State = RUSH;

		// 向きを補正
		m_rot.y = -D3DX_PI * 0.5f;

		// 座標を補正
		m_pos = CGameManager::GetEnemy()->GetBoss()->GetCenterPos() + ENEMY_DISTANCE;

		// 右スティック入力があった場合
		if (CManager::GetInstance()->GetJoyPad()->GetStickTriggerR(CJoyPad::STICK_ALL))
		{
			// 攻撃の方向を算出する
			float rot = atan2f(rand() - (RAND_MAX * 0.5f), rand() - (RAND_MAX * 0.5f));

			// 攻撃を生成
			CSlash::Create(CGameManager::GetEnemy()->GetBoss()->GetCenterPos(), rot);
		}
	}
	else
	{
		// 攻撃
		if (CGameManager::GetState() != CGameManager::STATE_END)
		{
			if (CManager::GetInstance()->GetJoyPad()->GetPress(CJoyPad::BUTTON_RB) || m_State == IAI)
			{
				//Dash();
			}
			else
			{
				Attack();
			}

			// ジャンプ
			Jump();
		}

		// 移動の処理
		Move();

		// 回転の処理
		Rotate();

		// 移動制限
		Limit();

		// 重力
		Gravity();

		// ダメージ
		Damage();

		// 体力が0になったら死ぬ
		if (m_nLife == 0)
		{
			m_State = DEATH;
			ChangeColor(false);
		}
	}

	// モーション
	Motion();

	// 更新
	CObject_Char::Update();

	// 既にダメージ状態の時
	if (m_bDamage)
	{
		// ダメージ時間の加算
		m_fDamageCounter += m_fDeltaTime;

		// 一定時間が経過していたら
		if (m_fDamageCounter >= DAMAGE_TIME)
		{
			m_bDamage = false;
			ChangeColor(false);
		}
	}

#ifdef _DEBUG

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		m_pos.x = 1300.0f;
	}

#endif
}

//==========================================
//  描画処理
//==========================================
void CPlayer::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  攻撃を受けた時の処理
//==========================================
void CPlayer::Attacked()
{
	// 既にダメージ状態の時
	if (m_bDamage)
	{
		// 抜ける
		return;
	}

	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_DEATH);
	--m_nLife;
	m_bDamage = true;
	m_fDamageCounter = 0.0f;
	ChangeColor(true);
}

//==========================================
//  オブジェクト生成処理
//==========================================
CPlayer *CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//インスタンス生成
	CPlayer *pPlayer = NULL;

	//NULLチェック
	if (pPlayer == NULL)
	{
		//メモリを確保
		pPlayer = new CPlayer;
	}

	//各種情報の保存
	pPlayer->m_pos = pos;
	pPlayer->m_size = size;
	pPlayer->m_rot = rot;

	//初期化
	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}

	//ポインタを返す
	return pPlayer;
}

//==========================================
//  モーションの更新
//==========================================
void CPlayer::Motion(void)
{
	//状態更新
	if (m_State == DEATH || m_State == IAI || m_State ==RUSH)
	{
		//更新しない
	}
	else if (!m_bRand) //着地してない状態
	{
		if (m_move.y > 0.0f)
		{
			m_State = JUMP;
		}
		else
		{
			m_State = FALL;
		}
	}
	else if (m_move.x != 0.0f) //移動している状態
	{
		m_State = WALK;
	}
	else //上記のどれでもない状態
	{
		m_State = NEUTRAL;
	}

	//モーションを更新
	if (m_State != m_oldState)
	{
		switch (m_State)
		{
		case IAI:
			m_pMotion->Set(CMotion::PLAYER_IAI);
			break;
		case JUMP:
			m_pMotion->Set(CMotion::PLAYER_JUMP);
			break;
		case FALL:
			m_pMotion->Set(CMotion::PLAYER_FALL);
			break;
		case WALK:
			m_pMotion->Set(CMotion::PLAYER_WALK);
			break;
		case NEUTRAL:
			m_pMotion->Set(CMotion::PLAYER_WAIT);
			break;
		case DEATH:
			m_pMotion->Set(CMotion::PLAYER_DEATH);
			break;
		case RUSH:
			m_pMotion->Set(CMotion::PLAYER_IAI);
			break;
		}
	}

	//現在の状態を保存
	m_oldState = m_State;
}

//==========================================
//  移動制限
//==========================================
void CPlayer::Limit(void)
{
	//X座標の制限
	if (CGameManager::GetState() != CGameManager::STATE_START && CGameManager::GetState() != CGameManager::STATE_END)
	{
		if (m_pos.x < -2250.0f)
		{
			m_pos.x = -2250.0f;
		}
		if (m_pos.x > 2250.0f)
		{
			m_pos.x = 2250.0f;
		}
	}

	//Y座標の制限
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
	}
	if (m_pos.y <= 0.0f)
	{
		m_bRand = true;
		m_bDoubleJump = false;
	}

	if (CGameManager::GetState() != CGameManager::STATE_BOSS)
	{
		if (m_pos.y > LIMIT_HEIGHT_NORMAL)
		{
			m_pos.y = LIMIT_HEIGHT_NORMAL;
		}
	}
	else
	{
		if (m_pos.y > LIMIT_HEIGHT_BOSS)
		{
			m_pos.y = LIMIT_HEIGHT_BOSS;
		}
		if (m_pos.x < LIMIT_WIDTH_BOSS)
		{
			m_pos.x = LIMIT_WIDTH_BOSS;
		}
	}
}

//==========================================
//  移動の処理
//==========================================
void CPlayer::Move(void)
{
	// 攻撃状態中は抜ける
	if (m_State == IAI)
	{
		return;
	}

	//ローカル変数宣言
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_State != DEATH)
	{
		//パッド移動量を取得
		move = CManager::GetInstance()->GetJoyPad()->GetStickL(0.1f);

		//キーボード移動量の取得
		if (move.x == 0.0f)
		{
			move = CManager::GetInstance()->GetKeyboard()->GetWASD();
		}
	}

	//自動歩行
	if (CGameManager::GetState() == CGameManager::STATE_START)
	{
		move.x = 1.0f;
	}

	//移動量の適用
	m_move.x = move.x * PLAYER_SPEED;

	//慣性による移動の停止
	m_move.x += (0.0f - m_move.x) * 0.1f;


	//移動量を適用
	m_pos += m_move * m_fDeltaTime;
}

//==========================================
//  回転処理
//==========================================
void CPlayer::Rotate(void)
{
	//移動してない時は回転しない
	if (m_move.x == 0.0f)
	{
		return;
	}

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

//==========================================
//  ジャンプの処理
//==========================================
void CPlayer::Jump(void)
{
	// 攻撃中に抜ける
	if (m_State == IAI)
	{
		return;
	}

	// 死亡時に抜ける
	if (m_State == DEATH)
	{
		return;
	}
	if (CGameManager::GetState() == CGameManager::STATE_START || CGameManager::GetState() == CGameManager::STATE_END)
	{
		return;
	}

	//着地フラグがオフの時
	else if (!m_bRand && m_bDoubleJump)
	{
		return;
	}

	//ジャンプ!
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_SPACE) || CManager::GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_LB))
	{
		if(!m_bRand)
		{
			m_bDoubleJump = true;
		}

		// 着地していない状態
		m_move.y = JUMP_MOVE;
		m_bRand = false;
	}
}

//==========================================
//  重力の処理
//==========================================
void CPlayer::Gravity(void)
{
	// 攻撃中は重力を受けない
	if (m_State == IAI)
	{
		return;
	}

	//重力の無効条件
	if (m_bRand)
	{
		m_move.y = 0.0f;
		return;
	}
	else if (m_move.y <= -JUMP_MOVE)
	{
		m_move.y = -JUMP_MOVE;
		return;
	}

	//移動量の減少
	m_move.y -= GRAVITY * CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();
}

//==========================================
//  殺す
//==========================================
void CPlayer::Damage(void)
{
	// 攻撃中は攻撃を受けない
	if (m_State == IAI || m_State == DEATH)
	{
		return;
	}

	//当たり判定の生成
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//先頭のアドレスを取得
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject* pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_ENEMY || pObj->GetType() == CObject::TYPE_BOSS) //敵の場合
			{
				if (pObj->GetObjState() == CObject::NORMAL)
				{
					//対象の座標を取得する
					D3DXVECTOR3 pos = pObj->GetPos();

					//ベクトルの算出
					D3DXVECTOR3 vec = m_CenterPos - pos;

					//ベクトルの大きさを比較する
					if (HIT_LENGTH * HIT_LENGTH >= (vec.x * vec.x + vec.y * vec.y))
					{
						// ダメージ処理
						Attacked();
					}
				}
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}
}

//==========================================
//  攻撃の処理
//==========================================
void CPlayer::Attack()
{
	// 死亡状態中は抜ける
	if (m_State == DEATH)
	{
		return;
	}

	// 右スティック入力があった場合
	if (CManager::GetInstance()->GetJoyPad()->GetStickTriggerR(CJoyPad::STICK_ALL))
	{
		// 右スティック入力の値を取得
		D3DXVECTOR3 vecInput = CManager::GetInstance()->GetJoyPad()->GetStickR(0.1f);

		// 攻撃の方向を算出する
		float rot = atan2f(vecInput.z, vecInput.x);

		// 攻撃を生成
		CSlash::Create(m_CenterPos, rot);
	}
#ifdef _DEBUG

	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_RIGHT))
	{
		// 攻撃の方向を算出する
		float rot = D3DX_PI;

		// 攻撃を生成
		CSlash::Create(m_CenterPos, rot);
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LEFT))
	{
		// 攻撃の方向を算出する
		float rot = -D3DX_PI;

		// 攻撃を生成
		CSlash::Create(m_CenterPos, rot);
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_UP))
	{
		// 攻撃の方向を算出する
		float rot = D3DX_PI * 0.5f;

		// 攻撃を生成
		CSlash::Create(m_CenterPos, rot);
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_DOWN))
	{
		// 攻撃の方向を算出する
		float rot = D3DX_PI * -0.5f;

		// 攻撃を生成
		CSlash::Create(m_CenterPos, rot);
	}

#endif
}

//==========================================
//  ダッシュ処理
//==========================================
void CPlayer::Dash()
{
	// 死亡状態中は抜ける
	if (m_State == DEATH)
	{
		return;
	}

	// クールタイムが一定未満だと攻撃不可
	if (m_AttackCoolTime < ATTACK_COOL_TIME)
	{
		// 攻撃のクールタイムを加算
		m_AttackCoolTime += m_fDeltaTime;

		return;
	}

	// 右スティック入力の値を取得
	D3DXVECTOR3 vecInput = CManager::GetInstance()->GetJoyPad()->GetStickR(0.1f);

	// 入力値を変更する
	vecInput.y = vecInput.z;
	vecInput.z = 0.0f;

	// 右スティック入力があった場合
	if (CManager::GetInstance()->GetJoyPad()->GetStickTriggerR(CJoyPad::STICK_ALL) && m_State != IAI)
	{
		// 入力値を正規化する
		D3DXVec3Normalize(&vecInput, &vecInput);

		// 移動量を入力方向に分解する
		m_move = vecInput * ATTACK_SPEED * m_fDeltaTime;

		// 攻撃状態に遷移
		m_State = IAI;

		// 攻撃時間をリセット
		m_fStateCounter = 0.0f;

		// 開始地点を記録する
		m_posStart = m_CenterPos;

		// 軌跡を描画
		m_pOrbit->SwitchDraw(true);
	}

	// 攻撃状態中の場合
	if (m_State == IAI)
	{
		// 攻撃時間の加算
		m_fStateCounter += m_fDeltaTime;

		// 移動する
		m_pos += m_move;

		// 攻撃判定
		Hit();

		// 一定時間で攻撃を解除する
		if (m_fStateCounter >= ATTACK_TIME)
		{
			// カウンターをリセット
			m_fStateCounter = 0.0f;

			// 空中にいたらジャンプ状態にする
			if (m_pos.y > 0.0f)
			{
				// 着地フラグオフ
				m_bRand = false;

				// 落下状態
				m_State = FALL;
			}
			else
			{
				// 待機状態
				m_State = NEUTRAL;
			}

			// クールタイムをリセット
			m_AttackCoolTime = 0.0f;

			// 軌跡を描画
			m_pOrbit->SwitchDraw(false);
		}
	}
}

//==========================================
//  敵との当たり判定
//==========================================
void CPlayer::Hit()
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
					D3DXVECTOR3 pos = pObj->GetPos();

					// 始点から終点までのベクトルを求める
					D3DXVECTOR3 vecLine = m_CenterPos - m_posStart;

					// 始点から目標点までのベクトルを求める
					D3DXVECTOR3 vecToPos = pos - m_posStart;

					// 各ベクトルの大きさを求める
					float lengthLine = sqrtf((vecLine.x * vecLine.x) + (vecLine.y * vecLine.y));
					float lengthToPos = sqrtf((vecToPos.x * vecToPos.x) + (vecToPos.y * vecToPos.y));

					// 媒介変数tを求める
					float t = (lengthLine * lengthToPos) / (lengthLine * lengthLine);

					// 線分の判定
					if (0.0f <= t && t <= 1.0f)
					{
						// 目標点から直線に垂線を下した時の交点を求める
						D3DXVECTOR3 posCross = m_posStart + (t * vecLine);

						// 交点から目標点までのベクトルを求める
						D3DXVECTOR3 vecToCross = pos - posCross;

						// 判定距離の比較
						if (m_fHitLength * m_fHitLength >= (vecToCross.x * vecToCross.x) + (vecToCross.y * vecToCross.y))
						{
							// 当たっていた時の演出系処理
							CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SLICE);
							pObj->SetState(CObject::ATTACKED);
						}
					}
				}
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}
}
