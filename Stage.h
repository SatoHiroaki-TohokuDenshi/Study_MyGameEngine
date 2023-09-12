#pragma once

#include <vector>
#include <windows.h>
#include "Engine/GameObject.h"

using std::vector;

namespace {
	enum BOX_TYPE {
		BOX_DEFAULT = 0,
		BOX_BRICK,
		BOX_GRASS,
		BOX_SAND,
		BOX_WATER,
		BOX_MAX,
	};
	const int sizeX = 15;
	const int sizeZ = 15;
}

//Stageを管理するクラス
class Stage : public GameObject
{
private:
	struct {
		BOX_TYPE type_;
		int height_;
	} table_[sizeX][sizeZ];

	struct {
		int x_;
		int z_;
		float dist_;
	} selectBlock_;
	
	vector<int> hModel_;		//モデル番号

	int mode_;		//0:上げる  1:下げる  2:変える
	int select_;	//種類

public:	//オーバーライド関数
	//コンストラクタ
	Stage(GameObject* parent);

	//デストラクタ
	~Stage();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

public:
	void SetBlock(int _x, int _z, BOX_TYPE _type);
	void SetBlockHeight(int _x, int _z, int _height);

	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

private:
	void CalcChoiceBlock();
};