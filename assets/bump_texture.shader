{
  "vertex" : "vmvpt.vsh",
  "fragment" : "bump_texture.fsh",
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
    
    "bumpMap",
    "numPointLights"
  ]
}