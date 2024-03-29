//==========================================
//
//  モーションクラス(moton.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "motion.h"
#include "model.h"

//==========================================
//  マクロ定義
//==========================================
#define TXTFILENAME_MOTION "data\\TXT\\MotionData.txt" //モーション情報を持ったテキストファイルのパス

//==========================================
//  静的メンバ変数宣言
//==========================================
CMotion::INFO CMotion::m_aInfo[MAX_NUM] = {};
int CMotion::m_nNumMotion = 0;

//==========================================
//  コンストラクタ
//==========================================
CMotion::CMotion()
{
	m_ppModel = NULL;
	memset(&m_Info, 0, sizeof(m_Info));
	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		m_startKey[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_startKey[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_nNumModel = 0;
	m_nCntFrame = 0;
	m_nCntKey = 0;
	m_bMotion = false;
}

//==========================================
//  デストラクタ
//==========================================
CMotion::~CMotion()
{

}

//==========================================
//  更新処理
//==========================================
void CMotion::Update(void)
{
	//NULLチェック
	if (m_ppModel != NULL)
	{
		//モーションが完了していたら抜ける
		if (m_bMotion)
		{
			return;
		}

		//キーの有無を確認
		if (m_Info.nNumKey > 0)
		{
			int nNowKey = m_nCntKey; // 現在のキー
			int nNextkey = (nNowKey + 1) % m_Info.nNumKey; //次のキー
			int nFrame = 0;
			if (nNowKey != -1)
			{
				nFrame = m_Info.aKeyInfo[nNowKey].nFrame;
			}

			//モデル数分のモーションを設定
			for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
			{
				//前回の値を取得
				m_oldKey.pos = m_ppModel[nCntModel]->GetPos();
				m_oldKey.rot = m_ppModel[nCntModel]->GetRot();

				//差分を算出
				D3DXVECTOR3 posDeff, rotDeff;
				if (m_nCntKey == -1)
				{
					posDeff = (m_Info.aKeyInfo[nNextkey].aKey[nCntModel].pos - m_startKey[nCntModel].pos);
					rotDeff = (m_Info.aKeyInfo[nNextkey].aKey[nCntModel].rot - m_startKey[nCntModel].rot);
				}
				else
				{
					posDeff = (m_Info.aKeyInfo[nNextkey].aKey[nCntModel].pos - m_Info.aKeyInfo[nNowKey].aKey[nCntModel].pos) / (float)nFrame;
					rotDeff = (m_Info.aKeyInfo[nNextkey].aKey[nCntModel].rot - m_Info.aKeyInfo[nNowKey].aKey[nCntModel].rot) / (float)nFrame;
				}

				//角度の補正
				if (rotDeff.x < -D3DX_PI) //x
				{
					rotDeff.x += D3DX_PI * 2;
				}
				else if (rotDeff.x > D3DX_PI)
				{
					rotDeff.x += -D3DX_PI * 2;
				}

				if (rotDeff.y < -D3DX_PI) //y
				{
					rotDeff.y += D3DX_PI * 2;
				}
				else if (rotDeff.y > D3DX_PI)
				{
					rotDeff.y += -D3DX_PI * 2;
				}

				if (rotDeff.z < -D3DX_PI) //z
				{
					rotDeff.z += D3DX_PI * 2;
				}
				else if (rotDeff.z > D3DX_PI)
				{
					rotDeff.z += -D3DX_PI * 2;
				}

				//現在の値を算出
				D3DXVECTOR3 posDest, rotDest;
				if (m_nCntKey == -1)
				{
					posDest = m_oldKey.pos + posDeff;
					rotDest = m_oldKey.rot + rotDeff;
				}
				else
				{
					posDest = m_oldKey.pos + posDeff;
					rotDest = m_oldKey.rot + rotDeff;
				}

				//算出した値の適用
				if (nCntModel == 0)
				{
					m_ppModel[nCntModel]->SetPos(posDest);
					m_ppModel[nCntModel]->SetRot(rotDest);
				}
				else
				{
					m_ppModel[nCntModel]->SetRot(rotDest);
				}
			}

			if (m_nCntKey == -1)
			{
				//キーの更新
				m_nCntKey = nNextkey;
				m_nCntFrame = 0;
			}
			else
			{
				//フレームカウントを加算
				m_nCntFrame++;

				//キーの更新をチェック
				if (m_Info.aKeyInfo[nNowKey].nFrame != 0)
				{
					if (m_nCntFrame == nFrame)
					{
						//キーの更新
						if (m_Info.bLoop)
						{
							m_nCntKey = nNextkey;
							m_nCntFrame = 0;
						}
						else
						{
							m_bMotion = true;
						}
					}
				}
			}
		}
	}
}

//==========================================
//  モデルの設定処理
//==========================================
void CMotion::SetModel(CModel **ppModel, int nNum, MOTION type)
{
	//モデルを記録
	m_ppModel = ppModel;

	//モデル数を記録
	m_nNumModel = nNum;

	//使用するモーションを設定
	m_Info = m_aInfo[type];

	//モーション開始時の値を取得
	for (int nCnt = 0; nCnt < m_Info.nNumModel; nCnt++)
	{
		m_startKey[nCnt].pos = m_ppModel[nCnt]->GetPos();
		m_startKey[nCnt].rot = m_ppModel[nCnt]->GetRot();
	}
}

//==========================================
//  モーションの設定処理
//==========================================
void CMotion::Set(MOTION type)
{
	//使用するモーションを設定
	m_Info = m_aInfo[type];

	//モーション開始時の値を取得
	for (int nCnt = 0; nCnt < m_Info.nNumModel; nCnt++)
	{
		m_startKey[nCnt].pos = m_ppModel[nCnt]->GetPos();
		m_startKey[nCnt].rot = m_ppModel[nCnt]->GetRot();
	}

	//カウンターをリセット
	m_nCntKey = -1;
	m_nCntFrame = 0;
	m_bMotion = false;
}

//==========================================
//  読み込み処理
//==========================================
void CMotion::Load(void)
{
	//ローカル変数宣言
	FILE *pFile; //ファイル名
	char aStr[256]; //不要な文字列の記録用
	int nCntInfo = 0; //現在のモーション番号
	int nCntKey = 0; //現在のキー番号
	int nCntModel = 0; //現在のモデル番号

	//ファイルを読み取り専用で開く
	pFile = fopen(TXTFILENAME_MOTION, "r");

	if (pFile != NULL)
	{
		while (1)
		{
			//文字列を取得
			fscanf(pFile, "%s", &aStr[0]);

			if (strcmp(&aStr[0], "NUM_MOTION") == 0)
			{
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_nNumMotion); //モーション数取得
			}
			else if (strcmp(&aStr[0], "LOOP") == 0)
			{
				//ループの有無を取得
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_aInfo[nCntInfo].bLoop);
			}
			else if (strcmp(&aStr[0], "NUM_KEY") == 0)
			{
				//キー数の取得
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_aInfo[nCntInfo].nNumKey);
			}
			else if (strcmp(&aStr[0], "NUM_MODEL") == 0)
			{
				//モデル数の取得
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_aInfo[nCntInfo].nNumModel);
			}
			else if (strcmp(&aStr[0], "FRAME") == 0)
			{
				//フレーム数を取得
				fscanf(pFile, "%s", &aStr[0]); //=
				fscanf(pFile, "%d", &m_aInfo[nCntInfo].aKeyInfo[nCntKey].nFrame);
			}
			else if (strcmp(&aStr[0], "POS") == 0)
			{
				//座標を取得
				fscanf(pFile, "%s", &aStr[0]); //=
				D3DXVECTOR3 pos;
				fscanf(pFile, "%f", &pos.x);
				fscanf(pFile, "%f", &pos.y);
				fscanf(pFile, "%f", &pos.z);

				m_aInfo[nCntInfo].aKeyInfo[nCntKey].aKey[nCntModel].pos = pos;
			}
			else if (strcmp(&aStr[0], "ROT") == 0)
			{
				//角度を取得
				fscanf(pFile, "%s", &aStr[0]); //=
				D3DXVECTOR3 rot;
				fscanf(pFile, "%f", &rot.x);
				fscanf(pFile, "%f", &rot.y);
				fscanf(pFile, "%f", &rot.z);

				m_aInfo[nCntInfo].aKeyInfo[nCntKey].aKey[nCntModel].rot = rot;
			}
			else if (strcmp(&aStr[0], "END_MOTIONSET") == 0)
			{
				//モーション番号を進める
				nCntInfo++;

				//キー番号とモデル番号をリセットする
				nCntModel = 0;
				nCntKey = 0;
			}
			else if (strcmp(&aStr[0], "END_KEYSET") == 0)
			{
				//キー番号を進める
				nCntKey++;

				//モデル番号をリセットする
				nCntModel = 0;
			}
			else if (strcmp(&aStr[0], "END_KEY") == 0)
			{
				//モデル番号を進める
				nCntModel++;
			}
			if (strcmp(&aStr[0], "END_SCRIPT") == 0)
			{
				//終端
				break;
			}
		}
		fclose(pFile);
	}
}
