#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), hModel_(-1), hBall_(-1), hArrow_{-1, -1}
{
}

void Stage::Initialize()
{
    hModel_ = Model::Load("Assets/Ground.fbx");
    assert(hModel_ >= 0);

    hBall_ = Model::Load("Assets/Ball.fbx");
    assert(hBall_ >= 0);

    ball_transform_.position_.y += 1.5f;

    hArrow_[0] = Model::Load("Assets/Arrow.fbx");
    assert(hArrow_[0] >= 0);

    hArrow_[1] = Model::Load("Assets/Arrow.fbx");
    assert(hArrow_[1] >= 0);
}

void Stage::Update()
{
    //hArrow_[1] = transform_.rotate_.y += 0.2f;
}

void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    Model::SetTransform(hBall_, ball_transform_);
    Model::Draw(hBall_);

    Model::SetTransform(hArrow_[0], transform_);
    Model::Draw(hArrow_[0]);

    Model::SetTransform(hArrow_[1], transform_);
    Model::Draw(hArrow_[1]);
}

void Stage::Release()
{
}
