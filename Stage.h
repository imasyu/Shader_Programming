#pragma once
#include "Engine/GameObject.h"

//�V�[�����Ǘ�����N���X
class Stage : public GameObject
{
	int hModel_; //���f���ԍ�
	int hBall_;
	Transform ball_transform_;
	int hArrow_[2];
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
