#include "standard.hlsl"

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


uniform float4x4 WorldViewProj;

struct VOutput {
      float4 position 			: SV_POSITION;
      float4 screenPosition		: TEXCOORD0;
};

VOutput vs(float4 position : POSITION) {
    VOutput OUT;
    OUT.position = mul(WorldViewProj, position);
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

	

	vec3 rvec = texture(RANDOM, TEXCOORD * NOISE_SCALE).xyz * 2.0 - 1.0;

	vec3 tangent = normalize(rvec - normal * dot(rvec, normal));
	vec3 bitangent = cross(normal, tangent);

	mat3 tbn = mat3(tangent, bitangent, normal);

}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
