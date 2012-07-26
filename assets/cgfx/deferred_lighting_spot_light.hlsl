#include "standard.hlsl"

Texture2D NormalMap;
SamplerState NormalMapSamplerState;

Texture2D DepthMap;
SamplerState DepthMapSamplerState;

Texture2D ShadowMap;
SamplerState ShadowMapSamplerState;

uniform bool ShadowsEnabled;

uniform float4 ViewPosition;

uniform float4 LightDirection;
uniform float4 LightPosition;
uniform float3 LightColor;

uniform float LightInnerAngle;
uniform float LightOuterAngle;
uniform float LightDecay;

uniform float4x4 ViewProjInv;
uniform float4x4 LightViewProj;
uniform float4x4 WorldViewProj;

struct VOutput {
      float4 position 			: SV_POSITION;
      float4 screenPosition 	: TEXCOORD0;
};

VOutput vs(float4 position : POSITION) {
    VOutput OUT;
    OUT.position = mul(WorldViewProj, position);
    OUT.screenPosition = OUT.position;
    return OUT;
}

float4 ps(float4 position 		: SV_POSITION,
		  float4 screenPosition : TEXCOORD0) : SV_TARGET0 {
	float3 screenPositionHom = screenPosition / screenPosition.w;
	float2 texCoord = contract(screenPositionHom);

	//------------------------------------------------------------
	// world position
	//------------------------------------------------------------

	float4 normalData = NormalMap.Sample(NormalMapSamplerState, texCoord);
	float3 normal = normalData.xyz;

	float3 depth = DepthMap.Sample(DepthMapSamplerState, texCoord);

	float4 positionScreen;
	positionScreen.xy = screenPositionHom.xy;
	positionScreen.z = depth; 
	positionScreen.w = 1.0f;

	float4 positionWorldRaw = mul(ViewProjInv, positionScreen);
	float4 positionWorld = positionWorldRaw / positionWorldRaw.w;

	float4 finalColor = float4(0, 0, 0, 0.0f);

	//------------------------------------------------------------
	// spot light
	//------------------------------------------------------------

	// diffuse
	float3 directionToLight = LightPosition - positionWorld;
	float3 directionOfLight = -LightDirection;
	float lightDirectionDot = max(0.0f, dot(normalize(directionOfLight), normalize(directionToLight)));

	float lightOuterCos = cos(LightOuterAngle);
	float lightInnerCos = cos(LightInnerAngle);

	float diffuseStrength = 0.0f;

	if (lightDirectionDot > lightOuterCos) {
		diffuseStrength = max(0.0f, dot(normalize(normal), normalize(directionOfLight)));
		float attenuation = LightDecay;
		finalColor.rgb = LightColor * diffuseStrength * smoothstep(lightOuterCos, lightInnerCos, lightDirectionDot);
		finalColor.a = diffuseStrength;	
	}

	if (lightDirectionDot > lightInnerCos) {
		diffuseStrength = max(0.0f, dot(normalize(normal), normalize(directionOfLight)));
		finalColor.rgb = LightColor * diffuseStrength;
		finalColor.a = diffuseStrength;
	}

	float4 viewDirection = ViewPosition - positionWorld;
	float4 lightDirection = LightPosition - positionWorld;

	// specular
	float3 halfVector = normalize(viewDirection.xyz + lightDirection.xyz);
	float halfDotNormal = max(0.0f, dot(halfVector, normal));
	float specularContribution = saturate(pow(halfDotNormal, 0.2));
	float SpecularPower = 1;
	finalColor.rgb += specularContribution * float4(1, 1, 1, 1) * SpecularPower * diffuseStrength;

	//------------------------------------------------------------
	// shadows
	//------------------------------------------------------------
	float4 pixelWorldPositionFromLight = mul(LightViewProj, positionWorld);
	float3 pixelWorldPositionFromLightHom = pixelWorldPositionFromLight / pixelWorldPositionFromLight.w;

	float2 shadowCoord = contract(pixelWorldPositionFromLightHom);
	float3 moments = ShadowMap.Sample(ShadowMapSamplerState, shadowCoord);

	float shadowLightContribution = 1.0f;

	if (moments.x < pixelWorldPositionFromLightHom.z && shadowCoord.x > 0.0f && shadowCoord.x < 1.0f) {
		shadowLightContribution = ChebyshevUpperBound(moments.xy, pixelWorldPositionFromLightHom.z, 0.0000005f);
		shadowLightContribution = ReduceLightBleeding(shadowLightContribution, 0.9f);
	}

	finalColor.rgb *= shadowLightContribution;

	return finalColor;
} 

technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(Add, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
