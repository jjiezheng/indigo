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
	// float Ex_2 = moments.x * moments.x; 
	// float E_x2 = moments.y;
	// float variance = min(max(E_x2 - Ex_2, 0.000001f) + bias, 1.0f);
	// float m_d = (-distance - moments.x);
	// float p = variance / (variance + m_d * m_d);
	// return max(p, distance <= moments.x);
    
    float E_x2 = moments.y;
    float Ex_2 = moments.x * moments.x;
    float variance = E_x2 - Ex_2;    
    float mD = (moments.x - distance );
    float mD_2 = mD * mD;
    float p = variance / (variance + mD_2 );

    float p_max = max( p, distance <= moments.x );
    p_max = linstep(0.000002, 1.0, p_max);
    p_max = clamp(max(p, p_max), 0.0, 1.0);
    return p_max;

    // float p = smoothstep(distance-0.000002, distance, moments.x);
    // float variance = max(moments.y - moments.x*moments.x, -0.001);
    // float d = distance - moments.x;
    // float p_max = linstep(0.2, 1.0, variance / (variance + d*d));
    // return clamp(max(p, p_max), 0.0, 1.0);

    
}

float shadowVSM(sampler2D shadowMap, float2 shadowCoord, float zToCompare, float shadowBias) {
	float4 moments = tex2D(shadowMap, shadowCoord);
	float shadowFactor = chebyshevUpperBound(moments.xy, zToCompare, shadowBias);
	return shadowFactor;
}