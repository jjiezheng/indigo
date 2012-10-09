#include "depth.h"

float3 packNormal(float3 unPackedNormal) {
	return 0.5f + unPackedNormal * 0.5f;
}

float3 unpackNormal(sampler2D normalSampler, float2 texCoord) {
	float4 normalData = tex2D(normalSampler, texCoord);
  	float4 unPackedNormal = (normalData * 2.0f) - 1.0f;
  	return unPackedNormal.xyz;
}

float shadowPCF(sampler2D shadowMap, float2 shadowCoord, float zToCompare, float2 shadowMapSize) {
	float shadowFactor = 1.0f;
#ifdef GCM
	float lightDepth = unpackDepth(shadowMap, shadowCoord);

	if (lightDepth + 0.0005f < zToCompare) {
		shadowFactor = 0.0f;
	}
#else
	float sum = 0;
	float x, y;

	for (y = -1.5; y <= 1.5; y += 1.0) {
		for (x = -1.5; x <= 1.5; x += 1.0) {
			float2 shadowCoordOffset = shadowCoord + float2(x * shadowMapSize.x, y * shadowMapSize.y);
			sum += tex2Dproj(shadowMap, float4(shadowCoordOffset, zToCompare - 0.00007f, 1)).r;
		}
	}

	shadowFactor = sum / 16.0f;
#endif
	return shadowFactor;
}

float linearize(float depth, float near, float far) {
	return (-depth - near) / (far - near);
}
