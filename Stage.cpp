#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), hModel_(-1), hBall_(-1), hArrow_{-1, -1}
{
}

void Stage::Initialize()
{
    //q = new Quad();
    //q->Initialize();

    hModel_ = Model::Load("Assets/Ground.fbx");
    assert(hModel_ >= 0);

    hBall_ = Model::Load("Assets/Ball.fbx");
    assert(hBall_ >= 0);

    

   hArrow_[0] = Model::Load("Assets/Arrow.fbx");
    assert(hArrow_[0] >= 0);

    hArrow_[1] = Model::Load("Assets/Arrow.fbx");
    assert(hArrow_[1] >= 0);

    //Camera::SetPosition(XMVECTOR{ 0, 0, -5, 0 });
    //Camera::SetTarget(XMVECTOR{ 0, 0, 0, 0 });
}

void Stage::Update()
{
    ball_transform_.position_.y = 1.5f;
    a_transform_.position_.y = 3;
    a_transform_.scale_.x = 0.5f;
    a_transform_.scale_.y = 0.5f;
    a_transform_.scale_.z = 1.0f;
    a_transform_.rotate_.x = 90.0f;
    a_transform_.rotate_.y = 90.0f;
    a_transform_.rotate_.z = 0.0f;
    b_transform_.scale_.x = 0.5f;
    b_transform_.scale_.y = 0.5f;
    b_transform_.scale_.z = 1.0f;
}

void Stage::Draw()
{
    //q->Draw(transform_);

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    Model::SetTransform(hBall_, ball_transform_);
    Model::Draw(hBall_);

    Model::SetTransform(hArrow_[0], a_transform_);
    Model::Draw(hArrow_[0]);

    Model::SetTransform(hArrow_[1], b_transform_);
    Model::Draw(hArrow_[1]);
}

void Stage::Release()
{
}
