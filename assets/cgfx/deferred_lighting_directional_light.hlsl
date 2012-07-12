#include "utils.cg"

Texture2D NormalMap;
SamplerState NormalSamplerState;

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

  float3 finalColor;

  // diffuse
  float4 lightVector = -LightDirection;
  float diffuseStrength = max(0.0f, dot(normalize(normal), normalize(lightVector)));
  finalColor = LightColor * diffuseStrength;

  return float4(finalColor, diffuseStrength);
}

technique11 Main {
  pass P0 {
    SetVertexShader(CompileShader(vs_4_0, vs()));
    SetPixelShader(CompileShader(ps_4_0, ps()));
  }
}
