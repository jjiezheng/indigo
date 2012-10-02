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
	float3 rgb = tex2D(depthSampler, texCoord).arg;
	float3 colour = round(rgb * 255.0);
	float depth = dot(colour, float3(65535.0, 255.0, 1.0));
	depth *= 1.0/16777215.0; 
	return depth;
#else
	return tex2D(depthSampler, texCoord).r;
#endif
}


