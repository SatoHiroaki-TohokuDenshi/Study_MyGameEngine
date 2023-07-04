#pragma once
#include <dInput.h>
#include "SafetyMacro.h"

//リンカ
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

namespace Input {
	//初期化
	void Initialize(HWND hWnd);
	//更新
	void Update();

	/// <summary>キーが押されているか</summary>
	/// <param name="keyCode">調べたいキーの番号</param>
	/// <returns>押されていたらtrue</returns>
	bool IsKey(int keyCode);
	
	/// <summary>キーが押されたか</summary>
	/// <param name="keyCode">調べたいキーの番号</param>
	/// <returns>押された瞬間ならtrue</returns>
	bool IsKeyDown(int keyCode);

	/// <summary>キーが離されたか</summary>
	/// <param name="keyCode">調べたいキーの番号</param>
	/// <returns>離された瞬間ならtrue</returns>
	bool IsKeyUp(int keyCode);
	//解放
	void Release();
};