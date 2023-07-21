#include "GameObject.h"
#include "SafetyMacro.h"
#include "SphereCollider.h"

GameObject::GameObject() :
	transform_(Transform()),
	pParent_(nullptr), objectName_(""), isDead_(false), pCollider_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :
	transform_(Transform()),
	pParent_(parent), objectName_(name), isDead_(false), pCollider_(nullptr)
{
	if (pParent_ != nullptr)
		this->transform_.SetParentTransform(&parent->transform_);
}

GameObject::~GameObject() {
}

void GameObject::UpdateSub() {
	//自分のUpdateを呼び出す
	Update();

	RoundRobin(GetRootJob());
	//子供のUpdateSubを呼ぶ
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->UpdateSub();
	}

	//オブジェクトの消去
	DeleteObject();
}

void GameObject::DrawSub() {
	//自分のDrawを呼び出す
	Draw();
	//子供のDrawSubを呼ぶ
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
}

void GameObject::ReleaseSub() {
	//子供のReleaseSubを呼ぶ
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->ReleaseSub();
		SAFE_DELETE(*itr);
	}
	//自分のReleaseを呼び出す
	Release();
}

void GameObject::KillMe() {
	this->isDead_ = true;
}

void GameObject::DeleteObject() {
	//オブジェクトの消去
	for (auto itr = childList_.begin(); itr != childList_.end();) {
		//消去フラグが立っている場合
		if ((*itr)->isDead_) {
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		//立っていないなら次を走査
		else
			itr++;
	}
}

GameObject* GameObject::FindChildObject(string objName) {
	//自分の名前だったら自分のアドレスを返す
	if (objName == this->objectName_) {
		return this;
	}
	else {
		for (auto &itr : childList_) {
			GameObject* obj = itr->FindChildObject(objName);
			if (obj != nullptr)
				return obj;
		}
	}

	//見つからなかった場合
	return nullptr;
}

GameObject* GameObject::GetRootJob() {
	//自身がRootJobの場合
	if (pParent_ == nullptr)
		return this;

	//親のGetRootJobで親について検索
	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string objName) {
	return GetRootJob()->FindChildObject(objName);
}

void GameObject::AddCollider(SphereCollider* pCollider) {
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget) {
	//相手に判定がないため終了
	if (pTarget->pCollider_ == nullptr) return;
	//自分が相手ならスキップ
	if (pTarget == this) return;

	float dist = (
		(this->transform_.position_.x - pTarget->transform_.position_.x) * (this->transform_.position_.x - pTarget->transform_.position_.x) +
		(this->transform_.position_.y - pTarget->transform_.position_.y) * (this->transform_.position_.y - pTarget->transform_.position_.y) +
		(this->transform_.position_.z - pTarget->transform_.position_.z) * (this->transform_.position_.z - pTarget->transform_.position_.z)
		);
	float rDist = (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius()) * (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius());
	if (dist <= rDist) {
		int n = 0;
	}
}

void GameObject::RoundRobin(GameObject* pTarget) {
	//自分が判定を持っていないならスキップ
	if (this->pCollider_ == nullptr) return;
	if (pTarget->pCollider_ != nullptr)
		Collision(pTarget);

	for (auto itr : pTarget->childList_)
		RoundRobin(itr);
}
