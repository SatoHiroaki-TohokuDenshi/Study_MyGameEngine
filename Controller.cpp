#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//コンストラクタ
Controller::Controller(GameObject* parent)
	:GameObject(parent, "Controller")
{
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
	}
	if (Input::IsKey(DIK_DOWN)) {
		transform_.rotate_.x -= 2.0f;
	}

	if (transform_.rotate_.x >=  60.0f) transform_.rotate_.x =  60.0f;
	if (transform_.rotate_.x <= -90.0f) transform_.rotate_.x = -89.0f;

	//現在地情報をベクトル型に変換
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	//transform_.rotate_.y度回転させる行列
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));

	//1フレーム当たりの移動量（ベクトル）
	XMVECTOR vMove = { 0.0f, 0.0f, 0.1f, 0.0f };     //奥方向に0.1m

	//1フレーム当たりの移動量（ベクトル）
	XMVECTOR vSwipe = { 0.1f, 0.0f, 0.0f, 0.0f };     //横方向に0.1m

	//移動ベクトルを変形（向いている方向）
	vMove = XMVector3TransformCoord(vMove, mRotY);
	vSwipe = XMVector3TransformCoord(vSwipe, mRotY);

	//移動処理
	if (Input::IsKey(DIK_W))
	{
		vPos += vMove;                              //移動
		XMStoreFloat3(&transform_.position_, vPos); //現在位置の更新
	}
	if (Input::IsKey(DIK_S))
	{
		vPos -= vMove;                              //移動
		XMStoreFloat3(&transform_.position_, vPos); //現在位置の更新
	}

	if (Input::IsKey(DIK_D))
	{
		vPos += vSwipe;                             //移動
		XMStoreFloat3(&transform_.position_, vPos); //現在位置の更新
	}
	if (Input::IsKey(DIK_A))
	{
		vPos -= vSwipe;                             //移動
		XMStoreFloat3(&transform_.position_, vPos); //現在位置の更新
	}

	XMFLOAT3 camTarget = { 0, 0, 0 };
	XMFLOAT3 camPos = { 0, 0, 0 };
	XMVECTOR vCam = { 0, 0, 0, 0 };
	XMVECTOR vTarget = { 0, 0, 0, 0 };

	camTarget = transform_.position_;
	vCam = { 0, 5, -10, 0 };
	vCam = XMVector3TransformCoord(vCam, mRotX);
	vCam = XMVector3TransformCoord(vCam, mRotY);
	XMStoreFloat3(&camPos, vPos + vCam);

	Camera::SetTarget(camTarget);
	Camera::SetPosition(camPos);
}

//描画
void Controller::Draw()
{
}

//開放
void Controller::Release()
{
}