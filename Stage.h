#pragma once
#include "Engine/GameObject.h"
#include "Engine/Quad.h"

struct CBUFF_STAGE
{
	XMFLOAT4    lightPosition;
	XMFLOAT4    eyePos;
};

//シーンを管理するクラス
class Stage : public GameObject
{
	int hModel_; //モデル番号
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
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Stage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetLightPos(XMFLOAT4& _pos) { lightSourcePosition_ = _pos; }
	XMFLOAT4 GetLightPos() { return (lightSourcePosition_); }
};
