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
	float3 rawval = floor( 255.0 * tex2D(depthSampler, texCoord ).arg + 0.5);
float depth = dot( rawval, float3(0.996093809371817670572857294849,
               0.0038909914428586627756752238080039,
               1.5199185323666651467481343000015e-5) / 255.0);
return depth;
#else
	return tex2D(depthSampler, texCoord).r;
#endif
}


