#version 150

uniform sampler2DShadow shadowMapTexture;

in vec4 shadowMapCoord;
out vec4 fragColor;

void main() {
  float shadowedness = textureProj(shadowMapTexture, shadowMapCoord);
  fragColor = vec4(shadowedness * vec3(1), 1.0);
}
