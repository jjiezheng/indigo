#version 150 core

uniform mat4 projection, view, model, lightMatrix;

in vec4 vertex;
in vec2 textureCoords;

out vec3 oNormal, oPosition;
out vec2 oTextureCoords;
out vec4 oShadowMapCoords;

void main() {  
  gl_Position = projection * view * model * vertex;
  
  vec4 position4 = model * vertex;
  oPosition = position4.xyz / position4.w;
    
  oTextureCoords = textureCoords;
  oShadowMapCoords = lightMatrix * model * vertex;
}