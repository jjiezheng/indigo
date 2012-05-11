#version 150 core

in vec4 vertex;
uniform mat4 model;

void main() {  
  gl_Position = model * vertex;
}