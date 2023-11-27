#pragma once
#include "Engine/GameObject.h"
#include "Engine/Quad.h"

//シーンを管理するクラス
class Stage : public GameObject
{
	int hModel_; //モデル番号
	int hBall_;
	Transform ball_transform_;
	int hArrow_[2];
	Transform a_transform_;
	Transform b_transform_;
	//Quad* q;
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
};
