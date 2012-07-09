struct VOutput {
	float4 position			: POSITION;
	float2 texCoord			: TEXCOORD0;
};

float4 ps(float4 position 		: POSITION,
		  float2 texCoord 		: TEXCOORD0) : SV_TARGET0 {
	return float4(0, 0, 0, 1);// Texture.Sample(TextureSampler, texCoord);
}

VOutput vs(float4 position 		: POSITION,
		   float2 texCoord 		: TEXCOORD0) {
	VOutput OUT;
	OUT.position = position;
	OUT.texCoord = texCoord;
 	return OUT;
}

technique11 Test {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
	}
}
