#include "RootJob.h"
#include "SceneManager.h"

RootJob::RootJob(GameObject* parent) :
	GameObject(parent, "RootJob")
{
}

RootJob::~RootJob() {
}

//‰Šú‰»
void RootJob::Initialize() {
	Instantiate<SceneManager>(this);
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
