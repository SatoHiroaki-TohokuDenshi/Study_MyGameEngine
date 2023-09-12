#pragma once

#include <vector>
#include <windows.h>
#include "Engine/GameObject.h"

using std::vector;

namespace {
	//ブロックの種類
	enum BOX_TYPE {
		BOX_DEFAULT = 0,		//通常
		BOX_BRICK,				//石
		BOX_GRASS,				//草
		BOX_SAND,				//砂
		BOX_WATER,				//水
		BOX_MAX,				//最大値
	};
	const int sizeX = 15;		//x座標の最大値
	const int sizeZ = 15;		//z座標の最大値

	//編集モード
	enum MODE {
		MODE_UP = 0,			//上げる
		MODE_DOWN,				//下げる
		MODE_CHANGE,			//変える
	};
}

//Stageを管理するクラス
class Stage : public GameObject
{
private:
	struct {
		BOX_TYPE type_;
		int height_;
	} table_[sizeX][sizeZ];		//データを格納する2次元配列

	struct {
		int x_;
		int z_;
		float dist_;
	} selectBlock_;				//選んだブロックの情報を保持する変数
	
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