#include "standard.hlsl"

uniform float2 NoiseScale;
uniform float Radius;

float4 samples[16] =
	{
		float4(0.355512, 	-0.709318, 	-0.102371,	0.0 ),
		float4(0.534186, 	0.71511, 	-0.115167,	0.0 ),
		float4(-0.87866, 	0.157139, 	-0.115167,	0.0 ),
		float4(0.140679, 	-0.475516, 	-0.0639818,	0.0 ),
		float4(-0.0796121, 	0.158842, 	-0.677075,	0.0 ),
		float4(-0.0759516, 	-0.101676, 	-0.483625,	0.0 ),
		float4(0.12493, 	-0.0223423,	-0.483625,	0.0 ),
		float4(-0.0720074, 	0.243395, 	-0.967251,	0.0 ),
		float4(-0.207641, 	0.414286, 	0.187755,	0.0 ),
		float4(-0.277332, 	-0.371262, 	0.187755,	0.0 ),
		float4(0.63864, 	-0.114214, 	0.262857,	0.0 ),
		float4(-0.184051, 	0.622119, 	0.262857,	0.0 ),
		float4(0.110007, 	-0.219486, 	0.435574,	0.0 ),
		float4(0.235085, 	0.314707, 	0.696918,	0.0 ),
		float4(-0.290012, 	0.0518654, 	0.522688,	0.0 ),
		float4(0.0975089, 	-0.329594, 	0.609803,	0.0 )
	};

Texture2D NoiseMap;
SamplerState NoiseMapSamplerState {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
    AddressV = Wrap;
};

Texture2D NormalMap;
SamplerState NormalMapSamplerState {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
    AddressV = Clamp;
};

Texture2D DepthMap;
SamplerState DepthMapSamplerState {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
    AddressV = Clamp;
};

uniform float4x4 Projection;
uniform float4x4 WorldViewProj;
uniform float4x4 ViewProj;
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

	// SSAO
	float3 randomNormal = NoiseMap.Sample(NoiseMapSamplerState, texCoord * NoiseScale);

	float occlusion = 0.0f;

	float radius = 0.5f;

	for (int i = 0; i < 16; i++) {
		float3 ray = reflect(samples[i].xyz, randomNormal) * radius;

		if (dot(ray, normal) < 0) {
			ray += normal * radius;
		}

		float4 sample = float4(positionScreen.xyz, 1.0f);
		float4 screenSpaceCoord = mul(sample, Projection);
		float2 sampleTexCoord = contract(screenSpaceCoord);

		if (sampleTexCoord.x > 0.0f && sampleTexCoord.x < 1.0f && sampleTexCoord.y > 0.0f && sampleTexCoord.y < 1.0f) {

			float sampleDepth = DepthMap.Sample(DepthMapSamplerState, sampleTexCoord);

			return float4(sampleDepth, sampleDepth, sampleDepth, 1);

			if (sampleDepth <= depth) {
				occlusion += 0.4f;
			}

			/*if (sampleDepth != 1.0f) {
				//occlusion += 20 * max(sampleDepth - depth, 0.0f);
				occlusion += 1.0f;
			}*/
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
