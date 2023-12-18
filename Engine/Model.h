#pragma once
#include <string>
#include <vector>
#include "Fbx.h"

namespace Model
{
	struct ModelData
	{
		Fbx* pfbx_;
		Transform transform_;//トランスフォーム
		std::string filename_;
	};
	
	int Load(std::string filenNme);
	void SetTransform(int hModel, Transform transform);
	Fbx* GetModel(int _hModel);
	void Draw(int hModel);
	void Release();
	void ToggleRenderState();

}

