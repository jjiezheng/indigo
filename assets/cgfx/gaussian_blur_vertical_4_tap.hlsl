Texture2D SourceMap;
SamplerState SourceMapSamplerState;

float SceneHeight;

float offsets[4] = {1, 2, 3, 4};
float weights[4] = {0.7978845608, 0.1079819330, 0.0002676605, 0.0000000122};

struct VOutput {
	float4 position 			: SV_POSITION;
	float2 centerTap			: TEXCOORD0;
};

VOutput vs(float4 position 	: POSITION,
		   float2 texCoord 	: TEXCOORD0) {
    VOutput OUT;
    OUT.position = position;
    OUT.centerTap = texCoord;
    return OUT;
}

float4 ps(float4 position  : SV_POSITION,
		  float2 centerTap : TEXCOORD0) : SV_TARGET0 {
	
	float4 color = SourceMap.Sample(SourceMapSamplerState, centerTap) * weights[0];

	float4x4 samples;

	float texelSize = 1.0f / SceneHeight;

	for (int i = 1; i < 4; i++) {
		float2 offset = float2(1, 0) * offsets[i] * texelSize;

		float2 rightTap = centerTap + offset;
		color += SourceMap.Sample(SourceMapSamplerState, rightTap) * weights[i];

		float2 leftTap = centerTap - offset;
		color += SourceMap.Sample(SourceMapSamplerState, leftTap) * weights[i];
	}

	return color;
}

technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
	}
}
