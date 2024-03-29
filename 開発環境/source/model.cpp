//==========================================
//
//  モデルクラス(model.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//==========================================
//  マクロ定義
//==========================================
#define TXTFILENAME_MODEL "data\\TXT\\ModelData.txt" //モデル情報を持ったテキストファイルのパス
#define SHARE_PASS_MODEL "data\\MODEL\\" //全てのXファイルに共通する相対パス

//==========================================
//  静的メンバ変数宣言
//==========================================
CModel::MODEL CModel::m_Model[MAX_MODEL] = {};
int CModel::m_nNumAll = 0;
char CModel::m_sFilePass[MAX_MODEL][128] = {};
bool CModel::m_bLoad = false;
int CModel::m_nNum = 0;

//==========================================
//  コンストラクタ
//==========================================
CModel::CModel()
{
	m_Info.pTexture = NULL;
	m_Info.pMesh = NULL;
	m_Info.pBuffMat = NULL;
	m_Info.dwNumMat = 0;
	m_Info.mtxWorld = {};
	m_pParent = NULL;
	m_nSelfID = 0;
	m_nNum++;
}

//==========================================
//  デストラクタ
//==========================================
CModel::~CModel()
{
	m_nNum--;
}

//==========================================
//  初期化処理
//==========================================
HRESULT CModel::Init(void)
{
	ResetMaterial();
	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CModel::Uninit(void)
{
	delete this;
}

//==========================================
//  更新処理
//==========================================
void CModel::Update(void)
{
}

//==========================================
//  描画処理
//==========================================
void CModel::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetInstance()->GetRenderer()->GetDevice();

	//ローカル変数宣言
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DXMATRIX mtxParent; //親マトリックス
	D3DMATERIAL9 matDef; //現在のマテリアルの保存用
	D3DXMATERIAL *pMat; //マテリアルへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//親マトリックスの設定
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->m_Info.mtxWorld;
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//ワールドマトリックスと親マトリックスをかけ合わせる
	D3DXMatrixMultiply
	(
		&m_Info.mtxWorld,
		&m_Info.mtxWorld,
		&mtxParent
	);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_Info.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_Info.dwNumMat; nCntMat++)
	{
		// マテリアルの設定
		if (!m_bChangeCol)
		{
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		}
		else
		{
			pDevice->SetMaterial(&m_ChangeMat);
		}

		//テクスチャの設定
		pDevice->SetTexture(0, m_Info.pTexture[nCntMat]);

		//モデルの描画
		m_Info.pMesh->DrawSubset(nCntMat);
	}

	//保存しているマテリアルを復元
	pDevice->SetMaterial(&matDef);
}

//==========================================
//  生成処理
//==========================================
CModel *CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nModelID, CModel *m_pParent)
{
	//インスタンス生成
	CModel *pModel = NULL;

	//NULLチェック
	if (pModel == NULL)
	{
		//メモリを確保
		pModel = new CModel;
	}

	//各種情報の保存
	pModel->m_pParent = m_pParent;
	pModel->m_nSelfID = nModelID;

	//各種情報の設定
	if (m_nNumAll > pModel->m_nSelfID)
	{
		pModel->m_Info = m_Model[pModel->m_nSelfID];
		pModel->m_pos = pos;
		pModel->m_rot = rot;
	}

	//初期化
	if (pModel != NULL)
	{
		pModel->Init();
	}

	//ポインタを返す
	return pModel;
}

//==========================================
//  読み込み処理
//==========================================
HRESULT CModel::Load(void)
{
	if (m_bLoad)
	{
		return E_FAIL;
	}

	//ローカル変数宣言
	FILE *pFile; //ファイル名
	int nNumModel; //読み込むテクスチャ数
	char aStr[256]; //不要な文字列の記録用

	//ファイルを読み取り専用で開く
	pFile = fopen(TXTFILENAME_MODEL, "r");

	if (pFile != NULL)
	{
		//不要な文字列の読み込み
		for (int nCntDiscard = 0; nCntDiscard < 13; nCntDiscard++)
		{
			fscanf(pFile, "%s", &aStr[0]);
		}

		//モデル数の読み込み
		fscanf(pFile, "%d", &nNumModel);

		//情報を格納する
		for (int nCnt = 0; nCnt < nNumModel; nCnt++)
		{
			m_Model[nCnt].pTexture = NULL;
			m_Model[nCnt].pMesh = NULL;
			m_Model[nCnt].pBuffMat = NULL;
			m_Model[nCnt].dwNumMat = 0;
			m_Model[nCnt].mtxWorld = {};
		}

		//1種類以上のモデルがある場合
		if (nNumModel > 0)
		{
			//テクスチャ総数の記録
			m_nNumAll = nNumModel;

			//不要な文字列の読み込み
			for (int nCntDiscard = 0; nCntDiscard < 4; nCntDiscard++)
			{
				fscanf(pFile, "%s", &aStr[0]);
			}

			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetInstance()->GetRenderer()->GetDevice();

			//モデルの読み込み
			for (int nCnt = 0; nCnt < nNumModel; nCnt++)
			{
				//xファイルのパス
				char sTexName[256];

				//共通のパスを取得
				strcpy(&sTexName[0], SHARE_PASS_MODEL);

				//ファイル名の読み込み
				for (int nCnt2 = 0; nCnt2 < 3; nCnt2++)
				{
					fscanf(pFile, "%s", &aStr[0]);
				}

				//パスとファイル名の連結
				strcat(&sTexName[0], &aStr[0]);

				//Xファイルの読み込み
				D3DXLoadMeshFromX
				(
					&sTexName[0],
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&m_Model[nCnt].pBuffMat,
					NULL,
					&m_Model[nCnt].dwNumMat,
					&m_Model[nCnt].pMesh
				);

				//マテリアル数分のポインタを確保する
				if (m_Model[nCnt].pTexture == NULL)
				{
					m_Model[nCnt].pTexture = new LPDIRECT3DTEXTURE9[m_Model[nCnt].dwNumMat];
				}
				else
				{
					return E_FAIL;
				}

				//マテリアルデータへのポインタを取得
				D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_Model[nCnt].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)m_Model[nCnt].dwNumMat; nCntMat++)
				{
					if (pMat[nCntMat].pTextureFilename != NULL)
					{
						//テクスチャを保存し、管理番号を取得する
						int nNumTexID = CManager::GetInstance()->GetInstance()->GetTexture()->Regist(pMat[nCntMat].pTextureFilename);

						//テクスチャを割り当てる
						m_Model[nCnt].pTexture[nCntMat] = CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(nNumTexID);

						D3DXCreateTextureFromFile
						(
							pDevice,
							pMat[nCntMat].pTextureFilename,
							&m_Model[nCnt].pTexture[nCntMat]
						);
					}
					else
					{
						m_Model[nCnt].pTexture[nCntMat] = NULL;
					}
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
//  破棄処理
//==========================================
void CModel::UnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		//メッシュの破棄
		if (m_Model[nCnt].pMesh != NULL)
		{
			m_Model[nCnt].pMesh->Release();
			m_Model[nCnt].pMesh = NULL;
		}

		//マテリアルの破棄
		if (m_Model[nCnt].pBuffMat != NULL)
		{
			m_Model[nCnt].pBuffMat->Release();
			m_Model[nCnt].pBuffMat = NULL;
		}

		//テクスチャの破棄
		if (m_Model[nCnt].pTexture != NULL)
		{
			for (int nCntMat = 0; nCntMat < (int)m_Model[nCnt].dwNumMat; nCntMat++)
			{
				if (m_Model[nCnt].pTexture[nCntMat] != NULL)
				{
					m_Model[nCnt].pTexture[nCntMat]->Release();
					m_Model[nCnt].pTexture[nCntMat] = NULL;
				}
			}
			delete[] m_Model[nCnt].pTexture;
			m_Model[nCnt].pTexture = NULL;
		}
	}
	m_bLoad = false;
}

//==========================================
//  変更後のマテリアルを初期化
//==========================================
void CModel::ResetMaterial()
{
	D3DXMATERIAL* pMat;	//マテリアルデータへのポインタ
	pMat = (D3DXMATERIAL*)m_Model[m_nSelfID].pBuffMat->GetBufferPointer();
	m_ChangeMat = pMat->MatD3D;
}
