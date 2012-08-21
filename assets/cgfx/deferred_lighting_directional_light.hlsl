#include "standard.hlsl"

Texture2D NormalMap;
SamplerState NormalSamplerState {
  Filter = MIN_MAG_MIP_LINEAR;
};

Texture2D DepthMap;
SamplerState DepthMapSamplerState {
  Filter = MIN_MAG_MIP_LINEAR;
};

uniform float4x4 View;
uniform float4x4 ViewProjInv;
uniform float4x4 NormalMatrix;

uniform float4 ViewPosition;
uniform float4 LightDirection;
uniform float3 LightColor;

struct VOutput {
	float4 position 			: SV_POSITION;
	float2 texCoord				: TEXCOORD0;
};

VOutput vs(float4 position 	: POSITION,
		       float2 texCoord 	: TEXCOORD0) {
    VOutput OUT;
    OUT.position = position;
    OUT.texCoord = texCoord;
    return OUT;
}

float4 ps(float4 position : SV_POSITION,
          float2 texCoord	: TEXCOORD0) : SV_TARGET0 {
  float3 depthSpec = DepthMap.Sample(DepthMapSamplerState, texCoord);

  if (depthSpec.r == 1.0f) {
    return float4(0, 0, 0, 0);
  }

  float4 normalData = NormalMap.Sample(NormalSamplerState, texCoord);
  float3 normal = normalize(normalData.xyz);

  float3 lightVector = -LightDirection.xyz;
  lightVector = normalize(mul(NormalMatrix, lightVector));

  // Blinn+Phong from http://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_shading_model

  // diffuse
  float diffuseStrength = max(0.0f, dot(normalize(normal), normalize(lightVector)));
  float3 diffuseContribution = LightColor * diffuseStrength;

  return float4(diffuseContribution, 0);
}

technique11 Main {
  pass P0 {
    SetVertexShader(CompileShader(vs_4_0, vs()));
    SetPixelShader(CompileShader(ps_4_0, ps()));
    SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
  }
}
