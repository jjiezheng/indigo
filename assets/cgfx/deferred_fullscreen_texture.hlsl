SamplerState TextureMap;

struct VOutput {
	float4 position			: POSITION;
	float2 texCoord			: TEXCOORD0;
};

VOutput vs(float4 position 		: POSITION,
		   float2 texCoord 		: TEXCOORD0) {
	VOutput OUT;
	OUT.position = position;
	OUT.texCoord = texCoord;
 	return OUT;
}

float4 ps(float2 texCoord : TEXCOORD0) : COLOR {
	return tex2D(TextureMap, texCoord);
}

technique11 Test {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
	}
}
