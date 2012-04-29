#version 150

out vec4 fragColor;

uniform vec3 ambient, diffuse;

uniform int numPointLights;
uniform vec3 lightPositions[6];

in vec3 oNormal;
in vec3 oPosition;

uniform sampler2DShadow shadowMapTexture;
in vec4 shadowMapCoord;

void main() {   
  // ambient
  fragColor.rgb = ambient;
  
  // diffuse
  float diffuseStrength = 0.0;
  for (int i = 0; i < numPointLights; i++) {
    vec3 lightDirection = lightPositions[i] - oPosition;
    diffuseStrength += max(0.0, dot(normalize(oNormal), normalize(lightDirection)));
  }
  fragColor.rgb += diffuse * diffuseStrength;
  
  // shadow
  vec4 shadowCoord = shadowMapCoord;
  shadowCoord.z += 0.0005;
  
  if (shadowCoord.w > 0.0f) {
    float depth = textureProj(shadowMapTexture, shadowCoord);
    float visibility = (depth == 0) ? 0.5 : 1.0;
    fragColor.rgb = fragColor.rgb * visibility;
  }
}
