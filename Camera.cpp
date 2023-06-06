#include "Camera.h"

//変数
namespace Camera {
	XMVECTOR position_;		//カメラの位置（視点）
	XMVECTOR target_;		//見る位置（焦点）
	XMMATRIX viewMatrix_;	//ビュー行列
	XMMATRIX projMatrix_;	//プロジェクション行列
};

//初期化
void Camera::Initialize(int winW, int winH) {
	position_ = XMVectorSet(0, 3, -10, 0);	//カメラの位置
	target_   = XMVectorSet(0, 0,   0, 0);	//カメラの焦点
	//プロジェクション行列
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)winW / (FLOAT)winH, 0.1f, 100.0f);
}

//更新
void Camera::Update() {
	//ビュー行列の作成
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

//位置を設定
void Camera::SetPosition(XMVECTOR position) {
	position_ = position;

}

void Camera::SetPosition(XMFLOAT3 position) {
	Camera::SetPosition(XMLoadFloat3(&position));
}

//焦点を設定
void Camera::SetTarget(XMVECTOR target) {
	target_ = target;
}

void Camera::SetTarget(XMFLOAT3 target) {
	Camera::SetTarget(XMLoadFloat3(&target));
}

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() {
	return viewMatrix_;
}

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix() {
	return projMatrix_;
}