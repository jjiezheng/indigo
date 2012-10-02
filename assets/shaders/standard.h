float4 packNormal(float4 unPackedNormal) {
	return 0.5f + unPackedNormal * 0.5f;
}

float4 unpackNormal(sampler2D normalSampler, float2 texCoord) {
	float4 normalData = tex2D(normalSampler, texCoord);
  	float4 unPackedNormal = (normalData * 2.0f) - 1.0f;
  	return unPackedNormal;
}


float unpackDepth(sampler2D depthSampler, float2 texCoord) {
#ifdef GCM
	return tex2D(depthSampler, texCoord).r;
#else
	return tex2D(depthSampler, texCoord).r;
#endif
}


