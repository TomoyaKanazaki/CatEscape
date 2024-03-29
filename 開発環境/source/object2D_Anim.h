//==========================================
//
//  アニメーション2Dクラス(object2D_Anim.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT2D_ANIM_H_
#define _OBJECT2D_ANIM_H_
#include "object2D.h"

//==========================================
//  アニメーション2Dクラス定義
//==========================================
class CObject2D_Anim : public CObject2D
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_U, //横方向のアニメーション
		TYPE_V //縦方向のアニメーション
	}UVTYPE;

	CObject2D_Anim(int nPriority = 3); //コンストラクタ
	~CObject2D_Anim(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	void SetAnim(int nPattern, int nInterval, bool bLoop, UVTYPE type);
	HRESULT SetTexPos(void);

	//静的メンバ関数
	static CObject2D_Anim *Create(int nPattern, int nInterval, bool bLoop, UVTYPE type);

private:

	//メンバ変数
	UVTYPE m_Type;
	int m_nNumPattern; //パターン数
	int m_nAnimPattern; //現在のパターン
	int m_nUpdateFrame; //更新間隔
	int m_nAnimCounter; //アニメーションカウンター
	bool m_bLoop; //ループの有無

};

#endif
