uniform	float4x4 Projection;

struct VOutput {
	float4 position			: SV_POSITION;
};

VOutput vs(float4 position 		: POSITION) {
	VOutput OUT;
	OUT.position =  mul(Projection, position);
 	return OUT;
}

struct POutput {
	float4 color 	: SV_TARGET0;
};

POutput ps(float4 position			: SV_POSITION) {
	POutput OUT;
	OUT.color = float4(1, 1, 1, 1);				
	return OUT;
}

technique11 Test {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
	}
}