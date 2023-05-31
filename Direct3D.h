#pragma once
#include <d3d11.h>

//リンカ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//安全に開放するマクロ
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Direct3D {
	extern ID3D11Device* pDevice;			//デバイス
	extern ID3D11DeviceContext* pContext;	//デバイスコンテキスト

	//初期化
	void Initialize(int winW, int winH, HWND hWnd);

	//シェーダー準備
	void InitShader();

	//描画開始（下準備：画面を単色で初期化する）
	void BeginDraw();

	//描画終了（完了：画面を表示させる）
	void EndDraw();

	//解放
	void Release();
};