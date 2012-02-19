#version 150 core

uniform mat4 projection, view, model;

in vec4 vertex;
in vec2 textureCoords;

out vec2 oTextureCoords;

void main() {  
  oTextureCoords = textureCoords;
  gl_Position = projection * view * model * vertex;
}