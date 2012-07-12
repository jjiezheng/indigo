float4 texMS(Texture2DMS<float> tex, float2 texCoord, int samples) {
	float4 sum = 0.0f;
	[unroll]
	for (int i = 0; i < samples; i++) {
		float4 c = tex.Load(texCoord, i);
		sum += c;
	}
	sum *= 1.0f / samples;
	return sum;
}