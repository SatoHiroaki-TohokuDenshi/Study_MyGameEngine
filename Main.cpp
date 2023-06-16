//インクルード
#include <Windows.h>
#include "Direct3D.h"
#include "Camera.h"
#include "Quad.h"
#include "Dice.h"

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";			//ウィンドウクラス名
const char* WIN_TITLE_NAME = "サンプルゲーム";		//タイトルバーの表示内容
const int WINDOW_WIDTH = 800;		//ウィンドウの幅
const int WINDOW_HEIGHT = 600;		//ウィンドウの高さ

//ポリゴン表示（お試し）
Quad* pQuad = nullptr;
Dice* pDice = nullptr;

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;          //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）

	RegisterClassEx(&wc);  //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,      //ウィンドウクラス名
		WIN_TITLE_NAME,      //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,                //ウィンドウ幅
		winH,                //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr = S_OK;

	//Direct3D初期化
	hr = Direct3D::Initialize(winW, winH, hWnd, true);
	if (FAILED(hr)) {
		//エラー処理
		MessageBox(nullptr, "Direct3Dの初期化に失敗しました", "エラー", MB_OK);
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}

	//カメラの初期化
	Camera::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//ポリゴン表示（お試し）
	pQuad = new Quad;
	hr = pQuad->Initialize();
	if (FAILED(hr)) {
		//エラー処理
		MessageBox(nullptr, "インスタンス\"Quad\"の初期化に失敗しました", "エラー", MB_OK);
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	pDice = new Dice;
	hr = pDice->Initialize();
	if (FAILED(hr)) {
		//エラー処理
		MessageBox(nullptr, "インスタンス\"Dice\"の初期化に失敗しました", "エラー", MB_OK);
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}

	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり（ウィンドウを閉じるなどの処理を優先）
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			Camera::Update();
			//ゲームの処理

			//描画処理
			Direct3D::BeginDraw();		//バックバッファの初期化

			static XMMATRIX mat = XMMatrixIdentity();
			mat *= XMMatrixRotationX(XMConvertToRadians(0.02f)) * XMMatrixRotationY(XMConvertToRadians(0.02f)) * XMMatrixRotationZ(XMConvertToRadians(0.02f));
			pQuad->Draw(mat);
			//pDice->Draw(mat);

			Direct3D::EndDraw();		//バッファの入れ替え
		}
	}

	//解放処理
	SAFE_RELEASE(pQuad);
	SAFE_DELETE(pQuad);
	SAFE_RELEASE(pDice);
	SAFE_DELETE(pDice);
	Direct3D::Release();

	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
//返り値　LRESULT（ここ以外では特に使わないから気にしなくてヨシ）
//CALLBACK　特定の状況で呼ばれるよって宣言（通常は勝手に呼ばれたりしない）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// 自分で処理を定義したいメッセージ
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	//デフォルトの処理でいいメッセージ
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

