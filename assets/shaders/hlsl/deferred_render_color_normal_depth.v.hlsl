uniform	float3x3 NormalMatrix;
uniform	float4x4 WorldViewProj;
uniform	float4x4 WorldView;
uniform	float4x4 World;

struct VOutput {
	float4 position			: SV_POSITION;
	float3 normal			: TEXCOORD0;
	float3 depth			: TEXCOORD1;
};

VOutput vs(float4 position 		: POSITION,
		   float4 normal 		: NORMAL) {
	VOutput OUT;
	OUT.position = mul(WorldViewProj, position);
	OUT.normal = normalize(mul(NormalMatrix, normal.xyz));
	OUT.depth.x = OUT.position.z;
	OUT.depth.y = OUT.position.w;

	float4 positionView = mul(WorldView, position);
 	OUT.depth.z = positionView.z;

 	return OUT;
}