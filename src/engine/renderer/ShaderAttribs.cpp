#include "ShaderAttribs.h"

int ATTRIB_VERTEX = 0;
int ATTRIB_NORMAL = 2;
int ATTRIB_UV = 8;

enum GenericVertexInputIndices {
    POSITION        = 0,
    BLENDWEIGHT     = 1,
    NORMAL          = 2,
    DIFFUSE         = 3,    COLOR0      = 3,
    SPECULAR        = 4,    COLOR1      = 4,
    TESSFACTOR      = 5,    FOGCOORD    = 5,
    PSIZE           = 6,
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