#version 150

uniform samplerCube cubeMap;
in vec3 oTextureCoords;
in vec3 oViewPosition;

out vec4 fragColor;

uniform vec4 fogColor;
uniform float fogStart, fogEnd, fogFactor;
uniform int fogType;

void main() {
  // texture
  fragColor = texture(cubeMap, oTextureCoords);
  
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