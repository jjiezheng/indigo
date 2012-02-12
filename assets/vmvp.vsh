attribute vec4 vertex;
uniform mat4 model, view, projection;

void main() {  
  gl_Position = projection * view * model * vertex;
}