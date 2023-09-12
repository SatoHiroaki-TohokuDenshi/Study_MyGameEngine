#include "Stage.h"
#include <string>
#include "Engine/Direct3D.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "resource.h"

using std::string;

//コンストラクタ
Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), mode_(0), select_(0)
{
	for (int x = 0; x < sizeX; x++) {
		for (int z = 0; z < sizeZ; z++) {
			table_[x][z].type_ = (BOX_TYPE)(x % BOX_TYPE::BOX_MAX);
			table_[x][z].height_ = 0;
		}
	}

	selectBlock_.x_ = 0;
	selectBlock_.z_ = 0;
	selectBlock_.dist_ = -1.0f;
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
	if (!Input::IsMouseButtonDown(0))	return;

	CalcChoiceBlock();
	if (selectBlock_.dist_ <= 0.0f)		return;

	switch (mode_) {
	case MODE::MODE_UP:
		table_[selectBlock_.x_][selectBlock_.z_].height_++;
		break;
	case MODE::MODE_DOWN:
		if (table_[selectBlock_.x_][selectBlock_.z_].height_ != 0)
			table_[selectBlock_.x_][selectBlock_.z_].height_--;
		break;
	case MODE::MODE_CHANGE:
		table_[selectBlock_.x_][selectBlock_.z_].type_ = (BOX_TYPE)select_;
		break;
	default:
		break;
	}
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

			for (int h = 0; h < height + 1; h++) {
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

	case WM_COMMAND:		//ダイアログ選択
		WORD id;
		id = LOWORD(wp);
		if (id == IDC_COMBO1) {
			select_ = (int)SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);
		}
		else {
			switch (id) {
			case IDC_RADIO_UP:
				mode_ = MODE::MODE_UP;
				break;
			case IDC_RADIO_DOWN:
				mode_ = MODE::MODE_DOWN;
				break;
			case IDC_RADIO_CHANGE:
				mode_ = MODE::MODE_CHANGE;
				break;
			default:
				break;
			}
		}
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

void Stage::CalcChoiceBlock() {
	float w = (float)(Direct3D::scrWidth_ / 2.0f);
	float h = (float)(Direct3D::scrHeight_ / 2.0f);
	XMMATRIX vp = {
		w	, 0.0f	, 0.0f	, 0.0f,
		0.0f, -h	, 0.0f	, 0.0f,
		0.0f, 0.0f	, 1.0f	, 0.0f,
		w	, h		, 0.0f	, 1.0f
	};

	//逆行列を取得
	XMMATRIX invVP = XMMatrixInverse(nullptr, vp);								//ビューポート変換
	XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());	//プロジェクション変換
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());		//ビュー変換

	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	//3D空間に逆計算
	XMVECTOR mouseVecFront = XMLoadFloat3(&mousePosFront);
	mouseVecFront = XMVector3TransformCoord(mouseVecFront, invVP * invProj * invView);
	//XMVECTOR camPos = XMVector3TransformCoord(Camera::GetCameraPosition(), invVP * invProj * invView);

	XMVECTOR mouseVecBack = XMLoadFloat3(&mousePosBack);
	mouseVecBack = XMVector3TransformCoord(mouseVecBack, invVP * invProj * invView);

	//選択ブロックの初期化
	selectBlock_.x_ = 0;
	selectBlock_.z_ = 0;
	selectBlock_.dist_ = -1.0f;

	for (int x = 0; x < sizeX; x++) {
		for (int z = 0; z < sizeZ; z++) {
			for (int y = 0; y < table_[x][z].height_ + 1; y++) {
				RayCastData data;
				XMStoreFloat4(&data.start, mouseVecFront);
				XMStoreFloat4(&data.dir, mouseVecBack - mouseVecFront);

				Transform trans;
				trans.position_ = XMFLOAT3((float)x, (float)y, (float)z);
				Model::SetTransform(hModel_.at(0), trans);

				Model::RayCast(hModel_.at(0), data);

				if (data.hit) {
					//初めての場合
					if (selectBlock_.dist_ <= 0.0f) {
						selectBlock_.x_ = x;
						selectBlock_.z_ = z;
						selectBlock_.dist_ = data.dist;
					}
					//それ以外
					else if (selectBlock_.dist_ >= data.dist) {
						selectBlock_.x_ = x;
						selectBlock_.z_ = z;
						selectBlock_.dist_ = data.dist;
					}
					break;
				}
			}
		}
	}
}