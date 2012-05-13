#version 150

uniform sampler2D colorMap;

in vec2 oTextureCoords;
out vec4 fragColor;

void main() {
  vec4 texture = texture(colorMap, oTextureCoords);
  fragColor = vec4(texture.rgb, 1);
}
