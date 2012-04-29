{
  "vertex" : "vmvpcs.vsh",
  "fragment" : "diffuse_shadow.fsh",
  "attributes" : {
    "vertex" : 1,
    "normal" : 2
  },
  "uniforms" : [
    "model",
    "view",
    "projection",
    "normalMatrix",
    
    "diffuse",
    "ambient",
    "specular",
    "numPointLights",
    "lightMatrix"
  ]
}