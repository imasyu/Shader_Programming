#pragma once
#include "Engine/GameObject.h"

class TestScene :
    public GameObject
{
public:
    //�R���X�g���N�^
    //�����Fparent
    TestScene(GameObject* parent);

    //������
    void Initialize() override; 

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //���
    void Release()override;
};
