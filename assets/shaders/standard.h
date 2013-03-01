#include "depth.h"
#include "utils.h"

float3 packNormal(float3 unPackedNormal) {
	float3 packedNormal = unPackedNormal * 0.5f + 0.5f;
	return packedNormal;
}

float3 unpackNormal(sampler2D normalSampler, float2 texCoord) {
	float3 packedNormal = tex2D(normalSampler, texCoord).xyz;
	float3 unPackedNormal = packedNormal * 2.0f - 1.0f;
	return unPackedNormal.xyz;
}

float4 packPosition(float4 unPackedPosition) {
	float4 packedPosition = unPackedPosition * 0.5f + 0.5f;
	return packedPosition;
}

float4 unpackPosition(sampler2D positionSampler, float2 texCoord) {
	float4 packedPosition = tex2D(positionSampler, texCoord);
	float4 unPackedPosition = packedPosition * 2.0f - 1.0f;
	return unPackedPosition;
}

float shadow(sampler2D shadowMap, float2 shadowCoord, float zToCompare) {
	float shadowBias = 0.0f;

#ifdef GCM
	shadowBias += 0.0001f;
#endif

	float depthToCompare = zToCompare - shadowBias;
	float shadowFactor = depthCompare(shadowMap, shadowCoord, depthToCompare);
	return shadowFactor;
}

float shadowPCF(sampler2D shadowMap, float2 shadowCoord, float zToCompare, float2 shadowMapSize) {
	float shadowFactor = 1.0f;
	float shadowBias = 0.0f;
#ifdef GCM
	shadowBias += 0.0001f;
#endif

	float sum = 0;
	float x, y;

	float depthToCompare = zToCompare - shadowBias;

	for (y = -1.5; y <= 1.5; y += 1.0) {
		for (x = -1.5; x <= 1.5; x += 1.0) {
			float2 shadowCoordOffset = shadowCoord + float2(x * shadowMapSize.x, y * shadowMapSize.y);
			float shadowFactor = depthCompare(shadowMap, shadowCoordOffset, depthToCompare);
			sum += shadowFactor;
		}
	}

	shadowFactor = sum / 16.0f;
	return shadowFactor;
}

float linearize(float depth, float near, float far) {
	return (-depth - near) / (far - near);
}
