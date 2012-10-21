float unpackDepth(sampler2D depthSampler, float2 texCoord) {
#ifdef GCM
    // float3 depthColor = tex2D(depthSampler, texCoord).arg;
    // float3 depthFactor = float3(65536.0/16777215.0, 256.0/16777215.0, 1.0/16777215.0);
    // float depth = dot(round(depthColor * 255.0), depthFactor);
    // return depth;
  return texDepth2D_precise(depthSampler, texCoord).r;
#else
     return tex2D(depthSampler, texCoord).r;
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