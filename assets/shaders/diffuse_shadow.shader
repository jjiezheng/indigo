{
  "vertex" : "glsl/vmvpcs.vsh",
  "fragment" : "glsl/diffuse_shadow.fsh",
  "attributes" : {
    "vertex" : 1,
    "normal" : 2
  },
  "uniforms" : [
    "model",
    "view",
    "projection",
    "normalMatrix",
    
    "lightMatrix",
    "shadowMap",
    "lightPositions",
    
    "diffuse",
    "ambient",
    "numPointLights"
  ]
}