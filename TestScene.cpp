#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

TestScene::TestScene(GameObject* parent) :
	GameObject(parent, "TestScene")
{
}

TestScene::~TestScene() {
}

void TestScene::Initialize() {
}

void TestScene::Update() {
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		pSM->ChangeScene(SCENE_ID_PLAY);
	}
}

void TestScene::Draw() {
}

void TestScene::Release() {
}
