//==========================================
//
//  ゲーム全般の制御(main.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#include <time.h>
#include "manager.h"
#include "input.h"

//==========================================
//  プロトタイプ宣言
//==========================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//==========================================
//  メイン関数
//==========================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hInstancePrev*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	//デバッグ
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX), //WNDCLASSEXのメモリサイズ
		CS_CLASSDC, //ウィンドウのスタイル
		WindowsProc, //ウィンドウプロシージャ
		0, //0にする(通常は使用しない)
		0, //0にする(通常は使用しない)
		hInstance, //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION), //タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW), //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1), //クライアントの背景色
		NULL, //メニューバー
		CLASS_NAME, //ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION), //ファイルのアイコン
	};
	HWND hWnd; //ウィンドウハンドル
	MSG msg; //メッセージを格納する変数
	DWORD dwCurrentTime; //現在時刻
	DWORD dwExecLastTime; //最後に処理した時刻
	DWORD dwFrameCount; //フレームカウント
	DWORD dwFPSLastTime; //最後にFPSを計測した時間

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx
	(
		0, //拡張ウィンドウスタイル
		CLASS_NAME, //ウィンドウクラスの名前
		WINDOW_NAME, //ウィンドウの名前
		WS_OVERLAPPEDWINDOW, //ウィンドウスタイル
		CW_USEDEFAULT, //ウィンドウの左上X座標
		CW_USEDEFAULT, //ウィンドウの左上Y座標
		(rect.right - rect.left), //ウィンドウの幅
		(rect.bottom - rect.top), //ウィンドウの高さ
		NULL, //新規ウィンドウのハンドル
		NULL, //メニューハンドルまたは子ウィンドウID
		hInstance, //インスタンスハンドル
		NULL
	);

	//ローカル変数宣言
	CManager *pManager = NULL;

	//メモリの確保
	pManager = CManager::GetInstance();

	//初期化処理
	if (pManager != NULL)
	{
#ifdef _DEBUG
		if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
		{
			//初期化処理に失敗した場合
			return -1;
		}
#else
		if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
		{
			//初期化処理に失敗した場合
			return -1;
		}
#endif
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0; //初期化
	dwExecLastTime = timeGetTime(); //現在時刻を取得

	//デバッグ表示用の数値の設定
	dwFrameCount = 0; //初期化
	dwFPSLastTime = timeGetTime(); //現在時刻を取得

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow); //ウィンドウの表示状態を設定
	UpdateWindow(hWnd); //クライアント領域

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			//windowsの処理
			if (msg.message == WM_QUIT)
			{
				//WM_QUITメッセージを受け取った場合
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg); //仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg); //ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{
			//DirectXの処理
			dwCurrentTime = timeGetTime(); //現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				//0.5秒経過
				int nFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				CManager::GetInstance()->GetInstance()->SetFPS(nFPS);
				dwFPSLastTime = dwCurrentTime; //FPSを測定した時間
				dwFrameCount = 0; //フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				//60分の1秒経過
				dwExecLastTime = dwCurrentTime;
				dwFrameCount++;

				if (pManager != NULL)
				{
					//更新処理
					pManager->Update();

					//描画処理
					pManager->Draw();

#if _DEBUG
					if (pManager->GetKeyboard()->GetTrigger(DIK_F2))
					{
						pManager->Uninit();
						delete pManager;
						pManager = NULL;
					}
#endif
				}
				else
				{
					pManager = new CManager;
					pManager->Init(hInstance, hWnd, TRUE);
				}
			}
		}
	}

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウのクラスの解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	//インスタンスの破棄
	if (pManager != NULL)
	{
		pManager->Uninit();
		CManager::Release();
	}

	return (int)msg.wParam;
}

//==========================================
//  ウィンドウプロージャ
//==========================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY: //ウィンドウ破棄のメッセージ
					 //WM_DUITのメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //キー押下メッセージ
		switch (wParam)
		{
		case VK_ESCAPE:
			//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_CLOSE: //キー押下メッセージ
				   //ウィンドウを破棄する(WM_DESTROYメッセージを送る)
		DestroyWindow(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); //既定の処理を返す
}
