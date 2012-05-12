#version 150 core

uniform mat4 projection, view, model;

in vec4 vertex;

out vec3 oTextureCoords;

void main() {  
  gl_Position = projection * view * model * vertex;
  oTextureCoords = normalize(vertex.xyz);
}