#pragma once
#include <d3d11.h>

//リンカ
#pragma comment(lib, "d3d11.lib")

namespace Direct3D {
	//初期化
	void Initialize(int winW, int winH, HWND hWnd);

	//描画開始（下準備：画面を単色で初期化する）
	void BeginDraw();

	//描画終了（完了：画面を表示させる）
	void EndDraw();

	//解放
	void Release();
};