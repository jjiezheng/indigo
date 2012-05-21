#version 150 core

uniform mat4 projection, view, model;

in vec4 vertex;
out vec3 oTextureCoords;
out vec3 oViewPosition;

void main() {  
  gl_Position = projection * view * model * vertex;
  
  vec4 mvPosition = view * model * vertex;
  oViewPosition = mvPosition.xyz / mvPosition.w;
  
  oTextureCoords = normalize(vertex.xyz);
}