//==========================================
//
//  アニメーション3Dクラス(object3D.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "object3D_Anim.h"

//==========================================
//  コンストラクタ
//==========================================
CObject3D_Anim::CObject3D_Anim(int nPriority) : CObject3D(nPriority)
{
	m_Type = TYPE_NONE;
	m_nNumPattern = 0;
	m_nAnimPattern = 0;
	m_nAnimCounter = 0;
	m_nUpdateFrame = 0;
	m_bLoop = 0;
}

//==========================================
//  デストラクタ
//==========================================
CObject3D_Anim::~CObject3D_Anim()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CObject3D_Anim::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL;
	}

	//テクスチャ座標を設定
	SetTexPos();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CObject3D_Anim::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CObject3D_Anim::Update(void)
{
	//カウンターの更新
	m_nAnimCounter++;

	//アニメーションの更新
	if (m_nAnimCounter % m_nUpdateFrame == 0)
	{
		if (FAILED(SetTexPos()))
		{
			this->Release();
			return;
		}
	}

	//更新する
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CObject3D_Anim::Draw(void)
{
	CObject3D::Draw();
}

//==========================================
//  アニメーション情報の設定
//==========================================
void CObject3D_Anim::SetAnim(int nPattern, int nInterval, bool bLoop, UVTYPE type)
{
	m_nNumPattern = nPattern;
	m_nUpdateFrame = nInterval;
	m_bLoop = bLoop;
	m_Type = type;
}

//==========================================
//  テクスチャの設定
//==========================================
HRESULT CObject3D_Anim::SetTexPos(void)
{
	//ローカル変数宣言
	float fUVPos;
	D3DXVECTOR2 min, max;

	//テクスチャ座標の最小値を算出する
	fUVPos = (1.0f / m_nNumPattern) * m_nAnimPattern;

	//値を適応する
	switch (CObject3D_Anim::m_Type)
	{
	case TYPE_U:
		min = D3DXVECTOR2(fUVPos, 0.0f);
		break;
	case TYPE_V:
		min = D3DXVECTOR2(0.0f, fUVPos);
		break;
	default:
		break;
	}

	//テクスチャ座標の最大値を算出する
	if (this->GetType() == CObject::TYPE_BG)
	{
		fUVPos += 1.0f;
	}
	else
	{
		fUVPos = (1.0f / m_nNumPattern) * (m_nAnimPattern + 1);
	}

	//値を適応する
	switch (CObject3D_Anim::m_Type)
	{
	case TYPE_U:
		max = D3DXVECTOR2(fUVPos, 1.0f);
		break;
	case TYPE_V:
		max = D3DXVECTOR2(1.0f, fUVPos);
		break;
	default:
		break;
	}

	//テクスチャ座標の更新
	SetTex(min, max);

	if (m_nAnimPattern >= m_nNumPattern) //最後のアニメーションの場合
	{
		if (m_bLoop) //ループする場合
		{
			m_nAnimPattern = 0;
		}
		else
		{
			return E_FAIL;
		}
	}
	else
	{
		//アニメーション番号を更新する
		m_nAnimPattern++;
	}

	return S_OK;
}
