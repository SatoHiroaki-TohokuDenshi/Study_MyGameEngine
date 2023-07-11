//インクルード
#include <Windows.h>
#include <cstdlib>
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/RootJob.h"

#pragma comment(lib, "winmm.lib")

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

RootJob* pRootJob = nullptr;

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);				//この構造体のサイズ
	wc.hInstance = hInstance;					//インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;			//ウィンドウクラス名
	wc.lpfnWndProc = WndProc;					//ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;			//スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);	//小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//マウスカーソル
	wc.lpszMenuName = NULL;						//メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	RegisterClassEx(&wc); //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,			//ウィンドウクラス名
		"サンプルゲーム",		//タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW,	//スタイル（普通のウィンドウ）
		CW_USEDEFAULT,			//表示位置左（おまかせ）
		CW_USEDEFAULT,			//表示位置上（おまかせ）
		winW,					//ウィンドウ幅
		winH,					//ウィンドウ高さ
		NULL,					//親ウインドウ（なし）
		NULL,					//メニュー（なし）
		hInstance,				//インスタンス
		NULL					//パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	//Direct3D初期化
	HRESULT hr;
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr)) {
		//エラー起きたら強制終了
		PostQuitMessage(0);
	}

	//DirectInputの初期化
	Input::Initialize(hWnd);

	//カメラの初期化
	Camera::Initialize();

	pRootJob = new RootJob;
	pRootJob->Initialize();

	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else {
			timeBeginPeriod(1);							//正確に計るためのコマンド
			static DWORD countFps = 0;					//FPS
			static DWORD startTime = timeGetTime();		//プログラムの開始時刻
			DWORD nowTime = timeGetTime();				//現在時刻
			static DWORD lastUpdateTime = nowTime;		//最後の更新

			//1秒経っていたら
			if (nowTime - startTime >= 1000) {
				char str[16];
				wsprintf(str, "%u", countFps);
				SetWindowText(hWnd, str);

				countFps = 0;
				startTime = nowTime;
			}

			//前回の更新から1/60秒経過していない場合
			if ((nowTime - lastUpdateTime) * 60 <= 1000) {
				continue;
			}
			lastUpdateTime = nowTime;

			countFps++;
			timeEndPeriod(1);

			//★ゲームの処理
			//カメラの更新
			Camera::Update();
			//Inputの更新
			Input::Update();
			//オブジェクトの更新
			pRootJob->UpdateSub();

			//★描画処理
			Direct3D::BeginDraw();		//バックバッファの初期化

			//描画するもの
			//RootJobを介して、全部のDraw関数を呼ぶ
			pRootJob->DrawSub();

			Direct3D::EndDraw();		//バッファの入れ替え
		}
	}
	pRootJob->ReleaseSub();
	SAFE_DELETE(pRootJob);
	Input::Release();
	Direct3D::Release();

	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
//返り値　LRESULT（ここ以外では特に使わないから気にしなくてヨシ）
//CALLBACK　特定の状況で呼ばれるよって宣言（通常は勝手に呼ばれたりしない）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:			//ウィンドウを閉じたとき
		//プログラム終了
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}