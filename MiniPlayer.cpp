#include "MiniPlayer.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"

//コンストラクタ
MiniPlayer::MiniPlayer(GameObject* parent)
	:GameObject(parent, "MiniPlayer"), hModel_(-1)
{
}

//デストラクタ
MiniPlayer::~MiniPlayer()
{
}

//初期化
void MiniPlayer::Initialize() {
	hModel_ = Model::Load("Assets/Oden_2.fbx");
	assert(hModel_ >= 0);

	this->transform_.scale_ = XMFLOAT3(0.3f, 0.3f, 0.3f);

	SphereCollider* col = new SphereCollider();
	AddCollider(col);
}

//更新
void MiniPlayer::Update() {
	transform_.rotate_.y++;
	transform_.position_.z += 0.5f;

	if (transform_.position_.z >= 50.0f)
		KillMe();
}

//描画
void MiniPlayer::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void MiniPlayer::Release() {
}

void MiniPlayer::OnCollision(GameObject* pTarget)
{
	int i = 0;
}