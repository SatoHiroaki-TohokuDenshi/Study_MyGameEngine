#pragma once
#include "Engine/GameObject.h"

//Enemyを管理するクラス
class Enemy : public GameObject
{
private:
    int hModel_;
public:
    //コンストラクタ
    Enemy(GameObject* parent);

    //デストラクタ
    ~Enemy();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};