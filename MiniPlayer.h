#pragma once
#include "Engine/GameObject.h"

//前方宣言
class Fbx;

//MiniPlayerを管理するクラス
class MiniPlayer : public GameObject
{
private:
    Fbx* pFbx;
public:
    //コンストラクタ
    MiniPlayer(GameObject* parent);

    //デストラクタ
    ~MiniPlayer();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};