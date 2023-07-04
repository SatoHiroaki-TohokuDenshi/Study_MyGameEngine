#include "RootJob.h"
#include "../PlayScene.h"

RootJob::RootJob() :
	GameObject()
{
}

RootJob::~RootJob() {
}

//‰Šú‰»
void RootJob::Initialize() {
	Instantiate<PlayScene>(this);
}

//XV
void RootJob::Update() {
}

//•`‰æ
void RootJob::Draw() {
}

//‰ğ•ú
void RootJob::Release() {
}
