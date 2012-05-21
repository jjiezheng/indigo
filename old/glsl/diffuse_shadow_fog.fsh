#version 150

out vec4 fragColor;

uniform vec3 ambient, diffuse;

uniform int numPointLights;
uniform vec3 lightPositions[6];

in vec3 oNormal;
in vec3 oPosition;
in vec3 oViewPosition;

uniform sampler2DShadow shadowMap;
in vec4 shadowMapCoord;

uniform vec4 fogColor;
uniform float fogStart, fogEnd, fogFactor;
uniform int fogType;

void main() {   
  // ambient
  fragColor.rgb = ambient;
  
  // diffuse
  float diffuseStrength = 0.0;
  for (int i = 0; i < numPointLights; i++) {
    vec3 lightDirection = lightPositions[i] - oPosition;
    diffuseStrength += max(0.0, dot(normalize(oNormal), normalize(lightDirection)));
  }
  fragColor.rgb += diffuse * diffuseStrength;
  
  // shadow
  vec4 shadowCoord = shadowMapCoord;
  shadowCoord.z += 0.0005;
  
  if (shadowCoord.w > 0.0f) {
    float depth = textureProj(shadowMap, shadowCoord);
    float visibility = (depth == 0) ? 0.5 : 1.0;
    fragColor.rgb = fragColor.rgb * visibility;
  }
  
  // fog
  float e = 2.718281828;
  float f = 0;
  
  // linear
  if (fogType == 0) {
    f = clamp((fogEnd - oViewPosition.z) / (fogEnd - fogStart), 0, 1);
  }
  
  // exp  
  if (fogType == 1) {
    f = clamp(e * (fogFactor * oViewPosition.z), 0, 1);
  }
  
  // exp2
  if (fogType == 2) {
    f = clamp(pow(e * (fogFactor * oViewPosition.z), 2), 0, 1);
  }
  
  fragColor = (f * fragColor) + (1 - f) * fogColor;      
}
