varying vec3 varyingNormal;

uniform vec3 ambient, diffuse, specular;
uniform int numLights;
varying vec3 varyingLightDirections[6];

void main() {   
  // add ambient
  gl_FragColor.rgb = ambient;

  //calculate diffuse
  float diffuseStrength = 0.0;
  for (int i = 0; i < numLights; i++) {
    diffuseStrength += max(0.0, dot(varyingNormal, varyingLightDirections[i]));
  }
  gl_FragColor.rgb += diffuse * diffuseStrength;
  
  // mix in specular
  for (int i = 0; i < numLights; i++) {
    vec3 reflection = normalize(reflect(-normalize(varyingLightDirections[i]), 
                                         normalize(varyingNormal)));
    float spec = max(0.0, dot(normalize(varyingNormal), reflection));
    
    if (diffuseStrength != 0.0) {
      float fSpec = pow(spec, 128.0);
      gl_FragColor.rgb += vec3(spec, spec, spec); 
    }
  }
}
