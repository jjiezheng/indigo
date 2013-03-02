#include "depth.h"
#include "utils.h"
#include "shadow.h"

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

float4 EncodeFloatRGBA( float v ) {
  float4 enc = float4(1.0f, 255.0f, 65025.0f, 160581375.0f) * v;
  enc = frac(enc);
  enc -= enc.yzww * float4(1.0f/255.0f,1.0f/255.0f,1.0f/255.0f,0.0f);
  return enc;
}

float DecodeFloatRGBA( float4 rgba ) {
  return dot( rgba, float4(1.0f, 1/255.0f, 1/65025.0f, 1/160581375.0f) );
}

float4 packLinearDepth(float unpackedDepth) {
	float4 packedDepth = EncodeFloatRGBA(unpackedDepth);
	return packedDepth;
}

float unpackLinearDepth(sampler2D depthSampler, float2 texCoord) {
	float4 packedDepth = tex2D(depthSampler, texCoord);
	float unpackedDepth = DecodeFloatRGBA(packedDepth);
	return unpackedDepth;
}

float linearize(float depth, float near, float far) {
	return (-depth - near) / (far - near);
}
