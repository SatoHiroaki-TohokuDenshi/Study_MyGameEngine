#pragma once

#include <list>
#include <string>
#include "Transform.h"

using std::string;
using std::list;

class SphereCollider;

class GameObject {
protected:
	list<GameObject*>	childList_;		//自分の子供のポインタのリスト
	Transform			transform_;		//自分の位置、向き、拡大率
	GameObject*			pParent_;		//自分の親のポインタ
	string				objectName_;	//自分の名前
	SphereCollider* pCollider_;			//当たり判定

public:
	GameObject();
	GameObject(GameObject* parent, const string& name);
	~GameObject();

	//インターフェース用純粋仮想関数//
	//以下の4つの関数は必ずオーバーライドすること

	//初期化
	virtual void Initialize() = 0;
	//更新
	virtual void Update() = 0;
	//描画
	virtual void Draw() = 0;
	//解放
	virtual void Release() = 0;

	//--------各処理を再帰的に呼ぶ関数--------//
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();


	//--------アクセス関数--------//
	//位置の取得
	void SetPosition(XMFLOAT3 pos) { transform_.position_ = pos; };
	//回転の取得
	void SetRotate(XMFLOAT3 rot) { transform_.rotate_ = rot; };
	//拡大率の取得
	void SetScale(XMFLOAT3 scl) { transform_.scale_ = scl; };


	//--------オブジェクトの消去処理--------//
	bool isDead_;		//フラグ
	void KillMe();		//フラグを立てる
	void DeleteObject();//オブジェクトを消す


	//--------検索をする関数--------//
	//子供の検索
	//引数：オブジェクトの名前  戻値：GameObject型のポインタ　見つからない場合はnullptr
	GameObject* FindChildObject(string objName);

	//ルートジョブの検索
	//引数：オブジェクトの名前  戻値：RootJobのポインタ
	GameObject* GetRootJob();

	//オブジェクトの検索
	//引数：探したいオブジェクトの名前  戻値：GameObject型のポインタ　見つからない場合はnullptr
	GameObject* FindObject(string objName);

	//--------当たり判定--------//
	//当たり判定の追加
	void AddCollider(SphereCollider* pCollider);
	//
	void Collision(GameObject* pTarget);
	//総当たり
	void RoundRobin(GameObject* pTarget);

public:
	/// <summary>初期化用テンプレート</summary>
	/// <typeparam name="T">初期化するクラス</typeparam>
	/// <param name="parent">親のアドレス</param>
	/// <returns>作成されたオブジェクトのポインタ</returns>
	template <class T>
	GameObject* Instantiate(GameObject* parent) {
		T* p;
		p = new T(parent);
		p->Initialize();
		parent->childList_.push_back(p);
		return p;
	}
};