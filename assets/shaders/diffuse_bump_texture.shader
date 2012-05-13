{
  "vertex" : "glsl/vmvpt.vsh",
  "fragment" : "glsl/diffuse_bump_texture.fsh",
  "attributes" : {
    "vertex" : 1,
    "textureCoords" : 3
  },
  "uniforms" : [
    "model",
    "view",
    "projection",
    "normalMatrix",

    "ambient",    
    "diffuse",
    
    "colorMap",
    "bumpMap",
    "numPointLights"
  ]
}