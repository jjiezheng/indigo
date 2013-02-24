#ifndef UTILS_H
#define UTILS_H

float2 flipY(float2 vec) {
#ifdef GL
  return vec;
#else
  return float2(vec.x,  1.0 - vec.y);
 #endif
}

float2 ndc2tex(float2 ndc) {
	float2 tex = ndc * 0.5f + 0.5f;
	float2 flipped = flipY(tex);
	return flipped;
}

float4 tex2NDC(float2 texCoord, float depth) {
	float4 positionScreen;
	positionScreen.xy = texCoord.xy * 2.0f - 1.0f;

#ifndef GL
	positionScreen.y = 1.0f - positionScreen.y;
#endif

	positionScreen.z = depth;
	positionScreen.w = 1.0f;

	return positionScreen;
}

float linstep(float min, float max, float v) {
  return clamp((v - min) / (max - min), 0, 1);  
}  

float ReduceLightBleeding(float p_max, float Amount) {  
  // Remove the [0, Amount] tail and linearly rescale (Amount, 1].  
   return linstep(Amount, 1, p_max);  
}

float ChebyshevUpperBound(float2 moments, float depth, float shadowBias) {  
	float mean = moments.x;
	float meanSqr = moments.y;
	float Ex_2 = mean * mean; 
	float E_x2 = meanSqr;
	float variance = min(max(E_x2 - Ex_2, 0.0f) + shadowBias, 1.0f);
	float m_d = (depth - mean);
	float p_max = variance / (variance + m_d * m_d);
  float p = depth <= mean;
  return max(p, p_max);	
}  

#endif
