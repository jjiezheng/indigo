#include "standard.hlsl"

uniform float2 NoiseScale;
uniform float Radius;

float4 samples[16] =
	{
		float4(0.355512, 	-0.709318, 	-0.0,	0.0 ),
		float4(0.534186, 	0.71511, 	-0.0,	0.0 ),
		float4(-0.87866, 	0.157139, 	-0.0,	0.0 ),
		float4(0.140679, 	-0.475516, 	-0.0,	0.0 ),
		float4(-0.0796121, 	0.158842, 	-0.0,	0.0 ),
		float4(-0.0759516, 	-0.101676, 	-0.0,	0.0 ),
		float4(0.12493, 	-0.0223423,	-0.0,	0.0 ),
		float4(-0.0720074, 	0.243395, 	-0.0,	0.0 ),
		float4(-0.207641, 	0.414286, 	0.0,	0.0 ),
		float4(-0.277332, 	-0.371262, 	0.0,	0.0 ),
		float4(0.63864, 	-0.114214, 	0.0,	0.0 ),
		float4(-0.184051, 	0.622119, 	0.0,	0.0 ),
		float4(0.110007, 	-0.219486, 	0.0,	0.0 ),
		float4(0.235085, 	0.314707, 	0.0,	0.0 ),
		float4(-0.290012, 	0.0518654, 	0.0,	0.0 ),
		float4(0.534186, 	0.71511, 	-0.0,	0.0 )
	};

Texture2D NoiseMap;
SamplerState NoiseMapSamplerState {
	AddressU = Wrap;
    AddressV = Wrap;
};

Texture2D NormalMap;
SamplerState NormalMapSamplerState {
	AddressU = Clamp;
    AddressV = Clamp;
};

Texture2D DepthMap;
SamplerState DepthMapSamplerState {
	AddressU = Clamp;
    AddressV = Clamp;
};

uniform float4x4 Projection;
uniform float4x4 WorldViewProj;
uniform float4x4 ProjInv;
uniform float4x4 ViewInv;
uniform float4x4 ViewProj;
uniform float4x4 ViewProjInv;

struct VOutput {
      float4 position 			: SV_POSITION;
      float4 texCoord		: TEXCOORD0;
};

VOutput vs(float4 position 	: POSITION,
		   float4 texCoord 	: TEXCOORD0) {
    VOutput OUT;
    OUT.position = position;
    OUT.texCoord = texCoord;
    return OUT;
}
float4 ps(float4 position 		: SV_POSITION,
		  float4 texCoord 		: TEXCOORD0) : SV_TARGET0 {
	float4 normalData = NormalMap.Sample(NormalMapSamplerState, texCoord);
	float3 normal = normalData.xyz;

	float depth = DepthMap.Sample(DepthMapSamplerState, texCoord);

	float4 positionScreen;
	positionScreen.xy = (texCoord.xy * 2.0f) - 1.0f;
	positionScreen.z = depth; 
	positionScreen.w = 1.0f;

	float4 positionViewRaw = mul(ProjInv, positionScreen);
	float4 positionView = positionViewRaw / positionViewRaw.w;

	float4 positionWorldRaw = mul(ViewProjInv, positionScreen);
	float4 positionWorld = positionWorldRaw / positionWorldRaw.w;	

	// SSAO
	float3 randomNormal = NoiseMap.Sample(NoiseMapSamplerState, texCoord * NoiseScale);
	randomNormal = normalize(randomNormal);

	float occlusion = 0.0f;
	float radius = 0.5f;

	float3 tangent = normalize(randomNormal - (normal * dot(randomNormal, normal)));
	float3 bitangent = cross(normal, tangent);
	float3x3 tbn = float3x3(bitangent, tangent, normal);

	// right up to here
	for (int i = 0; i < 16; i++) {	
		float3 sample = mul(tbn, samples[i].xyz);
		sample = (sample * radius) + positionView;

		float4 offset = float4(sample, 1.0f);
		offset = mul(Projection, offset);
		offset = offset / offset.w;

		offset.xy = (offset.xy * 0.5f) + 0.5f;

		float sampleDepth = DepthMap.Sample(DepthMapSamplerState, offset);

		//return float4(sampleDepth, sampleDepth, sampleDepth, 1.0f);

		float depthDifference = abs(positionView.z - sampleDepth);
		if (sampleDepth < depth) {
			occlusion += 0.8f;
		}
	}

	occlusion = 1.0f - (occlusion / 16.0f);

	return float4(occlusion, occlusion, occlusion, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
