//==========================================
//
//  画面遷移クラス(scene.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _SCENE_H_
#define _SCENE_H_

//==========================================
//  画面遷移クラス定義
//==========================================
class CScene
{
public:
	CScene(); //コンストラクタ
	~CScene(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

};

#endif
