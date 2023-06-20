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
	
}

//ワールド行列を取得
XMMATRIX Transform::GetWorldMatrix() {
	return ;
}