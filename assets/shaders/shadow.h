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

float chebyshevUpperBound(float2 moments, float distance, float bias) {	
	if (distance <= moments.x) {
		return 1.0f;
	}

	float variance = moments.y - (moments.x*moments.x);
	variance = max(variance, bias);
	
	float d = distance - moments.x;
	float p_max = variance / (variance + d*d);
	
	return p_max;
}

float reduceLightBleed(float p_max, float lightBleed) {
	return smoothstep(lightBleed, 1.0f, p_max);
}

float shadowVSM(sampler2D shadowMap, float2 shadowCoord, float zToCompare, float shadowBias, float lightBleed) {
	float4 moments = tex2D(shadowMap, shadowCoord);
	float shadowFactor = chebyshevUpperBound(moments.xy, zToCompare, shadowBias);
	shadowFactor = reduceLightBleed(shadowFactor, lightBleed);
	return shadowFactor;
}