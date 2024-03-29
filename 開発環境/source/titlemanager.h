//==========================================
//
//  タイトルマネージャ(titlemanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TITLEMANAGER_H_
#define _TITLEMANAGER_H_
#include "scene.h"

//==========================================
//  前方宣言
//==========================================
class CLight;
class CTitle;
class CDoll;
class CCamera;

//==========================================
//  タイトルマネージャクラス定義
//==========================================
class CTitleManager : public CScene
{
public:
	CTitleManager(); //コンストラクタ
	~CTitleManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	//メンバ変数
	int m_nCntScene;

	//静的メンバ変数
	static CLight *m_pLight;
	static CTitle *m_pTitle;
	static CDoll *m_pDoll;
	static CCamera* m_pCamera;

};

#endif
