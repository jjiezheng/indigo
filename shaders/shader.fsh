uniform vec4 ambientColor, diffuseColor, specularColor;
varying vec3 varyingNormal, varyingLightDir[5];
uniform mat3 normalMatrix;
uniform vec3 lightPosition[5];
uniform int lightCount;
varying vec2 varyingTextureCoords;
uniform sampler2D colorMap;

void main() {
  float diffuse = 0.0;
  for (int i = 0; i < lightCount; i++) {
    diffuse += max(0.0, dot(normalize(varyingNormal),
                            normalize(varyingLightDir[i])));      
  }
  
  gl_FragColor = diffuseColor * diffuse;
  
  gl_FragColor += ambientColor;
  
//  gl_FragColor *= texture2D(colorMap, varyingTextureCoords.st);
  vec3 eyeNormal = normalMatrix * varyingNormal;
  
  for (int i = 0; i < lightCount; i++) {
    vec3 reflection = normalize(reflect(-varyingLightDir[i], eyeNormal));
    float spec = max(0.0, dot(eyeNormal, reflection));
    
    if (diffuse != 0) {
      float fSpec = pow(spec, 128.0);
      gl_FragColor.rgb += (vec3(fSpec, fSpec, fSpec)); 
    }
  }
}
