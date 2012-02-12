uniform mat4 projection, model, view;
attribute vec4 vertex;
varying float distance;

void main() {  
  gl_Position = projection * view * model * vertex;
  distance = gl_Position.z;
}