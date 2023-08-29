#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//コンストラクタ
Controller::Controller(GameObject* parent)
	:GameObject(parent, "Controller")
{
	transform_.position_ = XMFLOAT3(7.0f, 0.0f, 7.0f);
	transform_.rotate_.x = 45.0f;
}

//デストラクタ
Controller::~Controller()
{
}

//初期化
void Controller::Initialize()
{
}

//更新
void Controller::Update()
{
	//回転処理
	InputRotate();

	//移動処理
	InputMove();

	//カメラの設定
	SetCamera();
}

//描画
void Controller::Draw()
{
}

//開放
void Controller::Release()
{
}

void Controller::InputRotate()
{
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 2.0f;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 2.0f;
	}
	if (Input::IsKey(DIK_UP)) {
		transform_.rotate_.x += 2.0f;
		if (transform_.rotate_.x >= 89.0f) transform_.rotate_.x = 89.0f;
	}
	if (Input::IsKey(DIK_DOWN)) {
		transform_.rotate_.x -= 2.0f;
		if (transform_.rotate_.x <= 0.0f) transform_.rotate_.x = 0.0f;
	}
}

void Controller::InputMove()
{
	//1フレーム当たりの移動量（ベクトル）
	XMVECTOR vMoveFoward = { 0.0f, 0.0f, 0.1f, 0.0f };	//奥方向に0.1m

	//1フレーム当たりの移動量（ベクトル）
	XMVECTOR vMoveRight = { 0.1f, 0.0f, 0.0f, 0.0f };	//横方向に0.1m

	//y軸の回転行列
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	//移動ベクトルを変形（向いている方向）
	vMoveFoward = XMVector3TransformCoord(vMoveFoward, mRotY);
	vMoveRight = XMVector3TransformCoord(vMoveRight, mRotY);

	//現在地情報をベクトル型に変換
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	if (Input::IsKey(DIK_W))		//前
	{
		vPos += vMoveFoward;						//移動
		XMStoreFloat3(&transform_.position_, vPos); //現在位置の更新
	}
	if (Input::IsKey(DIK_S))		//後ろ
	{
		vPos -= vMoveFoward;						//移動
		XMStoreFloat3(&transform_.position_, vPos);	//現在位置の更新
	}

	if (Input::IsKey(DIK_D))		//右
	{
		vPos += vMoveRight;							//移動
		XMStoreFloat3(&transform_.position_, vPos); //現在位置の更新
	}
	if (Input::IsKey(DIK_A))		//左
	{
		vPos -= vMoveRight;							//移動
		XMStoreFloat3(&transform_.position_, vPos); //現在位置の更新
	}
}

void Controller::SetCamera()
{
	XMVECTOR vCam = { 0, 0, 0, 0 };		//カメラの位置ベクトル
	XMVECTOR vTarget = { 0, 0, 0, 0 };	//カメラの焦点ベクトル

	//回転を表す行列
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

	vCam = { 0, 0, -10, 0 };
	vCam = XMVector3TransformCoord(vCam, mRotX);
	vCam = XMVector3TransformCoord(vCam, mRotY);

	//現在地情報をベクトル型に変換
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	//カメラを設定
	Camera::SetTarget(transform_.position_);
	Camera::SetPosition(vPos + vCam);
}