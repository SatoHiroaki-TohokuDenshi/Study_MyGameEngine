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