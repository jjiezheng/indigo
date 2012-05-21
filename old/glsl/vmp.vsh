#version 150 core

uniform mat4 model, projection;

in vec4 vertex;

void main() {  
  gl_Position = projection * model * vertex;
}