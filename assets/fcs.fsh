#version 150

uniform sampler2DShadow shadowMap;

in vec4 shadowMapCoord;
out vec4 fragColor;

void main() {
  float shadowedness = textureProj(shadowMap, shadowMapCoord);
  fragColor = vec4(shadowedness * vec3(1), 1.0);
}
