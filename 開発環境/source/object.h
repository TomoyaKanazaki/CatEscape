//==========================================
//
//  オブジェクトクラス(object.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//==========================================
//  マクロ定義
//==========================================
#define PRIORITY_NUM (8) //優先順位の最大数

//==========================================
//  オブジェクトクラス生成
//==========================================
class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0, //不使用
		TYPE_PLAYER, //プレイヤー
		TYPE_ENEMY, //敵
		TYPE_BOSS, //ボス
		TYPE_BG, //背景
		TYPE_MAP, //地形
		TYPE_NUMBER, //数字
		TYPE_FIELD, //床
		TYPE_FADE, //フェード
		TYPE_ORBIT, //軌跡
		METHOD_MAX
	}TYPE;

	enum STATE
	{
		NORMAL = 0, //通常状態
		ATTACKED, // 被撃状態
		INVINCIBLE, // 無敵状態
		MAX
	};

	CObject(int nPriority = 3); //コンストラクタ
	virtual ~CObject(); //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	CObject *GetNext(void) { return m_pNext; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetOldPos(void) { return m_oldPos; }
	D3DXVECTOR3 GetOldRot(void) { return m_oldRot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	TYPE GetType(void) { return m_type; }
	STATE GetObjState(void) { return m_ObjState; }
	bool GetMap(void) { return m_bMap; }
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }
	void SetMove(const D3DXVECTOR3& move) { m_move = move; }
	void SetSize(const D3DXVECTOR3& size) { m_size = size; }
	void SetType(TYPE type) { m_type = type; }
	void SetMap(void) { m_bMap = true; }
	void SetState(STATE state) { m_ObjState = state; }

	// 下層情報の抜出用
	virtual float GetHitLength() { return 0.0f; }
	virtual D3DXVECTOR3 GetCenterPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }

	//静的メンバ関数
	static CObject *GetTop(int nPriority) { return m_apTop[nPriority]; }
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static int GetNum(void) { return m_nNumObject; }

protected:

	//メンバ関数
	bool OnScreen(void);
	void Release(void);
	void SetDeath(const bool frag) { m_bDeath = frag; }

	//メンバ変数
	D3DXVECTOR3 m_pos; //オブジェクトの中心座標
	D3DXVECTOR3 m_rot; //オブジェクトの向き
	D3DXVECTOR3 m_move; //オブジェクトの移動量
	D3DXVECTOR3 m_size; //オブジェクトのサイズ
	D3DXVECTOR3 m_oldPos; //オブジェクトの前回座標
	D3DXVECTOR3 m_oldRot; //オブジェクトの前回角度
	float m_fDeltaTime; //前回の更新からかかった時間
	STATE m_ObjState; //状態

private:

	//メンバ変数
	CObject *m_pNext; //次のオブジェクトのポインタ
	CObject *m_pPrev; //前のオブジェクトのポインタ
	int m_nPriority; //描画優先順位
	TYPE m_type; //種類
	bool m_bDeath; //死亡フラグ
	bool m_bMap; //マップに関係するオブジェクトか否か

	//静的メンバ変数
	static int m_nNumObject; //オブジェクトの総数
	static CObject *m_apTop[PRIORITY_NUM]; //先頭オブジェクトのポインタ配列
	static CObject *m_apCur[PRIORITY_NUM]; //最後尾オブジェクトのポインタ配列

};

#endif
