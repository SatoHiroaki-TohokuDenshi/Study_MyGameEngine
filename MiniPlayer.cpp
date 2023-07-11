#include "MiniPlayer.h"
#include "Engine/Fbx.h"
#include "Engine/Input.h"

//コンストラクタ
MiniPlayer::MiniPlayer(GameObject* parent)
	:GameObject(parent, "MiniPlayer"), pFbx(nullptr)
{
}

//デストラクタ
MiniPlayer::~MiniPlayer()
{
}

//初期化
void MiniPlayer::Initialize() {
	pFbx = new Fbx();
	pFbx->Load("Assets/Oden_2.fbx");
	transform_.position_.x = 3.0f;
	this->transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
}

//更新
void MiniPlayer::Update() {
	transform_.rotate_.y += 1.0f;
	if (Input::IsKeyDown(DIK_A)) {
		this->KillMe();
	}
}

//描画
void MiniPlayer::Draw() {
	pFbx->Draw(this->transform_);
}

//開放
void MiniPlayer::Release() {
	pFbx->Release();
	delete pFbx;
}