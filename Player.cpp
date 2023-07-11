#include "Player.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"
#include "MiniPlayer.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), pFbx(nullptr)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize() {
	pFbx = new Fbx();
	pFbx->Load("Assets/Oden_2.fbx");
	this->transform_.rotate_.z = 38.0f;
	Instantiate< MiniPlayer>(this);
}

//更新
void Player::Update() {
	transform_.rotate_.y += 1.0f;
	if (Input::IsKeyDown(DIK_A)) {
		this->KillMe();
	}
	if (Input::IsKey(DIK_LEFT))		transform_.position_.x -= 0.1f;
	if (Input::IsKey(DIK_RIGHT))	transform_.position_.x += 0.1f;
}

//描画
void Player::Draw() {
	pFbx->Draw(this->transform_);
}

//開放
void Player::Release() {
	pFbx->Release();
	delete pFbx;
}