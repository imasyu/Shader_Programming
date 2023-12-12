#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include <vector>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

using std::vector;

class Texture;

class Fbx
{
	//マテリアル
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;
	};

	struct CBUFF_MODEL
	{
		XMMATRIX	matWVP; //wvp ワールドビュープロジェクション
		XMMATRIX     matW; //W
		XMMATRIX	matNormal; //スケール×平行移動の逆行列
		XMFLOAT4    diffuseColor;//FBXからとってきた面の色
		BOOL        isTextured;
		//XMFLOAT4    lightPosition;
		//XMFLOAT4    eyePos;
	};

	struct VERTEX
	{
		XMVECTOR position;  //位置
		XMVECTOR uv;        //テクスチャ座標
		XMVECTOR normal;    
	};

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_; //マテリアルの個数

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;
	vector <int> indexCount_;

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
	bool IsFlatColor;
	XMFLOAT4    dColor_;
	XMFLOAT4    lightSourcePosition_;
public:

	Fbx();
	void     SetFlatColor(XMFLOAT4 col);
	HRESULT  Load(std::string fileName);
	void     Draw(Transform& transform);
	void     SetLightPos(XMFLOAT4& pos);
	XMFLOAT4 GetLightPos() { return(lightSourcePosition_);}
	void     Release();
};