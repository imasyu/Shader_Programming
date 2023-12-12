#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

namespace {
    const XMFLOAT4 DEF_LIGHT_POSITION{1, 2, 1, 0};
}

void Stage::IntConstantBuffer()
{
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CBUFF_STAGE);
    cb.Usage = D3D11_USAGE_DEFAULT;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = 0;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;

    //コンスタントバッファの作成
    HRESULT hr;
    hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pCBStageScene_);
    if (FAILED(hr))
    {
        MessageBox(NULL, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
    }
}

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"), hModel_(-1), hBall_(-1), hArrow_{-1, -1}, hLightBall_(-1), lightSourcePosition_(DEF_LIGHT_POSITION)
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

    IntConstantBuffer();

    //Camera::SetPosition(XMVECTOR{ 0, 0, -5, 0 });
    //Camera::SetTarget(XMVECTOR{ 0, 0, 0, 0 });
}

void Stage::Update()
{
    ball_transform_.position_.x = -2;
    ball_transform_.position_.y = 1.5f;
    ball_transform_.position_.z = -1;
    ball_transform_.scale_.x = 0.5f;
    ball_transform_.scale_.y = 0.5f;
    ball_transform_.scale_.z = 1.0f;
    //ball_transform_.rotate_.y += 0.3f;

    a_transform_.position_.x = 2;
    a_transform_.position_.y = 1;
    a_transform_.position_.z = -1;
    a_transform_.scale_.x = 0.5f;
    a_transform_.scale_.y = 0.5f;
    a_transform_.scale_.z = 1.0f;

    b_transform_.position_.y = 3;
    b_transform_.position_.z = -1.2;
    b_transform_.scale_.x = 0.5f;
    b_transform_.scale_.y = 0.5f;
    b_transform_.scale_.z = 1.0f;
    b_transform_.rotate_.x = 90.0f;
    b_transform_.rotate_.y = 90.0f;

    CBUFF_STAGE cb;
    cb.lightPosition = lightSourcePosition_;
    XMStoreFloat4(&cb.eyePos, Camera::GetEyePosition());

    Direct3D::pContext_->UpdateSubresource(pCBStageScene_, 0, NULL, &cb, 0, 0);

    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene_);  //頂点シェーダー用
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene_);  //ピクセルシェーダー用
}

void Stage::Draw()
{
    //q->Draw(transform_);

    //Model::SetTransform(hModel_, transform_);
    //Model::Draw(hModel_);

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
