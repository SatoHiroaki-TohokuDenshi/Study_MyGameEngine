#include "GameObject.h"

GameObject::GameObject() :
	transform_(Transform()),
	pParent_(nullptr), objectName_("")
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :
	transform_(Transform()),
	pParent_(parent), objectName_(name)
{
}

GameObject::~GameObject() {

}

void GameObject::DrawSub() {
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		//自分のDrawを呼び出す
		(*itr)->Draw();
		//子供のDrawSubを呼ぶ
		(*itr)->DrawSub();
	}
}

void GameObject::UpdateSub() {
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		//自分のUpdateを呼び出す
		(*itr)->Update();
		//子供のUpdateSubを呼ぶ
		(*itr)->UpdateSub();
	}
}

void GameObject::ReleaseSub() {
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		//自分のReleaseを呼び出す
		(*itr)->Release();
		//子供のReleaseSubを呼ぶ
		(*itr)->ReleaseSub();
	}
}