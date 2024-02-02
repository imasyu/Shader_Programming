#include "Direct3D.h"
#include "Texture.h"
#include <vector>
#include "Transform.h"
#pragma once

#define SAFE_DELETE_ARRAY(p) if(p !=　nullptr) {delete[p; p != nullptr;] }

class Sprite
{
	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX    world;     //頂点座標変換行列
		XMMATRIX    uvTrans;   //テクスチャ座標変換行列
		XMFLOAT4    color;     //テクスチャとの合成色
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;      //位置
		XMVECTOR uv;            //UV
	};
protected:
	UINT64 vertexNum_;                 //頂点数
	std::vector<VERTEX> vertices_;     //頂点情報
	ID3D11Buffer* pVertexBuffer_;    //頂点バッファ

	UINT64 indexNum;                 //インデックス数
	std::vector<int> index_;          //インデックス情報

	ID3D11Buffer* pIndexBuffer_;          //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;       //コンスタントバッファ

	Texture* pTexture_;                  //テクスチャ
public:
	Sprite();
	~Sprite();

	//初期化（ポリゴンを表示するための各種情報を準備）
	//戻り値：成功/失敗
	HRESULT Initialize();

	//描画
	//引数：worldMatrix　ワールド行列
	void Draw(Transform& transform);
	void Draw(Transform& transform, RECT rect, float alpha);

	//解放
	void Release();

	//画像サイズの取得
	//戻値：画像サイズ
	XMFLOAT2 GetTextureSize() { return pTexture_->GetTextureSize(); }

	//ロード
	//引数：fileName画像ファイル名
	//戻値：成功/失敗
	HRESULT Load(std::string fileName);

private:
	//---------Initiallizeから呼ばれる関数---------
	void InitVertexData();       //頂点情報の準備
	//HRESULT CreateVertexBuffer();         //頂点バッファを作成 InitVertexDataに吸収

	void InitIndexData();        //インデックス情報を準備
	//HRESULT CreateIndexBuffer();         //インデックスバッファを作成 InitIndexDataに吸収

	HRESULT CreateConstantBuffer();      //コンスタントバッファ作成

	HRESULT LoadTexture(std::string fileName);               //テクスチャをロード

	//---------Draw関数から呼ばれる関数----------
	void PassDataToCB(XMMATRIX worldMatrix);     //コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();                            //各バッファをパイプラインにセット
};

