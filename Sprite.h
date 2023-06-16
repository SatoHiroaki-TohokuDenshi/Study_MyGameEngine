#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"

#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ p->Release(); p = nullptr;}

using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER {
	XMMATRIX	matW;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;	//位置情報
	XMVECTOR uv;		//UV座標
};

class Sprite {
protected:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	Texture* pTexture_;				//テクスチャ情報
	int indexNum_;					//頂点インデックスの要素数
public:
	Sprite();
	~Sprite();
	//初期化
	virtual HRESULT Initialize();

	//描画
	void Draw(XMMATRIX& worldMatrix);

	//開放
	void Release();

	void PassInfoConstantBuffer(XMMATRIX& worldMatrix);
};

