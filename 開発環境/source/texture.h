//==========================================
//
//  テクスチャ管理クラス(texture.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//==========================================
//  マクロ定義
//==========================================
#define MAX_TEXTURE (256) //使用するテクスチャの最大数

//==========================================
//  テクスチャ管理クラス
//==========================================
class CTexture
{
public:
	//テクスチャの種類の列挙型定義
	enum TEXTURE
	{
		NUMBER = 0, //数字
		TITLE, //タイトル
		CLEAR, //ゲームクリア
		OVER, //ゲームオーバー
		FIELD, //床
		WATER, //水
		SKY, //空
		EFFECT, // エフェクト
		SLASH, // 斬撃エフェクト
		SPLASH, // 爆散エフェクト
		HIT, // ヒットエフェクト
		DEATH, // 死亡エフェクト
		BOSS1, // ボス出現エフェクト
		BOSS2, // ボス出現エフェクト
		BULLET, // 弾
		EXPLOSION, // 爆発
		LEAF, // 🍃
		PLAYER_FRAME, // 🍃用の枠
		ENEMY_FRAME, // 🔥用の枠
		FLAME, // 🔥
		RUSH, // 連撃
		TUTORIAL0, // チュートリアル
		TUTORIAL1, // チュートリアル
		STICK, // スティック
		BASE, // スティックベース
		TEXTURE_MAX
	};

	CTexture(); //コンストラクタ
	~CTexture(); //デストラクタ

	//メンバ関数
	HRESULT Load(void); //テクスチャのロード
	void UnLoad(void); //テクスチャの破棄
	int Regist(const char *pFilName); //テクスチャの登録
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx) { return m_apTexture[nIdx]; } //テクスチャの取得
	int GetNum(void) { return m_nNumAll; }

	//静的メンバ関数
	static bool GetLoadState(void) { return m_bLoad; }; //テクスチャの読み込み状態を取得

private:

	//メンバ変数
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE]; //テクスチャ情報
	char m_sFilePass[MAX_TEXTURE][256]; //既に読み込まれているテクスチャのパス
	int m_nNumAll; //テクスチャの総数

	//静的メンバ変数
	static bool m_bLoad;

};

#endif
