#ifndef UTILS_H
#define UTILS_H

float2 flipY(float2 vec) {
#ifdef GL
  return vec;
#endif
  return float2(vec.x, -vec.y);
}

float3 expand(float3 vec) {
	return 2.0f * (vec - 1.0f);
}

float2 contract(float2 vec) {
	return 0.5f * (flipY(vec) + float2(1.0f, 1.0f));
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
