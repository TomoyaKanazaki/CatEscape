//==========================================
//
//  フェードクラス(fade.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "fade.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  コンストラクタ
//==========================================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	m_bFinish = false;
	m_nTime = 0;
	m_nCounter = 0;
	m_fAlpha = 0.0f;
	m_Mode = MODE_NONE;
}

//==========================================
//  デストラクタ
//==========================================
CFade::~CFade()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CFade::Init(void)
{
	//ポリゴンの情報を設定
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	m_size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//初期化
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	//タイプの設定
	SetType(TYPE_FADE);

	//カラーの情報を設定
	switch (m_Mode)
	{
	case MODE_IN:
		SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	case MODE_OUT:
		SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		break;
	default:
		break;
	}

	//透過定数を設定
	m_fAlpha = 1.0f / (float)m_nTime;
	if (m_Mode == MODE_IN)
	{
		m_fAlpha *= -1.0f;
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CFade::Update(void)
{
	//現在の不透明度を取得
	float fAlpha = GetCol().a;

	//終了フラグを立てる
	if (m_nCounter >= m_nTime && (fAlpha >= 1.0f || 0.0f >= fAlpha))
	{
		m_bFinish = true;
		return;
	}

	//不透明度を設定
	AddAlpah(m_fAlpha);

	//カウンターを加算
	m_nCounter++;

	//デバッグ表示
	DebugProc::Print("透明度 : %f\n", fAlpha);
}

//==========================================
//  描画処理
//==========================================
void CFade::Draw(void)
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CFade * CFade::Create(int nTime, MODE mode)
{
	//インスタンス生成
	CFade *pFade = NULL;

	//NULLチェック
	if (pFade == NULL)
	{
		//メモリを確保
		pFade = new CFade;
	}

	//値を割り当てる
	pFade->m_nTime = nTime;
	pFade->m_Mode = mode;

	//初期化
	if (pFade != NULL)
	{
		pFade->Init();
	}

	//ポインタを返す
	return pFade;
}
