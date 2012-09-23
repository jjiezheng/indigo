uniform	float4x4 WorldViewProj;

struct VOutput {
	float4 position			: SV_POSITION;
};

VOutput vs(float4 position 		: POSITION) {
	VOutput OUT;
	OUT.position =  mul(WorldViewProj, position);
 	return OUT;
}