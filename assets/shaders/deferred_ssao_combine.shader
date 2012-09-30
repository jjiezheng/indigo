#include "standard.h"

sampler2D ColorMap;
sampler2D SSAOMap;

struct VOutput {
	float4 position			: POSITION;
	float2 texCoord			: TEXCOORD0;
};

VOutput vs(float4 position 		: POSITION,
		   float2 texCoord 		: TEXCOORD0) {
	VOutput OUT;
	OUT.position = position;
	OUT.texCoord = texCoord;
 	return OUT;
}

float4 ps(float4 position	: POSITION,
		  float2 texCoord	: TEXCOORD0) : COLOR0 {
	float4 color = tex2D(ColorMap, texCoord);
	float4 ssao = tex2D(SSAOMap, texCoord);
	float4 finalColor = color * ssao;
	return finalColor;
}