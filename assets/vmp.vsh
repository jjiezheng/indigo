attribute vec4 vertex;
uniform mat4 model, projection;

void main() {  
  gl_Position = projection * model * vertex;
}