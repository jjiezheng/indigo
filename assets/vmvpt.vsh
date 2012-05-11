#version 150 core

uniform mat4 projection, view, model;

in vec4 vertex;
in vec2 textureCoords;

out vec2 oTextureCoords;
out vec3 oPosition;

void main() {  
  gl_Position = projection * view * model * vertex;
  
  vec4 position4 = model * vertex;
  oPosition = position4.xyz / position4.w;
  
  oTextureCoords = textureCoords;
}