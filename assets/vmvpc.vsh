attribute vec4 vertex;

uniform mat4 view, model, projection;

attribute vec3 normal;
uniform mat3 normalMatrix;
varying vec3 varyingNormal;

varying vec3 varyingPosition;


void main() {  
  gl_Position = projection * view * model * vertex;
  
  vec4 position4 = model * vertex;
  varyingPosition = position4.xyz / position4.w;
  varyingNormal = normalMatrix * normal;
}