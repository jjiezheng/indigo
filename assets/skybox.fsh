#version 150

uniform samplerCube cubeMap;
in vec3 oTextureCoords;

out vec4 fragColor;

void main() {
  fragColor = texture(cubeMap, oTextureCoords);
}
