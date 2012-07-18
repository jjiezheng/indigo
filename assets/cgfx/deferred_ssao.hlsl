#include "standard.hlsl"

uniform float2 NoiseScale;
uniform int SampleKernelSize;
uniform float4 SampleKernel[8];
uniform float Radius;

Texture2D NoiseMap;
SamplerState NoiseMapSamplerState {
	Filter = MIN_MAG_MIP_LINEAR;
};

Texture2D ColorMap;
SamplerState ColorMapSamplerState {
	Filter = MIN_MAG_MIP_LINEAR;
};

Texture2D NormalMap;
SamplerState NormalMapSamplerState {
	Filter = MIN_MAG_MIP_LINEAR;
};

Texture2D DepthMap;
SamplerState DepthMapSamplerState {
	Filter = MIN_MAG_MIP_LINEAR;
};

uniform float4x4 Projection;
uniform float4x4 WorldViewProj;
uniform float4x4 ViewProjInv;

struct VOutput {
      float4 position 			: SV_POSITION;
      float4 screenPosition		: TEXCOORD0;
};

VOutput vs(float4 position : POSITION) {
    VOutput OUT;
    OUT.position = position;
    OUT.screenPosition = OUT.position;
    return OUT;
}

float4 ps(float4 position 		: SV_POSITION,
		  float4 screenPosition : TEXCOORD0) : SV_TARGET0 {
	float3 screenPositionHom = screenPosition.xyz / screenPosition.w;
	float2 texCoord = contract(screenPositionHom);

	float4 normalData = NormalMap.Sample(NormalMapSamplerState, texCoord);
	float3 normal = normalData.xyz;

	float depth = DepthMap.Sample(DepthMapSamplerState, texCoord);

	float4 positionScreen;
	positionScreen.xy = screenPositionHom.xy;
	positionScreen.z = depth; 
	positionScreen.w = 1.0f;

	float4 positionWorldRaw = mul(ViewProjInv, positionScreen);
	float4 positionWorld = positionWorldRaw / positionWorldRaw.w;

	float4 randomNoiseData = NoiseMap.Sample(NoiseMapSamplerState, texCoord * NoiseScale);
	float3 randomNoise = contract(randomNoiseData);

	float3 tangent = normalize(randomNoise - normal * dot(randomNoise, normal));
	float3 bitangent = cross(normal, tangent);

	float3x3 tbn;
	tbn[0] = tangent;
	tbn[1] = bitangent;
	tbn[2] = normal;

	float occlusion = 0.0;
	for (int i = 0; i < SampleKernelSize; ++i) {
		//	get sample position:
		float3 sample = mul(tbn, SampleKernel[i].xyz);
		sample = sample * Radius + positionWorld;
			
		//	project sample position:
		float4 offset = float4(sample, 1.0);
		offset = mul(Projection, positionWorld);
		offset.xy /= offset.w;
		offset.xy = offset.xy * 0.5 + 0.5;

		//	get sample depth:
		float sample_depth = DepthMap.Sample(DepthMapSamplerState, texCoord);

		//	range check & accumulate:
		float range_check = abs(positionWorld.z - sample_depth) < Radius ? 1.0 : 0.0;
		occlusion += (sample_depth <= sample.z ? 1.0 : 0.0) * range_check;
	} 

	return float4(occlusion, occlusion, occlusion, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
