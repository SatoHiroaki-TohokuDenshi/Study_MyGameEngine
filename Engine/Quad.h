#pragma once

#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"
#include <vector>
#include "Transform.h"

using namespace DirectX;

//コンスタントバッファーに渡す情報をまとめた構造体
struct CONSTANT_BUFFER {
	XMMATRIX	matWVP;
	XMMATRIX	matNormal; //matWからNormal用に改名
};

struct VERTEX {
	XMVECTOR postion;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Quad {
protected:
	int vertexNum_;
	std::vector<VERTEX> vertices_;	//頂点情報
	int indexNum_;					//インデックス数
	std::vector<int> index_;		//インデックス情報

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;
public:
	Quad();
	~Quad();
	//初期化
	HRESULT Initialize();
	//描画
	void Draw(Transform& transform);
	//開放
	void Release();

private:
	//---------Initialize関数から呼ばれる関数---------
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();
	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture();

	//---------Draw関数から呼ばれる関数---------
	void PassDataToCB(Transform transform);	//コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();
};