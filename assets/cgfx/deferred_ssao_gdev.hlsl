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

float4 positionViewSpace(float2 texCoord, float4x4 inverseProjection) {
	float depth = DepthMap.Sample(DepthMapSamplerState, texCoord).r;

	float4 positionScreen;
	positionScreen.xy = texCoord.xy * 2.0f - 1.0f;
	positionScreen.y = -positionScreen.y;
	positionScreen.z = depth;
	positionScreen.w = 1.0f;

	float4 positionViewRaw = mul(inverseProjection, positionScreen);
	float4 positionView = positionViewRaw / positionViewRaw.w;
	return positionView;
}

float ambientOcclusion(float2 texCoord, float2 uv, float3 position, float3 normal) {
	float intensity = 2;
	float bias = 0.002;
	float scale = 2.0;

	float3 diff = positionViewSpace(texCoord + uv, ProjInv) - position;
	float3 diffN = normalize(diff);

	float distance = length(diff) * scale;

	float occlusion = max(0.0, dot(normal, diffN)) * (1.0f / (1.0f + distance)) * intensity;

	return occlusion;
}

float4 ps(float4 position 		: SV_POSITION,
		  float2 texCoord 		: TEXCOORD0) : SV_TARGET0 {
	float4 normalData = NormalMap.Sample(NormalMapSamplerState, texCoord);
	float3 normal = normalize(normalData.xyz);

	float4 positionView = positionViewSpace(texCoord, ProjInv);

	float3 randomNormal = NoiseMap.Sample(NoiseMapSamplerState, texCoord * NoiseScale);
	randomNormal = normalize(randomNormal);

	const float2 vec[4] = { 
		float2( 1,  0),
		float2(-1,  0),
        float2( 0,  1),
        float2( 0, -1)
	};

	float occlusion = 0.0f;
	float radius = 0.05f / positionView.z;

	int iterations = 4;

	float depth = DepthMap.Sample(DepthMapSamplerState, texCoord).r;

	for (int i = 0; i < iterations; ++i) {
		if (depth < 1.0f) {
			float2 coord1 = reflect(vec[i], randomNormal) * radius;

			float2 coord2 = float2(coord1.x * 0.707 - coord1.y * 0.707, coord1.x * 0.707 + coord1.y * 0.707);

			occlusion += ambientOcclusion(texCoord, coord1 * 0.25, positionView, normal);
			occlusion += ambientOcclusion(texCoord, coord2 * 0.50, positionView, normal);
			occlusion += ambientOcclusion(texCoord, coord1 * 0.75, positionView, normal);
			occlusion += ambientOcclusion(texCoord, coord2, positionView, normal);
		}
	}

	occlusion /= (float)iterations * 4;

	occlusion = 1.0f - (occlusion * 1);

	return float4(occlusion, occlusion, occlusion, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
