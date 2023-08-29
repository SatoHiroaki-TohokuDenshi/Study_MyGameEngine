#include "Stage.h"
#include <string>
#include "Engine/Model.h"

using std::string;

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{
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

    table_.resize(sizeX);
    for (int x = 0; x < sizeX; x++) {
        for (int z = 0; z < sizeZ; z++) {
            table_.at(x).push_back(x % BOX_TYPE::BOX_MAX);
        }
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

    for (int x = 0; x < sizeX; x++)
    {
        for (int z = 0; z < sizeZ; z++)
        {
            blockTrans.position_.x = (float)x;
            blockTrans.position_.z = (float)z;

            type = table_.at(x).at(z);

            Model::SetTransform(hModel_.at(type), blockTrans);
            Model::Draw(hModel_.at(type));
        }
    }
}

//開放
void Stage::Release()
{
}