#pragma once
#include <DirectXMath.h>

using namespace DirectX;

//位置、向き、拡大率などを管理するクラス
class Transform {
	XMMATRIX matTranslate_;	//移動行列
	XMMATRIX matRotate_;	//回転行列	
	XMMATRIX matScale_;		//拡大行列

public:
	XMFLOAT3 position_;	//位置
	XMFLOAT3 rotate_;	//向き
	XMFLOAT3 scale_;	//拡大率

	Transform* pParent_;//親オブジェクトのTransform

	//コンストラクタ
	Transform();

	//デストラクタ
	~Transform();

	//各行列の計算
	void Calclation();

	//ワールド行列を取得
	XMMATRIX GetWorldMatrix();

	//法線変形用行列を取得
	XMMATRIX GetNormalMatrix();

	//親オブジェクトの登録
	void SetParentTransform(Transform* p) { pParent_ = p; };
};

//-------------------------------------
//DirectXの変数（構造体）計算用の演算子
//-------------------------------------

//XMFLOAT3同士の加算
inline XMFLOAT3 operator +(const XMFLOAT3& f1, const XMFLOAT3& f2) {
	return XMFLOAT3(f1.x + f2.x, f1.y + f2.y, f1.z + f2.z);
};
//XMFLOAT3同士の減算
inline XMFLOAT3 operator -(const XMFLOAT3& f1, const XMFLOAT3& f2) {
	return XMFLOAT3(f1.x - f2.x, f1.y - f2.y, f1.z - f2.z);
};
