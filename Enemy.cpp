#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize() {
	hModel_ = Model::Load("Assets/Oden_2.fbx");
	assert(hModel_ >= 0);

	transform_.position_.z = 20.0f;
	transform_.rotate_.z = 180.0f;

	SphereCollider* col = new SphereCollider();
	AddCollider(col);
}

//更新
void Enemy::Update() {
	transform_.rotate_.y++;
}

//描画
void Enemy::Draw() {
	Model::SetTransform(hModel_, this->transform_);
	Model::Draw(hModel_);
}

//開放
void Enemy::Release() {
}