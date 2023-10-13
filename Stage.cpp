#include "Stage.h"
#include <string>
#include "Engine/Direct3D.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "resource.h"

#include <Windows.h>
#include <filesystem>

using std::string;

//コンストラクタ
Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), mode_(0), select_(0), brushSize_(brushS)
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
	//何も選ばれていないなら中止
	if (selectBlock_.dist_ <= 0.0f)		return;

	switch (mode_) {
	case MODE::MODE_UP:
		table_[selectBlock_.x_][selectBlock_.z_].height_++;
		break;
	case MODE::MODE_DOWN:
		//0以下には下げられない
		if (table_[selectBlock_.x_][selectBlock_.z_].height_ > 0)
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
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_ADDSTRING, 0, (LPARAM)"デフォルト");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_ADDSTRING, 0, (LPARAM)"石");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_ADDSTRING, 0, (LPARAM)"草");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_ADDSTRING, 0, (LPARAM)"砂");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_ADDSTRING, 0, (LPARAM)"水");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_SETCURSEL, 0, 0);

		//サイズ
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SIZE), CB_ADDSTRING, 0, (LPARAM)"1");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SIZE), CB_ADDSTRING, 0, (LPARAM)"3");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SIZE), CB_ADDSTRING, 0, (LPARAM)"5");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_SIZE), CB_SETCURSEL, 0, 0);

		return TRUE;

	case WM_COMMAND:		//ダイアログ選択
		WORD id;
		id = LOWORD(wp);
		if (id == IDC_COMBO_SELECT) {
			select_ = (int)SendMessage(GetDlgItem(hDlg, IDC_COMBO_SELECT), CB_GETCURSEL, 0, 0);
		}
		else if (id == IDC_COMBO_SIZE) {
			int size = (int)SendMessage(GetDlgItem(hDlg, IDC_COMBO_SIZE), CB_GETCURSEL, 0, 0);
			switch (size) {
			case BRUSH_SIZE::BRUSH_SMALL:
				brushSize_ = brushS;
				break;
			case BRUSH_SIZE::BRUSH_MEDIUM:
				brushSize_ = brushM;
				break;
			case BRUSH_SIZE::BRUSH_LARGE:
				brushSize_ = brushL;
				break;
			default:
				break;
			}
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

//選択されたブロックの計算
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

	//マウスの位置の取得
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	//マウスの位置を3D空間に逆計算
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

				//レイキャスト
				Model::RayCast(hModel_.at(0), data);

				//当たっていたら
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

void Stage::NewStage() {
	for (int x = 0; x < sizeX; x++) {
		for (int z = 0; z < sizeZ; z++) {
			table_[x][z].type_ = (BOX_TYPE)(x % BOX_TYPE::BOX_MAX);
			table_[x][z].height_ = 0;
		}
	}
}

void Stage::LoadStage() {
	//セーブダイアログ
	char fileName[MAX_PATH] = "";  //ファイル名を入れる変数
	string path = std::filesystem::current_path().string();
	path += "\\無題.map";
	path.copy(fileName, MAX_PATH);

	//「ファイルを保存」ダイアログの設定
	OPENFILENAME ofn;										//名前をつけて保存ダイアログの設定用構造体
	ZeroMemory(&ofn, sizeof(ofn));							//構造体初期化
	ofn.lStructSize = sizeof(OPENFILENAME);					//構造体のサイズ
	ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")	//─┬ファイルの種類
		TEXT("すべてのファイル(*.*)\0*.*\0\0");				//─┘
	ofn.lpstrFile = fileName;								//ファイル名
	ofn.nMaxFile = MAX_PATH;								//パスの最大文字数
	ofn.Flags = OFN_FILEMUSTEXIST;							//フラグ（存在するファイルしか選べない）
	ofn.lpstrDefExt = "map";								//デフォルト拡張子

	//「ファイルを保存」ダイアログ
	BOOL selFile;
	selFile = GetOpenFileName(&ofn);

	//キャンセルしたら中断
	if (selFile == FALSE) return;

	///// 読み込み /////
	HANDLE hFile;        //ファイルのハンドル
	hFile = CreateFile(
		"map.csv",				//ファイル名
		GENERIC_READ,			//アクセスモード（書き込み用）
		0,						//共有（なし）
		NULL,					//セキュリティ属性（継承しない）
		OPEN_EXISTING,			//作成方法
		FILE_ATTRIBUTE_NORMAL,	//属性とフラグ（設定なし）
		NULL					//拡張属性（なし）
	);

	//ファイルのサイズを取得
	DWORD fileSize = GetFileSize(hFile, NULL);

	//ファイルのサイズ分メモリを確保
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //読み込み位置

	BOOL result = ReadFile(
		hFile,		//ファイルハンドル
		data,		//データを入れる変数
		fileSize,	//読み込むサイズ
		&dwBytes,	//読み込んだサイズ
		NULL		//オーバーラップド構造体（今回は使わない）
	);
	if (result == FALSE) {
		delete[] data;
		CloseHandle(hFile);
		return;
	}

	string sData = data;
	string tmp = "";
	string::iterator it = sData.begin();

	for (int x = 0; x < sizeX; x++) {
		for (int z = 0; z < sizeZ; z++) {
			//高さの情報の検索
			while (true) {
				if ((*it) == ',')	break;
				tmp += (*it);
				it++;
			}
			table_[x][z].height_ = std::stoi(tmp);
			tmp = "";
			it++;

			//種類の情報の検索
			while (true) {
				if ((*it) == ',' || (*it) == 'z')	break;
				tmp += (*it);
				it++;
			}
			table_[x][z].type_ = (BOX_TYPE)std::stoi(tmp);
			if ((*it) == 'z')	break;
			tmp = "";
			it++;

			//改行コードがあったらイテレータを進める
			if ((*it) == '\n')	it++;
		}
		if ((*it) == 'z')	break;
	}

	delete[] data;
	CloseHandle(hFile);
}

void Stage::SaveStage() {
	//セーブダイアログ
	char fileName[MAX_PATH] = "";  //ファイル名を入れる変数
	string path = std::filesystem::current_path().string();
	path += "\\無題.map";
	path.copy(fileName, MAX_PATH);

	//「ファイルを保存」ダイアログの設定
	OPENFILENAME ofn;										//名前をつけて保存ダイアログの設定用構造体
	ZeroMemory(&ofn, sizeof(ofn));							//構造体初期化
	ofn.lStructSize = sizeof(OPENFILENAME);					//構造体のサイズ
	ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0")	//─┬ファイルの種類
		TEXT("すべてのファイル(*.*)\0*.*\0\0");				//─┘
	ofn.lpstrFile = fileName;								//ファイル名
	ofn.nMaxFile = MAX_PATH;								//パスの最大文字数
	ofn.Flags = OFN_OVERWRITEPROMPT;						//フラグ（同名ファイルが存在したら上書き確認）
	ofn.lpstrDefExt = "map";								//デフォルト拡張子

	//「ファイルを保存」ダイアログ
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);

	//キャンセルしたら中断
	if (selFile == FALSE) return;

	///// 書き込み /////
	HANDLE hFile;        //ファイルのハンドル
	hFile = CreateFile(
		fileName,				//ファイル名
		GENERIC_WRITE,			//アクセスモード（書き込み用）
		0,						//共有（なし）
		NULL,					//セキュリティ属性（継承しない）
		CREATE_ALWAYS,			//作成方法
		FILE_ATTRIBUTE_NORMAL,	//属性とフラグ（設定なし）
		NULL					//拡張属性（なし）
	);
	if (hFile == nullptr)	return;

	DWORD dwBytes = 0;	//書き込み位置

	string data = "";
	for (int x = 0; x < sizeX; x++) {
		for (int z = 0; z < sizeZ; z++) {
			data += std::to_string(table_[x][z].height_) + ",";
			data += std::to_string(table_[x][z].type_);
			//最後のデータだったらコンマを打たない
			if (x == sizeX - 1 && z == sizeZ - 1)	break;
			data += ",";
		}
		if (x == sizeX - 1)	break;
		data += "\n";
	}

	data += "z";
	BOOL result = WriteFile(
		hFile,						//ファイルハンドル
		data.c_str(),				//保存するデータ（文字列）
		(DWORD)strlen(data.c_str()),//書き込む文字数
		&dwBytes,					//書き込んだサイズを入れる変数
		NULL						//オーバーラップド構造体（今回は使わない）
	);

	CloseHandle(hFile);
}