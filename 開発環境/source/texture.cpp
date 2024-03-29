//==========================================
//
//  テクスチャ管理クラス(texture.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include <string.h>

//==========================================
//  マクロ定義
//==========================================
#define TXTFILENAME_TEX "data\\TXT\\TexData.txt" //テクスチャ情報を持ったテキストファイルのパス
#define SHARE_PASS_TEX "data\\TEXTURE\\" //全てのテクスチャファイルに共通する相対パス

//==========================================
//  静的メンバ変数宣言
//==========================================
bool CTexture::m_bLoad = false;

//==========================================
//  コンストラクタ
//==========================================
CTexture::CTexture()
{
	m_nNumAll = 0;
}

//==========================================
//  デストラクタ
//==========================================
CTexture::~CTexture()
{
	m_bLoad = false;
}

//==========================================
//  読み込み処理
//==========================================
HRESULT CTexture::Load(void)
{
	//2度目はないぞ
	if (m_bLoad)
	{
		return E_FAIL;
	}

	//ローカル変数宣言
	FILE *pFile; //ファイル名
	int nNumTex; //読み込むテクスチャ数
	char aStr[256]; //不要な文字列の記録用

	//ファイルを読み取り専用で開く
	pFile = fopen(TXTFILENAME_TEX, "r");

	if (pFile != NULL)
	{
		//不要な文字列の読み込み
		for (int nCntDiscard = 0; nCntDiscard < 13; nCntDiscard++)
		{
			fscanf(pFile, "%s", &aStr[0]);
		}

		//テクスチャ数の読み込み
		fscanf(pFile, "%d", &nNumTex);

		//一枚以上のテクスチャがある場合
		if (nNumTex > 0)
		{
			//テクスチャ総数の記録
			m_nNumAll = nNumTex;

			//不要な文字列の読み込み
			for (int nCntDiscard = 0; nCntDiscard < 4; nCntDiscard++)
			{
				fscanf(pFile, "%s", &aStr[0]);
			}

			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

			//テクスチャの読み込み
			for (int nCnt = 0; nCnt < nNumTex; nCnt++)
			{
				//テクスチャファイルのパス
				char sTexName[256];

				//共通のパスを取得
				strcpy(&sTexName[0], SHARE_PASS_TEX);

				//ファイル名の読み込み
				for (int nCnt2 = 0; nCnt2 < 3; nCnt2++)
				{
					fscanf(pFile, "%s", &aStr[0]);
				}

				//パスとファイル名の連結
				strcat(&sTexName[0], &aStr[0]);

				//テクスチャの読み込み
				if (FAILED(D3DXCreateTextureFromFile(pDevice, &sTexName[0], &m_apTexture[nCnt])))
				{
					return E_FAIL;
				}

				//読み込んだテクスチャのパスを記録
				strcpy(&m_sFilePass[nCnt][0], &sTexName[0]);

				//不要な文字列の読み込み
				fscanf(pFile, "%s", &aStr[0]);
			}

			//読み込み完了フラグを立てる
			m_bLoad = true;
		}
		else
		{
			fclose(pFile);
			return E_FAIL;
		}
		fclose(pFile);
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

//==========================================
//  全テクスチャの破棄処理
//==========================================
void CTexture::UnLoad(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

//==========================================
//  テクスチャの登録処理
//==========================================
int CTexture::Regist(const char *pFilName)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//テクスチャの重複を防ぐ
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		if (strcmp(&m_sFilePass[nCnt][0], pFilName) == 0) //既に同じテクスチャが読み込まれている場合
		{
			//先に読み込まれていたテクスチャの番号を返す
			return nCnt;
		}
	}

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, pFilName, &m_apTexture[m_nNumAll])))
	{
		return -1;
	}
	else
	{
		//読み込んだテクスチャのパスを記録
		strcpy(&m_sFilePass[m_nNumAll][0], pFilName);

		//総数を加算
		m_nNumAll++;
	}

	//登録されたテクスチャの番号を返す
	return m_nNumAll - 1;
}
