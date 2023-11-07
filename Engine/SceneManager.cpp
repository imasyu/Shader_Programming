#include "SceneManager.h"
#include "../TestScene.h"
#include "Model.h"

SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentScene_ID_ = SCENE_ID_TEST;
	nextScene_ID_ = currentScene_ID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	//シーンを実際に切り替える
	//現在のシーンと、ネクストシーンが別だったら切り替え
	if (currentScene_ID_ != nextScene_ID_)
	{
		//そのシーンのオブジェクトを全削除
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();

		//ロードしたデータを全削除
		Model::Release();
		//後片付け終了
		switch (nextScene_ID_)
		{
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		}
		currentScene_ID_ = nextScene_ID_;
	}
	//現在のシーンと後片付け
	//新しいシーンの準備
	//currentScene_ID_をnextScene_ID_
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

/// <summary>
/// 指定したシーンをnextSceneID_に設定する（＝次のUpdateでシーンが変わる）
/// </summary>
/// <param name="_next">次に移行するシーンID(次のフレームで更新)</param>
void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextScene_ID_ = _next;
}
