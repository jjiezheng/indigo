{
  "vertex" : "vmvpcsf.vsh",
  "fragment" : "diffuse_shadow_fog.fsh",
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
    "numPointLights",
    
    "fogStart",
    "fogEnd",
    "fogColor",
    "fogType",
    "fogFactor"
  ]
}