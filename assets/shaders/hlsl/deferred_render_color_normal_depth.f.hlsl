uniform	float3 DiffuseColor;
uniform	float3 AmbientColor;

uniform float DiffusePower;
uniform float SpecularPower;
uniform float SpecularIntensity;

uniform float Far;
uniform float Near;

struct POutput {
	float4 color 	: SV_TARGET0;
	float4 normal 	: SV_TARGET1;
	float4 depth 	: SV_TARGET2;
};

POutput ps(float4 position			: SV_POSITION,
		   float3 normal			: TEXCOORD0,
		   float3 depth 			: TEXCOORD1) {
	POutput OUT;
	
	OUT.color = float4(DiffuseColor, 1);					
	OUT.normal = float4(normal, DiffusePower);

	float depthNDC = depth.x / depth.y; // z / w
	float depthLinear = (-depth.z - Near) / (Far - Near);
	OUT.depth = float4(depthNDC, depthLinear, SpecularPower, SpecularIntensity);

	return OUT;
}