#include "Dice.h"

Dice::Dice() :
    Quad()
{
}

Dice::~Dice() {

}

HRESULT Dice::Initialize() {
	HRESULT hr = S_OK;

	// 頂点情報
	VERTEX vertices[] = {
		//１
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f)},		//0
		{XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f)},		//1
		{XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},		//2
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f), XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f)},		//3
		//２
		{XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f)},		//4
		{XMVectorSet(1.0f,  1.0f,  1.0f, 0.0f), XMVectorSet(0.5f,  0.0f, 0.0f, 0.0f)},		//5
		{XMVectorSet(1.0f, -1.0f,  1.0f, 0.0f), XMVectorSet(0.5f,  0.5f, 0.0f, 0.0f)},		//6
		{XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},		//7
		//３
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f), XMVectorSet(0.5f,  0.0f, 0.0f, 0.0f)},		//8
		{XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f), XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f)},		//9
		{XMVectorSet(1.0f, -1.0f,  1.0f, 0.0f), XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f)},		//10
		{XMVectorSet(-1.0f, -1.0f,  1.0f, 0.0f), XMVectorSet(0.5f,  0.5f, 0.0f, 0.0f)},		//11
		//４
		{XMVectorSet(-1.0f,  1.0f,  1.0f, 0.0f), XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f)},		//12
		{XMVectorSet(1.0f,  1.0f,  1.0f, 0.0f), XMVectorSet(1.0f,  0.0f, 0.0f, 0.0f)},		//13
		{XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(1.0f,  0.5f, 0.0f, 0.0f)},		//14
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f)},		//15
		//５
		{XMVectorSet(-1.0f,  1.0f,  1.0f, 0.0f), XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f)},		//16
		{XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},		//17
		{XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f), XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f)},		//18
		{XMVectorSet(-1.0f, -1.0f,  1.0f, 0.0f), XMVectorSet(0.0f,  1.0f, 0.0f, 0.0f)},		//19
		//６
		{XMVectorSet(1.0f,  1.0f,  1.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},		//20
		{XMVectorSet(-1.0f,  1.0f,  1.0f, 0.0f), XMVectorSet(0.5f,  0.5f, 0.0f, 0.0f)},		//21
		{XMVectorSet(-1.0f, -1.0f,  1.0f, 0.0f), XMVectorSet(0.5f,  1.0f, 0.0f, 0.0f)},		//22
		{XMVectorSet(1.0f, -1.0f,  1.0f, 0.0f), XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f)},		//23
	};

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr)) {
		//エラー処理
		MessageBox(nullptr, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	//インデックス情報
	int index[] = {
		0, 2, 3,  0, 1, 2,	//1
		4, 6, 7,  4, 5, 6,	//2
		8,10,11,  8, 9,10,	//3
		12,14,15, 12,13,14,	//4
		16,18,19, 16,17,18,	//5
		20,22,23, 20,21,22	//6
	};
	indexNum_ = sizeof(index) / sizeof(int);

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr)) {
		//エラー処理
		MessageBox(nullptr, "インデックスバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}


	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr)) {
		//エラー処理
		MessageBox(nullptr, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	pTexture_ = new Texture;
	hr = pTexture_->Load("Assets\\dice.png");
	if (FAILED(hr)) {
		//エラー処理
		MessageBox(nullptr, "テクスチャの読み込みに失敗しました", "エラー", MB_OK);
		return hr;
	}

	return hr;
}
