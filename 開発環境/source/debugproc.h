//==========================================================
//
//デバッグ表示処理 [debugproc.h]
//Author Ibuki Okusada
// Added by Tomoya Kanazaki
//
//==========================================================
#ifndef _DEBUGPROC_H_		//このマクロが定義されていない場合
#define _DEBUGPROC_H_


//**********************************************************
//ネームスペースの定義
//**********************************************************
namespace DebugProc
{
	void Init(void); // 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void); // 描画処理
	void Print(const char *fmt, ...); // 文字列入力
};

#endif