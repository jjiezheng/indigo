#include "standard.hlsl"

Texture2D NormalMap;
SamplerState NormalMapSamplerState;

Texture2D DepthMap;
SamplerState DepthMapSamplerState;

Texture2D ShadowMap;
SamplerState ShadowMapSamplerState;

uniform float4 ViewPosition;

uniform float4 LightDirection;
uniform float4 LightPosition;
uniform float3 LightColor;

uniform float LightInnerAngle;
uniform float LightOuterAngle;
uniform float LightDecay;

uniform float4x4 View;
uniform float4x4 ViewProjInv;
uniform float4x4 ProjInv;
uniform float4x4 LightViewProj;
uniform float4x4 WorldViewProj;
uniform float4x4 NormalMatrix;

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
	float3 normal = normalize(normalData.xyz);
	float diffusePower = normalData.w;

	float4 depthSpec = DepthMap.Sample(DepthMapSamplerState, texCoord);

	float depth = depthSpec.x;
	float specularPower = depthSpec.z;
	float specularIntensity = depthSpec.w;

	float4 positionScreen = float4(screenPositionHom.xy, depthSpec.x, 1.0f);
	float4 positionWorldRaw = mul(ViewProjInv, positionScreen);
	float4 positionWorld = positionWorldRaw / positionWorldRaw.w;

	//------------------------------------------------------------
	// spot light
	//------------------------------------------------------------

	float distance = length(LightDirection);
  	distance = distance * distance;

	// diffuse
	float3 directionToLight = normalize(LightPosition.xyz - positionWorld.xyz);
	float lightDirectionDot = dot(normalize(LightDirection.xyz), -directionToLight);

	float diffuseStrength = 0.0f;

	float3 lightVector = normalize(-LightDirection.xyz);
  	lightVector = normalize(mul(NormalMatrix, lightVector));

	float lightOuterCos = cos(LightOuterAngle);
	float lightInnerCos = cos(LightInnerAngle);	

	if (lightDirectionDot > lightOuterCos) {
		diffuseStrength = max(0.0f, saturate(dot(normal, normalize(lightVector))));
		diffuseStrength *= smoothstep(lightOuterCos, lightInnerCos, lightDirectionDot);	
	}

	if (lightDirectionDot > lightInnerCos) {
		diffuseStrength = max(0.0f, saturate(dot(normal, normalize(lightVector))));
	}
	
	float3 diffuseContribution = LightColor * diffusePower * diffuseStrength / distance;

	//specular
	float specularContribution = 0;
	
	// suss with new view space calculations
	if (diffuseStrength > 0) {
		float3 viewDirectionRaw = ViewPosition - positionWorld;
		float3 viewDirection = normalize(viewDirectionRaw);

		float3 halfVectorRaw = lightVector + viewDirection;
		float3 halfVector = normalize(halfVectorRaw);

		halfVector = normalize(mul(NormalMatrix, halfVector));

		float i = pow(saturate(dot(normal, halfVector)), specularPower);
		specularContribution = i * specularIntensity / distance;
	}

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

	diffuseContribution *= shadowLightContribution;

	return float4(diffuseContribution, specularContribution);
} 

technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
