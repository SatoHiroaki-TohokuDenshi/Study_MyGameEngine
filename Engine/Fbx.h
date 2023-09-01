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

//レイキャスト用構造体
struct RayCastData {
	XMFLOAT3 start;
	XMFLOAT3 dir;
	bool hit;
	float dist;
};

class Fbx {
	//コンスタントバッファに渡す情報をまとめた構造体
	struct CONSTANT_BUFFER {
		XMMATRIX matWVP;
		XMMATRIX matNormal;
		XMFLOAT4 color;
		int isTexture;
	};

	//頂点情報
	struct VERTEX {
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};

	//マテリアル
	struct MATERIAL {
		Texture* pTexture;
		XMFLOAT4	diffuse;
	};

	VERTEX* pVertices_;	//頂点情報
	int** ppIndex_;		//頂点番号

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
	void PassDataToCB(Transform transform, int i);	//コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline(int i);

public:
	/// <summary>レイキャストを計算する</summary>
	/// <param name="rayData">必要なデータの構造体</param>
	void RayCast(RayCastData& rayData);
};