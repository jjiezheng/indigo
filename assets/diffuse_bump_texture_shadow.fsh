#version 150

out vec4 fragColor;

uniform vec3 ambient, diffuse;

uniform int numPointLights;
uniform vec3 lightPositions[6];

in vec3 oNormal;
in vec3 oPosition;
in vec2 oTextureCoords;
in vec4 oShadowMapCoords;

uniform sampler2D colorMap;
uniform sampler2D bumpMap;
uniform sampler2DShadow shadowMap;

void main() {   
  // ambient
  fragColor.rgb = ambient;
  
  vec3 bumpNormal = vec3(texture(bumpMap, oTextureCoords));
  bumpNormal = (bumpNormal -0.5) * 2.0;
  
  vec4 texture = texture(colorMap, oTextureCoords);
  
  // diffuse
  float diffuseStrength = 0.0;
  for (int i = 0; i < numPointLights; i++) {
    vec3 lightDirection = lightPositions[i] - oPosition;
    diffuseStrength += max(0.0, dot(normalize(bumpNormal), normalize(lightDirection)));
  }
  fragColor.rgb += texture.rgb * diffuseStrength;
  
  vec4 shadowCoord = oShadowMapCoords;
  shadowCoord.z += 0.0005;
  
  if (shadowCoord.w > 0.0f) {
    float depth = textureProj(shadowMap, shadowCoord);
    float visibility = (depth == 0) ? 0.5 : 1.0;
    fragColor.rgb = fragColor.rgb * visibility;
  }
}