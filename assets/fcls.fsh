#version 150

uniform vec3 ambient, diffuse, specular;
uniform int numLights;
uniform vec3 lightPositions[6];

uniform sampler2DShadow shadowMapTexture;
in vec4 shadowMapCoord;

in vec3 oNormal;
in vec3 oPosition;

out vec4 fragColor;

void main() {   
  
  // //calculate diffuse
  float diffuseStrength = 0.0;
  for (int i = 0; i < numLights; i++) {
    vec3 lightDirection = lightPositions[i] - oPosition;
    diffuseStrength += max(0.0, dot(normalize(oNormal), normalize(lightDirection)));
  }
  fragColor.rgb = diffuse * diffuseStrength;
 
 // add ambient
 fragColor.rgb += ambient;
 
 // mix in specular
 for (int i = 0; i < numLights; i++) {
   vec3 lightDirection = lightPositions[i] - oPosition;
   vec3 reflection = normalize(reflect(-normalize(lightDirection), 
                                        normalize(oNormal)));
   float spec = max(0.0, dot(normalize(oNormal), reflection));
   
   if (diffuseStrength != 0.0) {
     float fSpec = pow(spec, 128.0);
     fragColor.rgb += vec3(spec, spec, spec); 
   }
 }
 
 float shadowedness = textureProj(shadowMapTexture, shadowMapCoord);
 fragColor.rgb *= shadowedness;
}
