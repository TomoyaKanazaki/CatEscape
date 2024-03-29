//==========================================
//
//  アニメーション3Dクラス(object3D_Anim.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT3D_ANIM_H_
#define _OBJECT3D_ANIM_H_
#include "object3D.h"

//==========================================
//  アニメーション3Dクラス定義
//==========================================
class CObject3D_Anim : public CObject3D
{
public:
	enum UVTYPE
	{
		TYPE_NONE = 0,
		TYPE_U, //横方向のアニメーション
		TYPE_V //縦方向のアニメーション
	};

	CObject3D_Anim(int nPriority = 3); //コンストラクタ
	~CObject3D_Anim(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	void SetAnim(int nPattern, int nInterval, bool bLoop, UVTYPE type);
	int GetAnimPattern(void) { return m_nNumPattern; }
	HRESULT SetTexPos(void);

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
