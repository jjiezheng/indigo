#include "standard.hlsl"

Texture2D NormalMap;
SamplerState NormalSamplerState {
  Filter = MIN_MAG_MIP_LINEAR;
};

Texture2D DepthMap;
SamplerState DepthMapSamplerState {
  Filter = MIN_MAG_MIP_LINEAR;
};

uniform float4x4 ViewProjInv;

uniform float4 ViewPosition;
uniform float4 LightDirection;
uniform float3 LightColor;

struct VOutput {
	float4 position 			: SV_POSITION;
	float2 texCoord				: TEXCOORD0;
};

VOutput vs(float4 position 	: POSITION,
		       float4 texCoord 	: TEXCOORD0) {
    VOutput OUT;
    OUT.position = position;
    OUT.texCoord = texCoord;
    return OUT;
}

float4 ps(float4 position : SV_POSITION,
          float2 texCoord	: TEXCOORD0) : SV_TARGET0 {
  float4 normalData = NormalMap.Sample(NormalSamplerState, texCoord);
  float3 normal = normalData.xyz;

  float3 depthSpec = DepthMap.Sample(DepthMapSamplerState, texCoord);
  float depth = depthSpec.x;
  float specularPower = depthSpec.y * 255;
  float specularIntensity = depthSpec.z;

  float4 positionScreen;
  positionScreen.xy = (texCoord.xy * 2.0f) - 1.0f;
  positionScreen.y = -positionScreen.y;
  positionScreen.z = depth; 
  positionScreen.w = 1.0f;

  float4 positionWorldRaw = mul(ViewProjInv, positionScreen);
  float4 positionWorld = positionWorldRaw / positionWorldRaw.w;

  float4 lightVector = -LightDirection;

  // diffuse
  float diffuseStrength = max(0.0f, dot(normalize(normal), normalize(lightVector)));
  float3 diffuseContribution = LightColor * diffuseStrength;

  //specular
  float3 reflectionVector = normalize(reflect(lightVector, normal));

  float3 viewDirection = normalize(ViewPosition - positionWorld).xyz;
  float specularContribution = specularIntensity * pow(saturate(dot(reflectionVector, viewDirection)), specularPower);

  return float4(diffuseContribution, specularContribution);
}

technique11 Main {
  pass P0 {
    SetVertexShader(CompileShader(vs_4_0, vs()));
    SetPixelShader(CompileShader(ps_4_0, ps()));
    SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
  }
}
