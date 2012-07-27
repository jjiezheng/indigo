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
		       float2 texCoord 	: TEXCOORD0) {
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
  float depth = depthSpec.r;

  if (depth == 1.0f) {
    return float4(0, 0, 0, 0);
  }

  float specularPower = depthSpec.y;// * 255;
  float specularIntensity = depthSpec.z;

  float4 positionScreen;
  positionScreen.xy = (texCoord.xy * 2.0f) - 1.0f;
  positionScreen.y = -positionScreen.y;
  positionScreen.z = depth; 
  positionScreen.w = 1.0f;

  float4 positionWorldRaw = mul(ViewProjInv, positionScreen);
  float4 positionWorld = positionWorldRaw / positionWorldRaw.w;

  float4 lightVector = -LightDirection;

  // pulled from http://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_shading_model
  float distance = length(LightDirection);
  distance = distance * distance;

  // diffuse
  float diffuseStrength = max(0.0f, dot(normalize(normal), normalize(lightVector)));
  float3 diffuseContribution = LightColor * diffuseStrength / distance;

  //specular
  float specularContribution = 0;
  if (diffuseStrength > 0) {
    float3 viewDirectionRaw = ViewPosition - positionWorld;
    float3 viewDirection = normalize(viewDirectionRaw);

    float3 halfVectorRaw = lightVector + viewDirection;
    float3 halfVector = normalize(halfVectorRaw);

    float i = pow(saturate(dot(normalize(normal), halfVector)), specularPower);
    specularContribution = i * specularIntensity / distance;
  }

  return float4(diffuseContribution, specularContribution);
}

technique11 Main {
  pass P0 {
    SetVertexShader(CompileShader(vs_4_0, vs()));
    SetPixelShader(CompileShader(ps_4_0, ps()));
    SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
  }
}
