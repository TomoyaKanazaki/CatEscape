//==========================================
//
//  ゲームシーンのカメラ(camera_game.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_GAME_H_
#define _CAMERA_GAME_H_
#include "camera.h"

//==========================================
//  クラス定義
//==========================================
class CCameraGame : public CCamera
{
public:

	//メンバ関数
	CCameraGame();
	~CCameraGame();

	HRESULT Init(void) override;
	void Update(void) override;

	void SetQuake(const D3DXVECTOR3& range, float time) override;
	void AddQuake(const D3DXVECTOR3& range, float time = 0.0f) override;

private:

	//メンバ関数
	void MovePlayer(void);
	void LockBoss(void);
	void LockRush();
	void Quake();

	// 画面揺れ用の構造体
	struct QuakeData
	{
		D3DXVECTOR3 rangeR; // 注視点の揺れ
		D3DXVECTOR3 rangeV; // 視点の揺れ
		float time; // 継続時間
	};

	// メンバ変数
	QuakeData m_Quake; // 揺れ情報

};

#endif
