#ifndef SHADER_SEMANTICS_H
#define SHADER_SEMANTICS_H

enum ShaderSemantics {
  POSITION        = 0,
  BLENDWEIGHT     = 1,
  NORMAL          = 2,
  DIFFUSE         = 3,    COLOR0      = 3,
  SPECULAR        = 4,    COLOR1      = 4,
  TESSFACTOR      = 5,    FOGCOORD    = 5,
  OPSIZE           = 6,
  BLENDINDICES    = 7,
  TEXCOORD0       = 8,
  TEXCOORD1       = 9,
  TEXCOORD2       = 10,
  TEXCOORD3       = 11,
  TEXCOORD4       = 12,
  TEXCOORD5       = 13,
  TEXCOORD6       = 14,   TANGENT     = 14,
  TEXCOORD7       = 15,   BINORMAL    = 15,
};


#endif
