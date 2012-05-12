#version 150 core

in vec4 vertex;
in vec2 textureCoords;

out vec2 oTextureCoords;

void main() {  
  oTextureCoords = textureCoords;
  gl_Position = vertex;
}