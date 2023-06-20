#pragma once
#include <d3d11.h>
#include <cassert>

//リンカ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//安全に開放するマクロ
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

enum SHADER_TYPE {
	SHADER_3D = 0,
	SHADER_2D,
	SHADER_MAX,
};

struct ShaderBundle {
	ID3D11VertexShader* pVertexShader_;			//頂点シェーダー
	ID3D11PixelShader* pPixelShader_;			//ピクセルシェーダー
	ID3D11RasterizerState* pRasterizerState_;	//ラスタライザー
	ID3D11InputLayout* pVertexLayout_;			//頂点インプットレイアウト
};

namespace Direct3D {
	extern ID3D11Device* pDevice_;			//デバイス
	extern ID3D11DeviceContext* pContext_;	//デバイスコンテキスト

	//初期化
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//シェーダー準備
	HRESULT InitShader();
	HRESULT Init3DShader();
	HRESULT Init2DShader();

	//コンテキストの設定
	//引数  0:3D用シェーダー  1:2D用シェーダー
	void SetContext(SHADER_TYPE type);

	//描画開始（下準備：画面を単色で初期化する）
	void BeginDraw();

	//描画終了（完了：画面を表示させる）
	void EndDraw();

	//解放
	void Release();
};