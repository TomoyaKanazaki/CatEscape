//==========================================
//
//  リザルトマネージャ(resultmanager.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _RESULTMANAGER_H_
#define _RESULTMANAGER_H_
#include "scene.h"

//==========================================
//  前方宣言
//==========================================
class CLight;
class CCamera;
class CRunning;

//==========================================
//  タイトルマネージャクラス定義
//==========================================
class CResultManager : public CScene
{
public:
	CResultManager(); //コンストラクタ
	~CResultManager(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	// 静的メンバ関数
	static CRunning* GetPlayer() { return m_pRunning; }
	static CCamera* GetCamera() { return m_pCamera; }

private:

	//メンバ変数
	float m_fCntScene;
	int m_nRank;

	//静的メンバ変数
	static CLight* m_pLight;
	static CCamera* m_pCamera;
	static CRunning* m_pRunning;

};

#endif
