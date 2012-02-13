attribute vec4 vertex;

uniform mat4 view, model, projection;

attribute vec3 normal;
uniform mat3 normalMatrix;
varying vec3 varyingNormal;

uniform int numLights;
uniform vec3 lightPositions[6];
varying vec3 varyingLightDirections[6];


void main() {  
  gl_Position = projection * view * model * vertex;
  
  vec4 position4 = model * vertex;
  vec3 position = position4.xyz / position4.w;
  varyingNormal = normalMatrix * normal;
  
  for (int i = 0; i < numLights; i++) {
    varyingLightDirections[i] = normalize(lightPositions[i] - position);
  }
}