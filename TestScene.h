#pragma once
#include "Engine/GameObject.h"

class TestScene :
    public GameObject
{
public:
    //コンストラクタ
    //引数：parent
    TestScene(GameObject* parent);

    //初期化
    void Initialize() override; 

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //解放
    void Release()override;
};

