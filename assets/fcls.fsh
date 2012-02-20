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
  
  { // directional lights
    // diffuse
    float diffuseStrength = 0.0;
    for (int i = 0; i < numDirectionalLights; i++) {
      diffuseStrength += max(0.0, dot(normalize(-oNormal), normalize(lightDirections[i])));
    }

    float directionalIntensity = 0.5;
    fragColor.rgb += diffuse * diffuseStrength * directionalIntensity;
  }
  
  { // point lights
    // mix in diffuse
    float diffuseStrength = 0.0;
    for (int i = 0; i < numPointLights; i++) {
      vec3 lightDirection = lightPositions[i] - oPosition;
      diffuseStrength += max(0.0, dot(normalize(oNormal), normalize(lightDirection)));
    }
    fragColor.rgb += diffuse * diffuseStrength;    

    // mix in specular
    for (int i = 0; i < numPointLights; i++) {
      vec3 lightDirection = lightPositions[i] - oPosition;
      vec3 reflection = normalize(reflect(-normalize(lightDirection), 
                                          normalize(oNormal)));
      float spec = max(0.0, dot(normalize(oNormal), reflection));
   
      if (diffuseStrength != 0.0) {
        float fSpec = pow(spec, 128.0);
        fragColor.rgb += vec3(spec, spec, spec); 
      }
    }
  }

  // add ambient
  fragColor.rgb += ambient;

 // multiply by shadow 
 // if (shadowMapCoord.w > 0.0f) {
   float shadowedness = textureProj(shadowMapTexture, shadowMapCoord);
   fragColor = vec4(vec3(1,1,1)*shadowedness, 1);
 // }
}
