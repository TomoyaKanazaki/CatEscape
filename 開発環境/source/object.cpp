//==========================================
//
//  オブジェクトクラス(object.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"
#include "debugproc.h"
#include "scenemanager.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CObject *CObject::m_apTop[PRIORITY_NUM] = {};
CObject *CObject::m_apCur[PRIORITY_NUM] = {};
int CObject::m_nNumObject = 0;

//==========================================
//  コンストラクタ
//==========================================
CObject::CObject(int nPriority)
{
	//先頭オブジェクトの判定
	if (m_apTop[nPriority] == NULL)
	{
		m_apTop[nPriority] = this;
		m_apCur[nPriority] = this;
		this->m_pNext = NULL;
		this->m_pPrev = NULL;
	}
	else //先頭でない場合、最後尾オブジェクトの次に設定する
	{
		this->m_pPrev = m_apCur[nPriority];
		m_apCur[nPriority] = this;
		this->m_pPrev->m_pNext = this;
		this->m_pNext = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_oldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_oldRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nPriority = nPriority;
	m_fDeltaTime = 0.0f;
	m_type = TYPE_NONE;
	m_ObjState = NORMAL;
	++m_nNumObject;
	m_bDeath = false;
	m_bMap = false;
}

//==========================================
//  デストラクタ
//==========================================
CObject::~CObject()
{
	//オブジェクト位置の判定
	if (this == m_apTop[m_nPriority]) //先頭の場合
	{
		//自身の次のオブジェクトを先頭にする
		m_apTop[m_nPriority] = this->m_pNext;

		//NULLチェック
		if (m_apTop[m_nPriority] != NULL)
		{
			//先頭オブジェクトの前はNULL
			m_apTop[m_nPriority]->m_pPrev = NULL;
		}
	}
	else if (this == m_apCur[m_nPriority]) //最後尾の場合
	{
		//自身の前のオブジェクトを最後尾にする
		m_apCur[m_nPriority] = this->m_pPrev;

		//最後尾オブジェクトの次はNULL
		m_apCur[m_nPriority]->m_pNext = NULL;
	}
	else
	{
		//自身の次のオブジェクトの前のオブジェクトを自身の前のオブジェクトに設定する
		this->m_pNext->m_pPrev = this->m_pPrev;

		//自身の前のオブジェクトの次のオブジェクトを自身の次のオブジェクトに設定する
		this->m_pPrev->m_pNext = this->m_pNext;
	}
	--m_nNumObject;
}

//==========================================
//  全オブジェクトの破棄
//==========================================
void CObject::ReleaseAll(void)
{
	//各オブジェクトのフラグを立てる
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//先頭オブジェクトを取得
		CObject *pObj = m_apTop[nCntPriority];

		//NULLになるまで続ける
		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			//現在のオブジェクトを終了
			pObj->Uninit();

			//アドレスを次のアドレスにずらす
			pObj = pNext;
		}
	}

	//死亡フラグの確認
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//先頭オブジェクトを取得
		CObject *pObj = m_apTop[nCntPriority];

		//NULLになるまで続ける
		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			//現在のオブジェクトを終了
			if (pObj->m_bDeath)
			{
				delete pObj;
				pObj = NULL;
			}

			//アドレスを次のアドレスにずらす
			pObj = pNext;
		}
	}
}

//==========================================
//  全オブジェクトの更新
//==========================================
void CObject::UpdateAll(void)
{
	//各オブジェクトの更新
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//先頭オブジェクトを取得
		CObject *pObj = m_apTop[nCntPriority];

		//NULLになるまで続ける
		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			//現在のオブジェクトを更新
			if (!pObj->m_bDeath)
			{
				pObj->Update();
			}

			//アドレスを次のアドレスにずらす
			pObj = pNext;
		}
	}

	//死亡フラグの確認
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//先頭オブジェクトを取得
		CObject *pObj = m_apTop[nCntPriority];

		//NULLになるまで続ける
		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			//現在のオブジェクトを終了
			if (pObj->m_bDeath)
			{
				delete pObj;
				pObj = NULL;
			}

			//アドレスを次のアドレスにずらす
			pObj = pNext;
		}
	}

	DebugProc::Print("オブジェクト数 : %d\n", m_nNumObject);
}

//==========================================
//  全オブジェクトの描画
//==========================================
void CObject::DrawAll(void)
{
	//描画優先順位
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//先頭オブジェクトを取得
		CObject *pObj = m_apTop[nCntPriority];

		//NULLになるまで続ける
		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject *pNext = pObj->GetNext();

			//現在のオブジェクトを描画
			pObj->Draw();

			//アドレスを次のアドレスにずらす
			pObj = pNext;
		}
	}
}

//==========================================
//  スクリーンに入っているか否か
//==========================================
bool CObject::OnScreen(void)
{
	//内部判定フラグ
	bool bIn = false;

	//ビューポートの設定
	D3DVIEWPORT9 vp = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f };

	//計算用変数宣言
	D3DXMATRIX mtxView = CManager::GetInstance()->GetSceneManager()->GetCamera()->CreateViewMatrix(); //ビューマトリックス
	D3DXMATRIX mtxWorld; //ワールドマトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//スクリーン座標を算出
	D3DXVECTOR3 screenPos;
	D3DXMATRIX mtxProjection = CManager::GetInstance()->GetSceneManager()->GetCamera()->GetMtxPro();
	D3DXVec3Project
	(
		&screenPos,
		&m_pos,
		&vp,
		&mtxProjection,
		&mtxView,
		&mtxWorld
	);

	if (screenPos.x >= 0.0f && screenPos.x <= FLOAT_SCREEN_WIDTH)
	{
		if (screenPos.y >= 0.0f && screenPos.y <= FLOAT_SCREEN_HEIGHT)
		{
			bIn = true;
		}
	}

	//値を返す
	return bIn;
}

//==========================================
//  単体の破棄
//==========================================
void CObject::Release(void)
{
	//死亡フラグを立てる
	m_bDeath = true;
}
