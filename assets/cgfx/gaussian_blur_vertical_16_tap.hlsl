Texture2D SourceMap;
SamplerState SourceMapSamplerState;

float SceneHeight;

float offsets[8] = {1, 2, 3, 4, 5, 6, 7, 8};
float weights[8] = {0.2659615203, 0.2129653370, 0.1093400498, 0.0359939777, 0.0075973240, 0.0010281860, 0.0000892202, 0.0000049640};

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

	for (int i = 1; i < 8; i++) {
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
