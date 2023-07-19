#include "GameObject.h"
#include "SafetyMacro.h"

GameObject::GameObject() :
	transform_(Transform()),
	pParent_(nullptr), objectName_(""), isDead_(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :
	transform_(Transform()),
	pParent_(parent), objectName_(name), isDead_(false)
{
	if (pParent_ != nullptr)
		this->transform_.SetParentTransform(&parent->transform_);
}

GameObject::~GameObject() {
}

void GameObject::UpdateSub() {
	//自分のUpdateを呼び出す
	Update();
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
