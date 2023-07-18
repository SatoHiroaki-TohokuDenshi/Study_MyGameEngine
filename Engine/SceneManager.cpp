#include "SceneManager.h"
#include "Model.h"
#include "SafetyMacro.h"
#include "../TestScene.h"
#include "../PlayScene.h"

SceneManager::SceneManager(GameObject* parent) :
	GameObject(parent, "SceneManager"), 
	currentSceneID_(SCENE_ID_TEST), nextSceneID(SCENE_ID_TEST)
{
}

SceneManager::~SceneManager() {
}

void SceneManager::Initialize() {
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update() {
	//現在のシーンIDと次のシーンIDが異なる場合切り替える
	if (currentSceneID_ != nextSceneID) {
		//現在のシーンの後片付け
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();

		//ロードしたデータの削除
		Model::Release();

		//次のシーンの準備
		switch (nextSceneID)
		{
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		case SCENE_ID_PLAY:
			Instantiate<PlayScene>(this);
			break;
		}
		currentSceneID_ = nextSceneID;
	}

}

void SceneManager::Draw() {
}

void SceneManager::Release() {
}

//シーンを切り替える
void SceneManager::ChangeScene(SCENE_ID next) {
	nextSceneID = next;
}
