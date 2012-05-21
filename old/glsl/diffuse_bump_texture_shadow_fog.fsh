#version 150

out vec4 fragColor;

uniform vec3 ambient, diffuse;

uniform int numPointLights;
uniform vec3 lightPositions[6];

in vec3 oPosition;
in vec3 oViewPosition;
in vec2 oTextureCoords;
in vec4 oShadowMapCoords;

uniform sampler2D colorMap;
uniform sampler2D bumpMap;
uniform sampler2DShadow shadowMap;

uniform vec4 fogColor;
uniform float fogStart, fogEnd, fogFactor;
uniform int fogType;

void main() {   
  // ambient
  fragColor.rgb = ambient;
  
  // normal map
  vec3 bumpNormal = vec3(texture(bumpMap, oTextureCoords));
  bumpNormal = (bumpNormal -0.5) * 2.0;
  vec4 texture = texture(colorMap, oTextureCoords);
  
  // diffuse
  float diffuseStrength = 0.0;
  for (int i = 0; i < numPointLights; i++) {
    vec3 lightDirection = lightPositions[i] - oPosition;
    diffuseStrength += max(0.0, dot(normalize(bumpNormal), normalize(lightDirection)));
  }
  fragColor.rgb += texture.rgb * diffuseStrength;
  
  // shadow
  vec4 shadowCoord = oShadowMapCoords;
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
  if (fogType == 1) {
    f = clamp((fogEnd - oViewPosition.z) / (fogEnd - fogStart), 0, 1);
  }
  
  // exp  
  if (fogType == 2) {
    f = clamp(e * (fogFactor * oViewPosition.z), 0, 1);
  }
  
  // exp2
  if (fogType == 3) {
    f = clamp(pow(e * (fogFactor * oViewPosition.z), 2), 0, 1);
  }
  
  if (fogType != 0) {
    fragColor = (f * fragColor) + (1 - f) * fogColor; 
  }
}