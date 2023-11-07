#include "Stage.h"
#include "Engine/Model.h"

#include "Engine/Input.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), hModel_(-1)
{
}

void Stage::Initialize()
{
    hModel_ = Model::Load("Assets/BoxDefault.fbx");
    assert(hModel_ >= 0);
}

void Stage::Update()
{
    transform_.rotate_.y += 0.5f;
}

void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Stage::Release()
{
}
