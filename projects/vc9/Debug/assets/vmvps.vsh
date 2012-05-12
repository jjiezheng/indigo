#version 150

uniform mat4 model, view, projection, lightMatrix;
in vec4 vertex;
out vec4 shadowMapCoord;

void main() {  
  shadowMapCoord = lightMatrix * vertex;
  gl_Position = projection * view * model * vertex;
}