varying vec3 varyingNormal;

uniform vec3 ambient, diffuse, specular;
uniform int numLights;
uniform vec3 lightPositions[6];

varying vec3 varyingPosition;

void main() {   
  
  // //calculate diffuse
  float diffuseStrength = 0.0;
  for (int i = 0; i < numLights; i++) {
    vec3 lightDirection = lightPositions[i] - varyingPosition;
    diffuseStrength += max(0.0, dot(normalize(varyingNormal), normalize(lightDirection)));
  }
  gl_FragColor.rgb = diffuse * diffuseStrength;
 
 // add ambient
 gl_FragColor.rgb += ambient;
 
 // mix in specular
 for (int i = 0; i < numLights; i++) {
   vec3 lightDirection = lightPositions[i] - varyingPosition;
   vec3 reflection = normalize(reflect(-normalize(lightDirection), 
                                        normalize(varyingNormal)));
   float spec = max(0.0, dot(normalize(varyingNormal), reflection));
   
   if (diffuseStrength != 0.0) {
     float fSpec = pow(spec, 128.0);
     gl_FragColor.rgb += vec3(spec, spec, spec); 
   }
 }
}
