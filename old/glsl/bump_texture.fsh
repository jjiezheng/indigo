#version 150

out vec4 fragColor;

uniform vec3 ambient, diffuse;

uniform int numPointLights;
uniform vec3 lightPositions[6];

in vec3 oNormal;
in vec3 oPosition;
in vec2 oTextureCoords;

uniform sampler2D bumpMap;

void main() {   
  // ambient
  fragColor.rgb = ambient;
  
  vec3 bumpNormal = vec3(texture(bumpMap, oTextureCoords));
  bumpNormal = (bumpNormal -0.5) * 2.0;
  
  // diffuse
  float diffuseStrength = 0.0;
  for (int i = 0; i < numPointLights; i++) {
    vec3 lightDirection = lightPositions[i] - oPosition;
    diffuseStrength += max(0.0, dot(normalize(bumpNormal), normalize(lightDirection)));
  }
  fragColor.rgb += diffuse * diffuseStrength;
}