//==========================================
//
//  ゲーム内時間計測のクラス(gametime.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gametime.h"
#include "manager.h"
#include "debugproc.h"

//==========================================
//  コンストラクタ
//==========================================
CGameTime::CGameTime() :
	m_fScale(1.0f),
	m_fScaleTime(0.0f)
{
	m_nCurrentTime = 0;
	m_nOldTime = 0;
	m_nDeltaTime = 0;
	m_fDelta = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
CGameTime::~CGameTime()
{

}

//==========================================
//  初期化処理
//==========================================
void CGameTime::Init(void)
{
	//現在時間を取得
	m_nCurrentTime = timeGetTime();
	
	//現在時間を前回時間に保存
	m_nOldTime = m_nCurrentTime;
}

//==========================================
//  終了処理
//==========================================
void CGameTime::Uninit(void)
{

}

//==========================================
//  更新処理
//==========================================
void CGameTime::Update(void)
{
	//前回時間を保存する
	m_nOldTime = m_nCurrentTime;

	//現在時間を取得する
	m_nCurrentTime = timeGetTime();

	//前回時間と現在時間の差分を求める
	m_nDeltaTime = m_nCurrentTime - m_nOldTime;

	//経過時間の割合を求める
	m_fDelta = (float)m_nDeltaTime / 1000.0f;

	// 倍率
	Scaling();

	//デバッグ表示
	DebugProc::Print("前回時刻 : %d\n", m_nOldTime);
	DebugProc::Print("現在時刻 : %d\n", m_nCurrentTime);
	DebugProc::Print("経過時間 : %d\n", m_nDeltaTime);
	DebugProc::Print("経過割合 : %f\n", m_fDelta);
}

//==========================================
//  倍率と時間の加算
//==========================================
void CGameTime::AddScaling(float scale, float keep)
{
	AddScale(scale);
	AddTime(keep);
}

//==========================================
//  倍率の加算
//==========================================
void CGameTime::AddScale(float scale)
{
	if (m_fScale + scale > 0.0f)
	{
		m_fScale += scale;
	}
}

//==========================================
//  倍率時間の加算
//==========================================
void CGameTime::AddTime(float keep)
{
	m_fScaleTime += keep;
}

//==========================================
//  倍率と時間の設定
//==========================================
void CGameTime::SetScaling(float scale, float keep)
{
	SetScale(scale);
	SetTime(keep);
}

//==========================================
//  倍率の設定
//==========================================
void CGameTime::SetScale(float scale)
{
	if (scale > 0.0f)
	{
		m_fScale = scale;
	}
}

//==========================================
//  倍率時間の設定
//==========================================
void CGameTime::SetTime(float keep)
{
	m_fScaleTime = keep;
}

//==========================================
//  倍率適用時間
//==========================================
void CGameTime::Scaling()
{
	// 倍率適用時間
	if (m_fScaleTime <= 0.0f)
	{
		// 時間をリセット
		m_fScaleTime = 0.0f;

		// 倍率をリセット
		m_fScale = 1.0f;

		return;
	}

	// 時間を更新
	m_fScaleTime -= m_fDelta;
}
