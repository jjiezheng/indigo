varying vec2 varyingTextureCoords;
uniform sampler2D colorMap;

void main() {
  gl_FragColor = texture2D(colorMap, varyingTextureCoords);
}
