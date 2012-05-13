{
  "vertex" : "glsl/vmvptsf.vsh",
  "fragment" : "glsl/diffuse_bump_texture_shadow_fog.fsh",
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
    "numPointLights",
    
    "fogStart",
    "fogEnd",
    "fogColor",
    "fogType",
    "fogFactor"
  ]
}