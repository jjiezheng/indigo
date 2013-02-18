float unpackDepth(sampler2D depthSampler, float2 texCoord) {
#ifdef GCM
  return texDepth2D_precise(depthSampler, texCoord).r;
#else
  return tex2D(depthSampler, texCoord).r * 2.0f - 1.0f;
#endif
}

float depthCompare(sampler2D depthMap, float2 texCoord, float depthToCompare) {
#ifdef GCM
  return texDepth2D_precise(depthMap, float3(texCoord, depthToCompare));
#else 
  return tex2Dproj(depthMap, float4(texCoord, depthToCompare, 1)).r;
#endif
}

float depthCompareSSAO(sampler2D depthMap, float2 texCoord, float depthToCompare) {
#ifdef GCM
  return texDepth2D_precise(depthMap, float3(texCoord, depthToCompare));
#else 
  return tex2Dproj(depthMap, float4(texCoord, depthToCompare, 1)).r;
#endif
}