#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"

using namespace DirectX;

class Sprite {
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
protected:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	Texture* pTexture_;				//テクスチャ情報
	int indexNum_;					//頂点インデックスの要素数
public:
	Sprite();
	virtual ~Sprite();
	virtual HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();

	void PassInfoConstantBuffer(XMMATRIX& worldMatrix);
};