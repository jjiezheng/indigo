#version 150

uniform mat4 projection;

in vec4 vertex;

void main() {  
  gl_Position = projection * vertex;
}