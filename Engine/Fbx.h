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
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;
	};

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP; //wvp ���[���h�r���[�v���W�F�N�V����
		XMMATRIX     matW; //W
		XMMATRIX	matNormal; //�X�P�[���~���s�ړ��̋t�s��
		XMFLOAT4    diffuseColor;//FBX����Ƃ��Ă����ʂ̐F
		//XMFLOAT4    lightPosition;
		//XMFLOAT4    eyePos;
		BOOL        isTextured;
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