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
	float Ex_2 = moments.x * moments.x; 
	float E_x2 = moments.y;
	float variance = min(max(E_x2 - Ex_2, 0.0f) + bias, 1.0f);
	float m_d = (-distance - moments.x);
	float p = variance / (variance + m_d * m_d);
	return max(p, distance <= moments.x);
}

float shadowVSM(sampler2D shadowMap, float2 shadowCoord, float zToCompare, float shadowBias) {
	float4 moments = tex2D(shadowMap, shadowCoord);
	float shadowFactor = chebyshevUpperBound(moments.xy, zToCompare, shadowBias);
	return shadowFactor;
}