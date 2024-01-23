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

enum RENDER_STATE
{
	RENDRE_DIRLIGHT,
	RENDER_PNTLIGHT,
};

class Texture;

class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;
		XMFLOAT4 ambient;
		XMFLOAT4 specular;
		float shininess;
	};

	struct CBUFF_MODEL
	{
		XMMATRIX	matWVP; //wvp ���[���h�r���[�v���W�F�N�V����
		XMMATRIX     matW; //W
		XMMATRIX	matNormal; //�X�P�[���~���s�ړ��̋t�s��
		XMFLOAT4    diffuseColor;//FBX����Ƃ��Ă����ʂ̐F
		XMFLOAT4    ambientColor;
		XMFLOAT4    specularColor;
		FLOAT       shininess;
		BOOL        isTextured;
		//XMFLOAT4    lightPosition;
		//XMFLOAT4    eyePos;
	};

	struct VERTEX
	{
		XMVECTOR position;  //�ʒu
		XMVECTOR uv;        //�e�N�X�`�����W
		XMVECTOR normal;
	};

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_; //�}�e���A���̌�

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;
	vector <int> indexCount_;

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
	RENDER_STATE state_;
	Texture* pToonTex_;
public:

	Fbx();
	HRESULT  Load(std::string fileName);
	void     Draw(Transform& transform);
	void     SetRenderingShader(RENDER_STATE _state) { state_ = _state; }
	void     Release();
};