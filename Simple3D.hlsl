//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer gmodel:register(b0)
{
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4    matW;           //ワールド行列
	float4x4	matNormal;           // ワールド行列
	float4      diffuseColor;        //マテリアルの色＝拡散反射係数
	bool        isTextured;           //テクスチャ貼ってあるかどうか
}
cbuffer gmodel:register(b1)
{
	float4      lightPosition;
	float4      eyePosition;
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos  : SV_POSITION;	//位置
	float2 uv	: TEXCOORD;		//UV座標
	float4 color	: COLOR;	//色（明るさ）
	float4 eyev     :POSITION;
	float4 normal   :NORMAL;
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
	//outData.pos = pos;
	outData.uv = uv;
	float normalout;
	normalout = mul(normal, matNormal);
	normal = normalize(normal);
	outData.normal = normal;

	float4 light = float4(0, 1.5, 1, 0);
	light = normalize(light);

	outData.color = saturate(dot(normal, light));
	float4 posw = mul(pos, matW);
	outData.eyev = eyePosition - posw;

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0, 1.0, 1.0, 1.0);
	float4 ambentSource = float4(0.2, 0.2, 0.2, 1.0);
	float4 diffuse;
	float4 ambient;
	float4 NL = saturate(dot(inData.normal, normalize(lightPosition)));

	float4 reflect = normalize(2 * NL * inData.normal - normalize(lightPosition));

	float4 specular = pow(saturate(dot(reflect, normalize(inData.eyev))), 8);

	if (isTextured == false)
	{
		diffuse = lightSource * diffuseColor * inData.color;
		ambient = lightSource * diffuseColor * ambentSource;
	}
	else
	{
		diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
		ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambentSource;
	}
	return diffuse + ambient + specular;
}
//return g_texture.Sample(g_sampler, inData.uv); // (diffuse + ambient);
//float4 diffuse = lightSource * inData.color;
// float4 ambient = lightSource * ambentSource;