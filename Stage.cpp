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
	:GameObject(parent, "Stage"), hModel_(-1), hBall_(-1), hArrow_{-1, -1}, hLightBall_(-1), lightSourcePosition_(DEF_LIGHT_POSITION), sprite_(nullptr)
{
}

void Stage::Initialize()
{
    //q = new Quad();
    //q->Initialize();

    hModel_ = Model::Load("Assets/Water.fbx");
    assert(hModel_ >= 0);

    hBall_ = Model::Load("Assets/Ball.fbx");
    assert(hBall_ >= 0);

    hLightBall_ = Model::Load("Assets/Ball1.fbx");
    assert(hLightBall_ >= 0);

   hArrow_[0] = Model::Load("Assets/Arrow.fbx");
    assert(hArrow_[0] >= 0);

    hArrow_[1] = Model::Load("Assets/Arrow.fbx");
    assert(hArrow_[1] >= 0);

    Camera::SetPosition(XMVECTOR{ 0, 1, -15, 0 });
    Camera::SetTarget(XMVECTOR{ 0, 1, -10, 0 });
    trBall_.position_ = { 0,2,0 };
    trBall_.rotate_ = { 0,0,0 };
    //trBall_.scale_ = { 0.4,0.4,0.4 };

    trBall1_.position_ = { 1,1,2 };
    trBall1_.rotate_ = { 0,0,0 };
    trBall1_.scale_ = { 0.2f, 0.2f,0.2f };
   
    trLight_.position_ = { 0,0,0 };
    trLight_.rotate_ = { 0,0,0 };
    trLight_.scale_ = { 0.4f,0.4f,0.4f };
    
    trArrow1_.position_ = { 0,0,0 };
    trArrow1_.rotate_ = { 90,90,0 };
    trArrow1_.scale_ = { 0.5f,0.5f,0.5f };

    trArrow2_.position_ = { 2,-2,0 };
    trArrow2_.rotate_ = { 0,1,0 };
    trArrow2_.scale_ = { 0.5f,0.5f,0.5f };

    IntConstantBuffer();

    sprite_ = new Sprite;

    sprite_->Load("tex.png");
}

void Stage::Update()
{
    //trBall_.rotate_.y += 0.5f;

    if (Input::IsKeyUp(DIK_SPACE))
    {
        Model::ToggleRenderState();
    }
    if (Input::IsKey(DIK_RIGHT))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x + 0.1f,p.y + 0.0f,p.z + 0.0f,p.w + 0.0f };

        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_LEFT))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.1f,p.y - 0.0f,p.z - 0.0f,p.w - 0.0f };

        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_UP))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f,p.y + 0.1f,p.z - 0.0f,p.w - 0.0f };

        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_DOWN))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f,p.y - 0.1f,p.z - 0.0f,p.w - 0.0f };

        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_W))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f,p.y - 0.0f,p.z + 0.1f, 0 };

        SetLightPos(margin);
    }
    if (Input::IsKey(DIK_S))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f,p.y - 0.0f,p.z - 0.1f, 0 };

        SetLightPos(margin);
    }
    XMFLOAT4 tmp{ GetLightPos() };
    trLight_.position_ = { tmp.x,tmp.y,tmp.z };

    CBUFF_STAGE cb;
    cb.lightPosition = lightSourcePosition_;
    XMStoreFloat4(&(cb.eyePos), Camera::GetEyePosition());

    Direct3D::pContext_->UpdateSubresource(pCBStageScene_, 0, NULL, &cb, 0, 0);

    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene_);  //頂点シェーダー用
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene_);  //ピクセルシェーダー用
}

void Stage::Draw()
{
    //q->Draw(transform_);

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    Model::SetTransform(hBall_, trBall_);
    Model::Draw(hBall_);

    Model::SetTransform(hLightBall_, trLight_);
    Model::Draw(hLightBall_);


    /*Model::SetTransform(hArrow_[0], trArrow1_);
    Model::Draw(hArrow_[0]);

    Model::SetTransform(hArrow_[1], trArrow2_);
    Model::Draw(hArrow_[1]);*/

    Transform t;
    t.position_ = { 0,0,0 };
    t.scale_ = { 1.0,1.0,1.0 };
    t.rotate_ = { 0,0,0 };
    RECT rec{ 0,0,300,300 };
    //sprite_->Draw(t, rec, 0.5f);
}

void Stage::Release()
{
}
