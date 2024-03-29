//==========================================
//
//  カメラクラス(camera.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//==========================================
//  カメラクラスの定義
//==========================================
class CCamera
{
public:
	CCamera(); //コンストラクタ
	~CCamera(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);
	void Uninit(void);
	virtual void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetPosR(void) { return m_posR; }
	D3DXVECTOR3 GetPosV(void) { return m_posV; }
	void SetPosR(D3DXVECTOR3 pos) { m_posR = pos; }
	void SetPosV(D3DXVECTOR3 pos) { m_posV = pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXMATRIX GetMtxPro(void) { return m_mtxProjection; }
	D3DXMATRIX CreateViewMatrix(void);
	void SwitchDebug(void) { m_bDebug = !m_bDebug; }
	bool GetDebug(void) { return m_bDebug; }
	bool OnScreen(const D3DXVECTOR3 pos) const; // スクリーン内の判定
	D3DXVECTOR3 WorldToScreen(const D3DXVECTOR3& posWorld) const;
	//D3DXVECTOR3 ScreenToWorld(const D3DXVECTOR3& posScreen) const;
	virtual void SetQuake(const D3DXVECTOR3& range, float time) {};
	virtual void AddQuake(const D3DXVECTOR3& range, float time) {};

protected:
#define CAMERA_DISTANCE (-500.0f) //視点からプレイヤーの距離
#define R_HEIGHT (10.0f) //視点の高さ
#define V_HEIGHT (130.0f) //注視点の高さ
#define MAX_ROT (D3DX_PI * 0.99f) //視点の限界角
#define MIN_ROT (D3DX_PI * 0.01f) //視点の限界角
#define DEFAULT_FAV (45.0f) //視野角の規定値
#define MAX_FAV (54.0f) //視野角の規定値

	//メンバ関数
	void FirstPerson(void);
	void ThirdPerson(void);
	void Move(void);

	//メンバ変数
	D3DXVECTOR3 m_posV; //視点
	D3DXVECTOR3 m_posR; //注視点
	D3DXVECTOR3 m_vecU; //上方向ベクトル
	D3DXMATRIX m_mtxProjection; //プロジェクションマトリックス
	D3DXMATRIX m_mtxView; //ビューマトリックス
	D3DXVECTOR3 m_rot; //Xの計算に使用する角度
	D3DXVECTOR3 m_diff; //プレイヤー座標との差分
	float m_fFov; //視野角
	bool m_bDebug; //デバッグフラグ

};

#endif
