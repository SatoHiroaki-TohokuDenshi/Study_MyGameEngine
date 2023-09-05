#include "Stage.h"
#include <string>
#include "Engine/Model.h"
#include "resource.h"

using std::string;

//コンストラクタ
Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), mode_(0), select_(0)
{
	for (int x = 0; x < sizeX; x++) {
		for (int z = 0; z < sizeZ; z++) {
			table_[x][z].type_ = (BOX_TYPE)(x % BOX_TYPE::BOX_MAX);
			table_[x][z].height_ = 1;
		}
	}
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
	string modelName[] = {
		"BoxDefault.fbx",
		"BoxBrick.fbx",
		"BoxGrass.fbx",
		"BoxSand.fbx",
		"BoxWater.fbx"
	};

	//モデルデータのロード
	for (int i = 0; i < BOX_TYPE::BOX_MAX; i++) {
		hModel_.push_back(Model::Load("assets/" + modelName[i]));
		assert(hModel_.at(i) >= 0);
	}
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
	//Stageオブジェクトをずらさずに、ステージを配置するための変数
	Transform blockTrans;
	//表示するモデルを管理する変数
	int type = 0;
	int height = 1;

	for (int x = 0; x < sizeX; x++)
	{
		for (int z = 0; z < sizeZ; z++)
		{
			blockTrans.position_.x = (float)x;
			blockTrans.position_.z = (float)z;

			type = table_[x][z].type_;
			height = table_[x][z].height_;

			for (int h = 0; h < height; h++) {
				blockTrans.position_.y = (float)h;
				Model::SetTransform(hModel_.at(type), blockTrans);
				Model::Draw(hModel_.at(type));
			}
		}
	}
}

//開放
void Stage::Release()
{
}

void Stage::SetBlock(int _x, int _z, BOX_TYPE _type)
{
	if (_type >= BOX_TYPE::BOX_MAX)		return;
	table_[_x][_z].type_ = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
	if (_height >= 6) return;
	table_[_x][_z].height_ = _height;
}

//ダイアログのウィンドウプロシージャ
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp){
	switch (msg) {
	case WM_INITDIALOG:		//初期化
		//ラジオボタン
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

		//コンボボックス
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"デフォルト");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"石");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"草");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"砂");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"水");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
		return TRUE;
	default:
		break;
	}
	return FALSE;
}