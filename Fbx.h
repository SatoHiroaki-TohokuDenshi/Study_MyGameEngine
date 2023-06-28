#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include "Texture.h"

//リンカ
#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Fbx {
	//コンスタントバッファに渡す情報をまとめた構造体
	struct CONSTANT_BUFFER {
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	//頂点情報
	struct VERTEX {
		XMVECTOR position;
		XMVECTOR uv;
	};

	//マテリアル
	struct MATERIAL {
		Texture* pTexture;
	};

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;
	int* indexCount_;

public:
	Fbx();
	//読み込み
	HRESULT Load(std::string fileName);
	//描画
	void    Draw(Transform& transform);
	//開放
	void    Release();

private:
	//---------Initialize関数から呼ばれる関数---------
	//頂点バッファ準備
	HRESULT InitVertex(fbxsdk::FbxMesh* mesh);

	//インデックスバッファ準備
	HRESULT InitIndex(fbxsdk::FbxMesh* mesh);

	//コンスタントバッファ準備
	HRESULT InitConstantBuffer();

	//マテリアル準備
	void InitMaterial(fbxsdk::FbxNode* pNode);

	//---------Draw関数から呼ばれる関数---------
	void PassDataToCB(Transform transform);	//コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();
};