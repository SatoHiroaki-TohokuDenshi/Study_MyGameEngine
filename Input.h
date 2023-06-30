#pragma once
#include <dInput.h>

//リンカ
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

//解放マクロ
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input {
	//初期化
	void Initialize(HWND hWnd);
	//更新
	void Update();
	//キーの検出
	//引数：キーの番号
	//戻値：true押されている　false押されていない
	bool IsKey(int keyCode);
	//解放
	void Release();
};