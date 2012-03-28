#version 150

uniform vec3 ambient, diffuse, specular;

uniform int numDirectionalLights;
uniform vec3 lightDirections[6];

uniform int numPointLights;
uniform vec3 lightPositions[6];

uniform sampler2DShadow shadowMapTexture;
in vec4 shadowMapCoord;

in vec3 oNormal;
in vec3 oPosition;

out vec4 fragColor;

void main() {
  fragColor = vec4(vec3(0), 1);
  
  for (int i = 0; i < numDirectionalLights; i++) {
    float diffuseStrength = max(0.0, dot(-oNormal, normalize(lightDirections[i])));
    fragColor.rgb += diffuse * diffuseStrength;
  }
  
  for (int i = 0; i < numPointLights; i++) {
    vec3 lightDirection = lightPositions[i] - oPosition;
    float diffuseStrength = max(0.0, dot(normalize(oNormal), normalize(lightDirection)));
    fragColor.rgb += diffuse * diffuseStrength; 
  } 
  
  vec4 shadowCoord = shadowMapCoord;
  shadowCoord.z += 0.0005;
  
  if (shadowCoord.w > 0.0f) {
    float depth = textureProj(shadowMapTexture, shadowCoord);
    float visibility = (depth == 0) ? 0.5 : 1.0;
    fragColor.rgb = fragColor.rgb * visibility;
  }
}
