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
SamplerState DepthMapSamplerState {
	Filter = MIN_MAG_MIP_LINEAR;
};

uniform float4x4 Projection;
uniform float4x4 ProjInv;

uniform float4x4 ViewProjInv;
uniform float4x4 View;

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

float4 ps(float4 position 		: SV_POSITION,
		  float2 texCoord 		: TEXCOORD0) : SV_TARGET0 {
	float4 normalData = NormalMap.Sample(NormalMapSamplerState, texCoord);
	float3 normal = normalize(normalData.xyz);

	float depth = DepthMap.Sample(DepthMapSamplerState, texCoord).r;

	float4 positionScreen = float4(0, 0, 0, 1);
	positionScreen.xy = texCoord.xy * 2.0f - 1.0f;
	positionScreen.y = -positionScreen.y;
	positionScreen.z = depth;
	positionScreen.w = 1.0f;

	float4 positionViewRaw = mul(ProjInv, positionScreen);
	float4 positionView = positionViewRaw / positionViewRaw.w;

	float3 forward = normal;
	float3 up = float3(0, 1, 0);
	float3 right = cross(up, forward);
	up = cross(forward, right);

	float3x3 normalBasis = float3x3(right, up, forward);

	float occlusionContribution = 0;

	float3 samples[] = {
		{-0.60741, -0.547166, -0.559435},
		{0.704581, 0.824213, -0.975768},
		{-0.237953, 0.798456, -0.0737632},
		{-0.861385, 0.811029, -0.287362},
		{0.788018, -0.905148, -0.477126},
		{0.175329, -0.304605, -0.421216},
		{0.508957, 0.498031, -0.315378},
		{0.736198, -0.502426, -0.106967},
		{0.362774, 0.123631, -0.458754},
		{0.211524, 0.586596, -0.418867},
		{-0.486984, -0.471969, -0.189367},
		{0.0836512, 0.364849, -0.416242},
		{0.99884, 0.282937, -0.80401},
		{0.521592, 0.851741, -0.718375},
		{0.591357, 0.491195, -0.211127},
		{0.571703, 0.790704, -0.323344}
	};

	float radius = 0.1f;

	for (int i = 0; i < KernelSize; i++) {
		float3 sample = samples[i] * radius;

		float3 sampleAtNormalBasis = mul(sample, normalBasis);
		float3 sampleAtViewPosition = positionView + sampleAtNormalBasis;

		float4 sampleScreenRaw = mul(Projection, positionView);
		float4 sampleScreen = sampleScreenRaw / sampleScreenRaw.w;

		float4 sampleTexCoord = float4(0, 0, 0, 1);
		sampleTexCoord.xy = (sampleScreen.xy * 0.5f) + 0.5f;
		sampleTexCoord.y = 1.0f - sampleTexCoord.y;

		float sampleDepth = DepthMap.Sample(DepthMapSamplerState, sampleTexCoord).r;

		// the depths are coming out the same
		return float4(depth, sampleDepth, depth - sampleDepth, 1.0f);

		if (depth - sampleDepth > 0) {
			occlusionContribution += 1;
		}
	}

	float occlusion = 1.0f - (occlusionContribution / KernelSize);

	return float4(occlusion, occlusion, occlusion, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}