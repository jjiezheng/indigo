attribute vec4 vertex;
uniform mat4 projection, model;

attribute vec2 textureCoords;
varying vec2 varyingTextureCoords;

void main() {  
  varyingTextureCoords = textureCoords;
  gl_Position = projection * model * vertex;
}