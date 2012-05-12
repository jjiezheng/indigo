#version 150

out vec4 fragColor;

uniform vec3 ambient, diffuse;

uniform int numPointLights;
uniform vec3 lightPositions[6];

in vec3 oNormal;
in vec3 oPosition;

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
}
