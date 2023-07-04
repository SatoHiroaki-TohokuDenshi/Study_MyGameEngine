#pragma once

#include <list>
#include <string>
#include "Transform.h"

using std::string;
using std::list;

class GameObject {
protected:
	list<GameObject*>	childList_;		//自分の子供のポインタのリスト
	Transform			transform_;		//自分の位置、向き、拡大率
	GameObject*			pParent_;		//自分の親のポインタ
	string				objectName_;	//自分の名前

public:
	GameObject();
	GameObject(GameObject* parent, const string& name);
	~GameObject();

	//初期化
	virtual void Initialize() = 0;
	//更新
	virtual void Update() = 0;
	//描画
	virtual void Draw() = 0;
	//解放
	virtual void Release() = 0;

	template <class T>
	void Instantiate(GameObject* parent) {
		T* p;
		p = new T(parent);
		p->Initialize();
		parent->childList_.push_back(p);
	}
};