#version 150

uniform sampler2D colorMap;
uniform sampler2D bleedColorMap;

in vec2 oTextureCoords;
out vec4 fragColor;

void main() {
  vec4 mask = texture(bleedColorMap, oTextureCoords);
  float alpha = length(mask.xyz);
  vec4 texture = texture(colorMap, oTextureCoords);
  fragColor = vec4(texture.rgb, alpha);
}
