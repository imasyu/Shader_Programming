#pragma once
#include "Engine/GameObject.h"
#include "Engine/Quad.h"

struct CBUFF_STAGE
{
	XMFLOAT4    lightPosition;
	XMFLOAT4    eyePos;
};

//�V�[�����Ǘ�����N���X
class Stage : public GameObject
{
	int hModel_; //���f���ԍ�
	int hBall_;
	int hArrow_[2];
	int hLightBall_;
	Transform trGround_;
	Transform trBall_;
	Transform trArrow1_;
	Transform trArrow2_;
	Transform trLight_;
	ID3D11Buffer* pCBStageScene_;
	//Quad* q;
	void IntConstantBuffer();
	XMFLOAT4    lightSourcePosition_;
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

	void SetLightPos(XMFLOAT4& _pos) { lightSourcePosition_ = _pos; }
	XMFLOAT4 GetLightPos() { return (lightSourcePosition_); }
};
