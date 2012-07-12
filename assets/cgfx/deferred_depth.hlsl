uniform float4x4 WorldViewProj;

struct VOutput {
	float4 position			: SV_POSITION;
	float2 depth			: TEXCOORD0;
};

VOutput vs(float4 position : POSITION) {
	VOutput OUT;
	OUT.position = mul(WorldViewProj, position);
	OUT.depth.x = OUT.position.z;
	OUT.depth.y = OUT.position.w;
 	return OUT;
}

float4 ps(float4 position		: SV_POSITION,
		  float2 depth 			: TEXCOORD0) : SV_TARGET0 {
	float depthHom = depth.x / depth.y;
	return float4(depthHom, depthHom * depthHom, 0.0f, 1.0f);
}

technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
	}
}
