//==========================================
//
//  階層構造管理クラス(layer.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "layer.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CLayer::LAYERDATA *CLayer::m_pData = NULL;
int CLayer::m_nNumLayer = 0;

//==========================================
//  マクロ定義
//==========================================
#define TXTLAYER "data\\TXT\\LayerData.txt" //階層構造の情報

//==========================================
//  コンストラクタ
//==========================================
CLayer::CLayer()
{

}

//==========================================
//  デストラクタ
//==========================================
CLayer::~CLayer()
{

}

//==========================================
//  設定処理
//==========================================
CLayer::LAYERDATA *CLayer::Set(LAYERS type)
{
	//階層構造の情報を渡す
	return &m_pData[type];
}

//==========================================
//  読み込み処理
//==========================================
void CLayer::Load(void)
{
	//ローカル変数宣言
	FILE *pFile; //ファイル名
	char aStr[256]; //不要な文字列の記録用

	//ファイルを読み取り専用で開く
	pFile = fopen(TXTLAYER, "r");

	if (pFile != NULL)
	{
		//不要な文字列の取得
		while (1)
		{
			fscanf(pFile, "%s", &aStr[0]);

			if (strcmp(&aStr[0], "NUM_LAYER") == 0)
			{
				break;
			}
		}

		//階層構造情報の数を取得
		fscanf(pFile, "%s", &aStr[0]); // =
		fscanf(pFile, "%d", &m_nNumLayer);

		//レイヤー情報が存在する場合
		if (m_nNumLayer != 0)
		{
			//メモリを確保する
			m_pData = new LAYERDATA[m_nNumLayer];
		}

		//NULLチェック
		if (m_pData != NULL)
		{
			for (int nCntLayer = 0; nCntLayer < m_nNumLayer; nCntLayer++)
			{
				//不要な文字列の取得
				while (1)
				{
					fscanf(pFile, "%s", &aStr[0]);

					if (strcmp(&aStr[0], "NUM_MODEL") == 0)
					{
						break;
					}
				}

				//モデル数を取得
				fscanf(pFile, "%d", &m_pData[nCntLayer].nNumModel);

				//モデルが存在する場合
				if (m_pData[nCntLayer].nNumModel != 0)
				{
					//メモリを確保する
					m_pData[nCntLayer].pModelID = new int[m_pData[nCntLayer].nNumModel];
					m_pData[nCntLayer].pParentID = new int[m_pData[nCntLayer].nNumModel];
					m_pData[nCntLayer].pPos = new D3DXVECTOR3[m_pData[nCntLayer].nNumModel];
					m_pData[nCntLayer].pRot = new D3DXVECTOR3[m_pData[nCntLayer].nNumModel];
				}

				//NULLチェック
				if (m_pData[nCntLayer].pModelID != NULL && m_pData[nCntLayer].pParentID != NULL)
				{
					for (int nCntModel = 0; nCntModel < m_pData[nCntLayer].nNumModel; nCntModel++)
					{
						//自身が使用するモデルの取得
						fscanf(pFile, "%s", &aStr[0]); // MODELID
						fscanf(pFile, "%d", &m_pData[nCntLayer].pModelID[nCntModel]);

						//親モデルのインデックスを取得
						fscanf(pFile, "%s", &aStr[0]); // ParentID
						fscanf(pFile, "%d", &m_pData[nCntLayer].pParentID[nCntModel]);

						//相対位置を取得
						fscanf(pFile, "%s", &aStr[0]); // POS
						fscanf(pFile, "%f", &m_pData[nCntLayer].pPos[nCntModel].x);
						fscanf(pFile, "%f", &m_pData[nCntLayer].pPos[nCntModel].y);
						fscanf(pFile, "%f", &m_pData[nCntLayer].pPos[nCntModel].z);

						//相対角度を取得
						fscanf(pFile, "%s", &aStr[0]); // ROT
						fscanf(pFile, "%f", &m_pData[nCntLayer].pRot[nCntModel].x);
						fscanf(pFile, "%f", &m_pData[nCntLayer].pRot[nCntModel].y);
						fscanf(pFile, "%f", &m_pData[nCntLayer].pRot[nCntModel].z);
					}
				}
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}

//==========================================
//  破棄
//==========================================
void CLayer::UnLoad(void)
{
	//メモリを開放する
	if (m_pData != NULL)
	{
		for (int nCnt = 0; nCnt < m_nNumLayer; nCnt++)
		{
			delete m_pData[nCnt].pModelID;
			m_pData[nCnt].pModelID = NULL;

			delete m_pData[nCnt].pParentID;
			m_pData[nCnt].pParentID = NULL;

			delete m_pData[nCnt].pPos;
			m_pData[nCnt].pPos = NULL;

			delete m_pData[nCnt].pRot;
			m_pData[nCnt].pRot = NULL;
		}

		delete m_pData;
		m_pData = NULL;
	}
}
