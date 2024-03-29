//==========================================
//
//  ライトクラス(light.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "light.h"
#include "manager.h"
#include "renderer.h"
#include "gamemanager.h"
#include "camera.h"

//==========================================
//  コンストラクタ
//==========================================
CLight::CLight()
{
	for (int nCnt = 0; nCnt < NUM_LIGHT; nCnt++)
	{
		m_Light[nCnt] = {};
	}
}

//==========================================
//  デストラクタ
//==========================================
CLight::~CLight()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CLight::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ローカル変数宣言
	D3DXVECTOR3 vecDir; //設定用の方向ベクトル

	for (int nCnt = 0; nCnt < NUM_LIGHT; nCnt++)
	{
		//ライト情報のクリア
		ZeroMemory(&m_Light[nCnt], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		m_Light[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		m_Light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//ライトの方向を設定
		switch (nCnt)
		{
		case 0:
			vecDir = D3DXVECTOR3(0.34f, -0.87f, 0.35f);
			break;
		case 1:
			vecDir = D3DXVECTOR3(-0.59f, -0.10f, -0.80f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(-0.22f, -0.74f, 0.63f);
		}

		D3DXVec3Normalize(&vecDir, &vecDir); //ベクトルの正規化
		m_Light[nCnt].Direction = vecDir;

		//ライトを設定する
		pDevice->SetLight(nCnt, &m_Light[nCnt]);

		//ライトを有効化する
		pDevice->LightEnable(nCnt, TRUE);
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CLight::Uninit(void)
{

}

//==========================================
//  更新処理
//==========================================
void CLight::Update(void)
{

}
