uniform vec4 ambientColor, diffuseColor, specularColor;
varying vec3 varyingNormal, varyingLightDir;

varying vec4 varyingShadow;
uniform sampler2D shadowMap;

void main() {
  
  gl_FragColor = vec4(1);
  
  // shadow map
  vec4 shadowW = varyingShadow / varyingShadow.w;  
  float distanceFromLight = texture2D(shadowMap, shadowW.xy).z;
  float shadow = distanceFromLight < shadowW.z ? 0.5 : 1.0;
  
  gl_FragColor *= shadow;
  
  // diffuse lighting
  float diffuse = max(0.0, dot(normalize(varyingNormal),
                               normalize(varyingLightDir)));
  
  gl_FragColor *= diffuse * diffuseColor;  
  
  // ambient lighting
  gl_FragColor += ambientColor;
  
  //specular lighting
  vec3 lightDirection = varyingLightDir;
  vec3 reflection = normalize(reflect(-normalize(lightDirection), normalize(varyingNormal)));
  float spec = max(0.0, dot(normalize(varyingNormal), reflection));
  float fSpec = pow(spec, 128.0);
  gl_FragColor.rgb += vec3(fSpec, fSpec, fSpec); 
}


