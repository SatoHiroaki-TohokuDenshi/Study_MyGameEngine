#include "Player.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"

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
}

//更新
void Player::Update() {
	transform_.rotate_.y += 1.0f;
	if (Input::IsKeyDown(DIK_A)) {
		this->KillMe();
	}
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