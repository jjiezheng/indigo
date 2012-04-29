#version 150

in vec4 vertex;
in vec3 normal;

uniform mat4 view, model, projection;
uniform mat3 normalMatrix;

out vec3 oNormal, oPosition;

uniform mat4 lightMatrix;
out vec4 shadowMapCoord;

void main() {  
  gl_Position = projection * view * model * vertex;
    
  vec4 position4 = model * vertex;
  oPosition = position4.xyz / position4.w;
  oNormal = normalize(normalMatrix * normal);
  
  shadowMapCoord = lightMatrix * model * vertex;
}