#version 150 

uniform mat4 projection, model;

in vec4 vertex;
in vec2 textureCoords;
out vec2 oTextureCoords;

void main() {  
  oTextureCoords = textureCoords;
  gl_Position = projection * model * vertex;
}