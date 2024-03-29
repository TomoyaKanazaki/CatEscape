//==========================================
//
//  エネミーマネージャ(enemymanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemymanager.h"
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "gamemanager.h"
#include "boss.h"

//==========================================
//  クラス定義
//==========================================
namespace
{
	const D3DXVECTOR3 BOSS_POS = D3DXVECTOR3(1800.0f, 150.0f, 0.0f); // ボスのポジション
	const char* ENEMY_FILE = "data\\TXT\\Enemy.txt"; // 敵の配置情報が保存されたファイル
}

//==========================================
//  コンストラクタ
//==========================================
CEnemyManager::CEnemyManager() :
	m_pInfo(nullptr),
	m_pBoss(nullptr),
	m_bPopFrag(false),
	m_bBossCrush(false),
	m_bRush(false)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================
//  初期化処理
//==========================================
void CEnemyManager::Init()
{
	// 情報の読み込み
	Load();
}

//==========================================
//  終了処理
//==========================================
void CEnemyManager::Uninit()
{
	// 設置情報の破棄
	if (m_pInfo != nullptr)
	{
		delete m_pInfo;
		m_pInfo = nullptr;
	}

	// 自身の削除
	delete this;
}

//==========================================
//  更新処理
//==========================================
void CEnemyManager::Update()
{
	// ボスの出現
	if (!m_bBossCrush)
	{
		if (CGameManager::GetState() == CGameManager::STATE_BOSS)
		{
			if (!m_bPopFrag) // ボス出現フラグ
			{
				m_pBoss = CEnemy::Create(BOSS_POS, CEnemy::BOSS);
				m_bPopFrag = true;
			}
			else
			{
				if (m_pBoss->GetState() == CBoss::RUSH) // ラッシュ状態
				{
					m_bRush = true;
				}
			}
		}
	}
}

//==========================================
//  読み込み処理
//==========================================
void CEnemyManager::Load()
{
	//ローカル変数宣言
	FILE* pFile; // ファイルポインタ
	char aStr[256]; // 不要な文字列の記録用

	//ファイルを読み取り専用で開く
	pFile = fopen(ENEMY_FILE, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			// テキスト読み込み
			fscanf(pFile, "%s", &aStr[0]);

			// 条件分岐
			if (strcmp(&aStr[0], "ENEMY_SET") == 0) // 敵情報の設定
			{
				// 敵配置用変数
				D3DXVECTOR3 pos;
				CEnemy::TYPE type = CEnemy::NONE;

				while (1)
				{
					// テキスト読み込み
					fscanf(pFile, "%s", &aStr[0]);

					// 条件分岐処理
					if (strcmp(&aStr[0], "POS") == 0) // 座標
					{
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(&aStr[0], "TYPE") == 0) // 種類
					{
						fscanf(pFile, "%d", &type);
					}
					else if (strcmp(&aStr[0], "ENEMY_END") == 0) // 配置情報の終わり
					{
						// 配置
						CEnemy::Create(pos, type);

						// ループを抜ける
						break;
					}
				}
			}
			else if (strcmp(&aStr[0], "END_FILE") == 0) // ファイルの終端
			{
				// ファイルを閉じる
				fclose(pFile);

				// ループを抜ける
				break;
			}
		}
	}
}

//==========================================
//  生成処理
//==========================================
CEnemyManager* CEnemyManager::Create()
{
	// インスタンス生成
	CEnemyManager* manager = new CEnemyManager;

	// NULLチェック
	if (manager == nullptr) { return nullptr; }

	// 初期化処理
	manager->Init();

	// 値を返す
	return manager;
}
