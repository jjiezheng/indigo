#include "standard.hlsl"

uniform float Radius;
uniform float KernelSize;
uniform float2 NoiseScale;
uniform float4 Kernel[16];

Texture2D NoiseMap;
SamplerState NoiseMapSamplerState {
	AddressU = Wrap;
    AddressV = Wrap;
};

Texture2D NormalMap;
SamplerState NormalMapSamplerState;

Texture2D DepthMap;
SamplerState DepthMapSamplerState;

uniform float4x4 Projection;
uniform float4x4 ProjInv;

struct VOutput {
      float4 position 		: SV_POSITION;
      float2 texCoord		: TEXCOORD0;
};

VOutput vs(float4 position 	: POSITION,
		   float2 texCoord 	: TEXCOORD0) {
    VOutput OUT;
    OUT.position = position;
    OUT.texCoord = texCoord;
    return OUT;
}

float ambientOcclusion(float2 texCoord, float2 uv, float3 position, float3 normal) {
	float intensity = 1;
	float bias = 1;

	float3 diff = getPosition(texCoord + uv) - position;
	float3 diffN = normalize(diff);
	float distance = length(diff) * g_scale;
	return max(0.0, dot(normal, diffN) - bias) * (1.0 / (1.0 + distance)) * intensity;
}

float4 ps(float4 position 		: SV_POSITION,
		  float2 texCoord 		: TEXCOORD0) : SV_TARGET0 {
	float4 normalData = NormalMap.Sample(NormalMapSamplerState, texCoord);
	float3 normal = normalData.xyz;

	float depth = DepthMap.Sample(DepthMapSamplerState, texCoord).g;

	float4 positionScreen;
	positionScreen.xy = texCoord.x * 2.0f - 1.0f;
	positionScreen.y = (1.0f - texCoord.y) * 2.0f - 1.0f;
	positionScreen.z = depth;
	positionScreen.w = 1.0f;

	float4 positionViewRaw = mul(ProjInv, positionScreen);
	float4 positionView = positionViewRaw / positionViewRaw.w;

	float3 randomNormal = NoiseMap.Sample(NoiseMapSamplerState, texCoord * NoiseScale);
	randomNormal = normalize(randomNormal);

	const float2 vec[4] = { 
		float2( 1,  0),
		float2(-1,  0),
        float2( 0,  1),
        float2( 0, -1)
	};

	float occlusion = 0.0f;
	float radius = 5.0f / positionView.z;

	int iterations = 4;

	for (int i = 0; i < iterations; ++i) {
		float2 coord1 = reflect(vec[i], randomNormal) * radius;
		float2 coord2 = float2(coord1.x * 0.707 - coord1.y * 0.707, coord1.x = 0.707 + coord1.y * 0.707);

		occlusion += ambientOcclusion(texCoord, coord1 * 0.25, positionView, normal);
		occlusion += ambientOcclusion(texCoord, coord2 * 0.50, positionView, normal);

		occlusion += ambientOcclusion(texCoord, coord1 * 0.25, positionView, normal);
		occlusion += ambientOcclusion(texCoord, coord2 * 0.00, positionView, normal);
	}

	occlusion /= (float)iterations * 4.0;

	return float4(occlusion, occlusion, occlusion, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
