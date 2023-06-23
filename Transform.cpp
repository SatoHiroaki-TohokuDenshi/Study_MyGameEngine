#include "Transform.h"

//コンストラクタ
Transform::Transform() :
	matTranslate_(XMMatrixIdentity()), matRotate_(XMMatrixIdentity()), matScale_(XMMatrixIdentity()),
	position_(0.0f, 0.0f, 0.0f), rotate_(0.0f, 0.0f, 0.0f), scale_(1.0f, 1.0f, 1.0f)
{
}

//デストラクタ
Transform::~Transform() {

}

//各行列の計算
void Transform::Calclation() {
	//移動行列
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);
	//回転行列
	matRotate_ = XMMatrixRotationZ(rotate_.z) * XMMatrixRotationX(rotate_.x) * XMMatrixRotationY(rotate_.y);
	//拡大縮小行列
	matScale_ = XMMatrixScaling(rotate_.x, rotate_.y, rotate_.z);
}

//ワールド行列を取得
XMMATRIX Transform::GetWorldMatrix() {
	return matScale_ * matRotate_ * matTranslate_;
}

//法線変形用行列を取得
XMMATRIX Transform::GetNormalMatrix() {
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}