#include "RootJob.h"
#include "../PlayScene.h"

RootJob::RootJob() :
	GameObject()
{
}

RootJob::~RootJob() {
}

//初期化
void RootJob::Initialize() {
	Instantiate<PlayScene>(this);
}

//更新
void RootJob::Update() {
}

//描画
void RootJob::Draw() {
}

//解放
void RootJob::Release() {
}
