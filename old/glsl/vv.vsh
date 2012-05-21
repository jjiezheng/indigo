#version 150 core

in vec4 vertex;
uniform mat4 view;

void main() {  
  gl_Position = view * vertex;
}