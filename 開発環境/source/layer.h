//==========================================
//
//  階層構造管理クラス(layer.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _LAYER_H_
#define _LAYER_H_

//==========================================
//  前方宣言
//==========================================
class CModel;

//==========================================
//  階層構造管理クラス定義
//==========================================
class CLayer
{
public:
	//階層構造の種類
	typedef enum
	{
		PLAYER_LAYER = 0, //プレイヤー構造
		ENEMY_LANTERN, // 提灯お化け
		ENEMY_UMBRELLA, // 唐笠お化け
		ENEMY_BOSS, // ボス
		BLADE, // 刀弾
		MAP_LAYER, //マップのやつ
		LAYERS_MAX
	}LAYERS;

	//階層構造のデータ
	typedef struct
	{
		int nNumModel; //モデル数
		int *pModelID; //使用するモデルのインデックス
		int *pParentID; //親モデルのインデックス
		D3DXVECTOR3 *pPos; //初期位置
		D3DXVECTOR3 *pRot; //初期角度
	}LAYERDATA;

	CLayer(); //コンストラクタ
	~CLayer(); //デストラクタ

	//静的メンバ関数
	static LAYERDATA *Set(LAYERS type);
	static void Load(void);
	static void UnLoad(void);

private:

	//静的メンバ変数
	static int m_nNumLayer; //階層構造情報数
	static LAYERDATA *m_pData; //階層構造情報

};

#endif
