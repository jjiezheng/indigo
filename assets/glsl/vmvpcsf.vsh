#version 150

in vec4 vertex;
in vec3 normal;

uniform mat4 view, model, projection;
uniform mat3 normalMatrix;

out vec3 oNormal, oPosition, oViewPosition;

uniform mat4 lightMatrix;
out vec4 shadowMapCoord;

void main() {  
  gl_Position = projection * view * model * vertex;
    
  vec4 mPosition = model * vertex;
  oPosition = mPosition.xyz / mPosition.w;
  oNormal = normalize(normalMatrix * normal);
  
  shadowMapCoord = lightMatrix * model * vertex;
  
  vec4 mvPosition = view * model * vertex;
  oViewPosition = mvPosition.xyz / mvPosition.w;
}