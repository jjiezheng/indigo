attribute vec4 vertex;
attribute vec3 normal;
attribute vec2 textureCoords;

uniform mat3 normalMatrix;
uniform mat4 projection, modelview, shadow;

uniform vec3 lightPosition[5];
uniform int lightCount;

varying vec3 varyingLightDir[5];
varying vec3 varyingNormal;
varying vec2 varyingTextureCxoords;
varying vec4 varyingShadow;

void main() {  
  varyingShadow = shadow * projection * modelview * vertex;
  varyingTextureCoords = textureCoords;
  varyingNormal = normalMatrix * normal;

  vec4 position4 = modelview * vertex;
  vec3 position = position4.xyz / position4.w;
  
  for (int i = 0; i < lightCount; i++) {
    varyingLightDir[i] = normalize(lightPosition[i] - position);
  }
  
  gl_Position = projection * modelview * vertex;
}
