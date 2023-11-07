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
	//�V�[�������ۂɐ؂�ւ���
	//���݂̃V�[���ƁA�l�N�X�g�V�[�����ʂ�������؂�ւ�
	if (currentScene_ID_ != nextScene_ID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();

		//���[�h�����f�[�^��S�폜
		Model::Release();
		//��Еt���I��
		switch (nextScene_ID_)
		{
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		}
		currentScene_ID_ = nextScene_ID_;
	}
	//���݂̃V�[���ƌ�Еt��
	//�V�����V�[���̏���
	//currentScene_ID_��nextScene_ID_
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

/// <summary>
/// �w�肵���V�[����nextSceneID_�ɐݒ肷��i������Update�ŃV�[�����ς��j
/// </summary>
/// <param name="_next">���Ɉڍs����V�[��ID(���̃t���[���ōX�V)</param>
void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextScene_ID_ = _next;
}
