//==========================================
//
//  フェードクラス(fade.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _FADE_H_
#define _FADE_H_
#include "object2D.h"

//==========================================
//  フェードクラス定義
//==========================================
class CFade : public CObject2D
{
public:
	enum MODE
	{
		MODE_NONE = 0,
		MODE_IN, //フェードイン
		MODE_OUT, //フェードアウト
		MODE_MAX
	};

	CFade(int nPriority = 7); //コンストラクタ
	~CFade(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	bool GetState(void) { return m_bFinish; }
	MODE GetMode(void) { return m_Mode; }

	//静的メンバ関数
	static CFade *Create(int nTime, MODE mode);

private:

	//メンバ変数
	bool m_bFinish; //フェード終了フラグ
	int m_nTime; //フェードにかかる時間
	int m_nCounter; //フェードカウンター
	float m_fAlpha; //不透明度の割合
	MODE m_Mode; //フェードモード

};

#endif
