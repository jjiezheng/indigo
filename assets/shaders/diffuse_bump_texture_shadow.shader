{
  "vertex" : "glsl/vmvpts.vsh",
  "fragment" : "glsl/diffuse_bump_texture_shadow.fsh",
  "attributes" : {
    "vertex" : 1,
    "textureCoords" : 3
  },
  "uniforms" : [
    "model",
    "view",
    "projection",
    "normalMatrix",
    
    "lightMatrix",
    "shadowMap",
    "lightPositions",

    "ambient",    
    "diffuse",    
    "colorMap",
    "bumpMap",
    "numPointLights"
  ]
}