#pragma once
#include <dInput.h>
#include <DirectXMath.h>
#include "SafetyMacro.h"

//リンカ
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

using namespace DirectX;

namespace Input {
	//初期化
	void Initialize(HWND hWnd);
	//更新
	void Update();
	//解放
	void Release();

	//----------キーボードの関数----------//
	
	//キーが押されているか
	bool IsKey(int keyCode);
	//キーが押された瞬間か
	bool IsKeyDown(int keyCode);
	//キーが離された瞬間か
	bool IsKeyUp(int keyCode);

	//----------マウスの関数----------//

	//マウスが押されているか
	bool IsMouseButton(int buttonCode);
	//マウスが押された瞬間か
	bool IsMouseButtonDown(int buttonCode);
	//マウスが離された瞬間か
	bool IsMouseButtonUp(int buttonCode);
	//マウスの位置を指定
	void SetMousePosition(int x, int y);
	//マウスの位置
	XMFLOAT3 GetMousePosition();
	//マウスの移動量
	XMFLOAT3 GetMouseMove();
};