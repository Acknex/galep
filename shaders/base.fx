// Lambert bump mapping
// (c) oP group 2008  Version 2.1

float4x4 matWorld;
float4x4 matWorldViewProj;

float4 vecLightPos[8];

texture entSkin1;
sampler skin1Sampler = sampler_state { Texture = <entSkin1>; MipFilter = Linear; };

struct VSIN
{
	float3 position : POSITION;
	float2 texcoord : TEXCOORD0;
	float3 normal : NORMAL;
};

struct VSOUT
{
	float4 projectedPosition : POSITION;
	float2 texcoord : TEXCOORD0;
	float3 worldPosition : TEXCOORD1;
	float3 worldNormal : NORMAL;
};

VSOUT baseVS(VSIN input)
{
	VSOUT output;
	output.projectedPosition = mul(float4(input.position, 1.0f), matWorldViewProj);
	output.texcoord = input.texcoord;
	output.worldPosition = mul(float4(input.position, 1.0f), matWorld);
	output.worldNormal = mul(float4(input.normal, 0.0f), matWorld);
	return output;
}

float4 basePS(VSOUT input) : COLOR0
{
	float4 color = tex2D(skin1Sampler, input.texcoord.xy);
	
	float3 lightDir = normalize(vecLightPos[0]-input.worldPosition);
	color.rgb *= saturate(dot(lightDir, input.worldNormal));
	return color;
}

technique base
{
	pass one
	{
		ZEnable = true;
		ZWriteEnable = true;
		VertexShader = compile vs_3_0 baseVS();
		PixelShader = compile ps_3_0 basePS();
	}
}
