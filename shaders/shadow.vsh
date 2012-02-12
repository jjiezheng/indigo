attribute vec4 vertex;
attribute vec3 normal;

uniform vec3 lightPosition;
uniform mat4 projection, model, lightView, view, bias;
uniform mat3 normalMatrix;

varying vec3 varyingNormal, varyingLightDir;
varying vec4 varyingShadow;

void main() {
  vec4 position4 = view * model * vertex;
  vec3 position = position4.xyz / position4.w;
  
  varyingLightDir = lightPosition - position;
  varyingNormal = normalMatrix * normal;
  
  varyingShadow = bias * projection * lightView * model * vertex;
  
  gl_Position = projection * view * model * vertex;
}
