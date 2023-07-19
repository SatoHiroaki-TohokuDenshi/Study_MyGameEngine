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

	//子供のUpdate関数を再帰的に呼び出す
	void UpdateSub();
	//子供のDraw関数を再帰的に呼び出す
	void DrawSub();
	//子供のRelease関数を再帰的に呼び出す
	void ReleaseSub();

	//アクセス関数//
	//位置の取得
	void SetPosition(XMFLOAT3 pos) { transform_.position_ = pos; };
	//回転の取得
	void SetRotate(XMFLOAT3 rot) { transform_.rotate_ = rot; };
	//拡大率の取得
	void SetScale(XMFLOAT3 scl) { transform_.scale_ = scl; };

	//オブジェクトの消去処理//
	bool isDead_;		//フラグ
	void KillMe();		//フラグを立てる
	void DeleteObject();//オブジェクトを消す

	//子供の検索
	//引数：オブジェクトの名前
	//戻値：GameObject型のポインタ　見つからない場合はnullptr
	GameObject* FindChildObject(string objName);

	//オブジェクトの検索
	//引数：探したいオブジェクトの名前
	//戻値：RootJobのポインタ
	GameObject* GetRootJob();

	//オブジェクトの検索
	//引数：探したいオブジェクトの名前
	//戻値：GameObject型のポインタ　見つからない場合はnullptr
	GameObject* FindObject(string objName);

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