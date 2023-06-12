#include "Dice.h"
#include "Camera.h"

Dice::Dice() :
	pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr), indexNum_(0)
{

}

Dice::~Dice() {

}

HRESULT Dice::Initialize() {
	HRESULT hr = S_OK;

	// 頂点情報
	VERTEX vertices[] = {
		//１
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f,  0.0f, 0.0f, 0.0f)},		//1
		{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f)},		//2
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},		//3
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f)},		//4
		//２
		{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f)},		//5
		{XMVectorSet( 1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.5f,  0.0f, 0.0f, 0.0f)},		//6
		{XMVectorSet( 1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.5f,  0.5f, 0.0f, 0.0f)},		//7
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},		//8
		//３
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.5f,  0.0f, 0.0f, 0.0f)},		//9
		{XMVectorSet( 1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f)},		//10
		{XMVectorSet( 1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f)},		//11
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.5f,  0.5f, 0.0f, 0.0f)},		//12
		//４
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.75f, 0.0f, 0.0f, 0.0f)},		//13
		{XMVectorSet( 1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(1.0f,  0.0f, 0.0f, 0.0f)},		//14
		{XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f,  0.5f, 0.0f, 0.0f)},		//15
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.75f, 0.5f, 0.0f, 0.0f)},		//16
		//５
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.0f,  0.5f, 0.0f, 0.0f)},		//17
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},		//18
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f)},		//19
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.0f,  1.0f, 0.0f, 0.0f)},		//20
		//６
		{XMVectorSet( 1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f)},		//21
		{XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.5f,  0.5f, 0.0f, 0.0f)},		//22
		{XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.5f,  1.0f, 0.0f, 0.0f)},		//23
		{XMVectorSet( 1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.25f, 1.0f, 0.0f, 0.0f)},		//24
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
		0,  2, 3,  0, 1, 2,	//1
		5,  7, 8,  5, 6, 7,	//2
		9, 11,12,  9,10,11,	//3
		13,15,16, 13,14,15,	//4
		17,19,20, 17,18,19,	//5
		21,23,24, 21,22,23	//6
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

void Dice::Draw(XMMATRIX& worldMatrix) {
	PassInfoConstantBuffer(worldMatrix);

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	//描画!!
	Direct3D::pContext_->DrawIndexed(indexNum_, 0, 0);
}

void Dice::Release() {
	pTexture_->Release();
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
}

void Dice::PassInfoConstantBuffer(XMMATRIX& worldMatrix) {
	//コンスタントバッファに渡す情報
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開
}