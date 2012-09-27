{
"dx11" : {
"vertex" : "
// vs_4_0 output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile vs_5_0
// source file: deferred_render_color_normal_depth.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile vs_5_0
//program vs
//semantic NormalMatrix
//semantic WorldViewProj
//semantic WorldView
//semantic World
//semantic DiffuseColor
//semantic AmbientColor
//semantic DiffusePower
//semantic SpecularPower
//semantic SpecularIntensity
//semantic Far
//semantic Near
//var float3x3 NormalMatrix :  : _NormalMatrix[0], 3 : -1 : 1
//var float4x4 WorldViewProj :  : _WorldViewProj[0], 4 : -1 : 1
//var float4x4 WorldView :  : _WorldView[0], 4 : -1 : 1
//var float4 position : $vin.POSITION : POSITION : 0 : 1
//var float4 normal : $vin.NORMAL : NORMAL : 1 : 1
//var float4 vs.position : $vout.POSITION :  : -1 : 1
//var float3 vs.normal : $vout.TEXCOORD0 :  : -1 : 1
//var float3 vs.depth : $vout.TEXCOORD1 :  : -1 : 1

#pragma pack_matrix(row_major)

struct VOutput {
    float4 _position1 : POSITION;
    float3 _normal1 : TEXCOORD0;
    float3 _depth : TEXCOORD1;
};

struct POutput {
    float4 _color : COLOR0;
    float4 _normal2 : COLOR1;
    float4 _depth1 : COLOR2;
};

struct X1X {
    float4 _POSITION : SV_Position;
    float3 _TEXCOORD0 : TEXCOORD0;
    float3 _TEXCOORD1 : TEXCOORD1;
};

static float _TMP2;
static float _TMP1;
static float4 _r0004;
static float3 _r0006;
static float4 _r0010;
static X1X cout;
uniform float3x3 _NormalMatrix;
uniform float4x4 _WorldViewProj;
uniform float4x4 _WorldView;

 // main procedure, the original name was vs
X1X main(in float4 _position : POSITION, in float4 _normal : NORMAL0)
{

    VOutput _OUT;

    _r0004.x = dot(_WorldViewProj._11_12_13_14, _position);
    _r0004.y = dot(_WorldViewProj._21_22_23_24, _position);
    _r0004.z = dot(_WorldViewProj._31_32_33_34, _position);
    _r0004.w = dot(_WorldViewProj._41_42_43_44, _position);
    _OUT._position1 = _r0004;
    _r0006.x = dot(_NormalMatrix._11_12_13, _normal.xyz);
    _r0006.y = dot(_NormalMatrix._21_22_23, _normal.xyz);
    _r0006.z = dot(_NormalMatrix._31_32_33, _normal.xyz);
    _TMP1 = dot(_r0006, _r0006);
    _TMP2 = rsqrt(_TMP1);
    _OUT._normal1 = _TMP2*_r0006;
    _OUT._depth.x = _r0004.z;
    _OUT._depth.y = _r0004.w;
    _r0010.z = dot(_WorldView._31_32_33_34, _position);
    _OUT._depth.z = _r0010.z;
    cout._POSITION = _OUT._position1;
    cout._TEXCOORD0 = _OUT._normal1;
    cout._TEXCOORD1 = _OUT._depth;
    return cout;
} // main end
",
"fragment" : "
// ps_4_0 output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile ps_5_0
// source file: deferred_render_color_normal_depth.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile ps_5_0
//program ps
//semantic NormalMatrix
//semantic WorldViewProj
//semantic WorldView
//semantic World
//semantic DiffuseColor
//semantic AmbientColor
//semantic DiffusePower
//semantic SpecularPower
//semantic SpecularIntensity
//semantic Far
//semantic Near
//var float3 DiffuseColor :  : _DiffuseColor : -1 : 1
//var float DiffusePower :  : _DiffusePower : -1 : 1
//var float SpecularPower :  : _SpecularPower : -1 : 1
//var float SpecularIntensity :  : _SpecularIntensity : -1 : 1
//var float Far :  : _Far : -1 : 1
//var float Near :  : _Near : -1 : 1
//var float3 normal : $vin.TEXCOORD0 :  : 1 : 1
//var float3 depth : $vin.TEXCOORD1 :  : 2 : 1
//var float4 ps.color : $vout.COLOR0 : COLOR0 : -1 : 1
//var float4 ps.normal : $vout.COLOR1 : COLOR1 : -1 : 1
//var float4 ps.depth : $vout.COLOR2 : COLOR2 : -1 : 1

#pragma pack_matrix(row_major)

struct VOutput {
    float4 _position1 : SV_Position;
    float3 _normal2 : TEXCOORD0;
    float3 _depth2 : TEXCOORD1;
};

struct POutput {
    float4 _color : SV_Target0;
    float4 _normal : SV_Target1;
    float4 _depth : SV_Target2;
};

struct X1X {
    float4 _POSITION : SV_Position;
    float3 _TEXCOORD0 : TEXCOORD0;
    float3 _TEXCOORD1 : TEXCOORD1;
};

uniform float3 _DiffuseColor;
uniform float _DiffusePower;
uniform float _SpecularPower;
uniform float _SpecularIntensity;
uniform float _Far;
uniform float _Near;

 // main procedure, the original name was ps
POutput main( in X1X cin)
{

    float3 _normal1;
    float3 _depth1;
    POutput _OUT;
    float _depthNDC;
    float _depthLinear;

    _normal1 = cin._TEXCOORD0;
    _depth1 = cin._TEXCOORD1;
    _OUT._color = float4(_DiffuseColor.x, _DiffuseColor.y, _DiffuseColor.z,   1.00000000000000000E00f);
    _OUT._normal = float4(_normal1.x, _normal1.y, _normal1.z, _DiffusePower);
    _depthNDC = _depth1.x/_depth1.y;
    _depthLinear = (-_depth1.z - _Near)/(_Far - _Near);
    _OUT._depth = float4(_depthNDC, _depthLinear, _SpecularPower, _SpecularIntensity);
    return _OUT;
} // main end
"
}
,
"gl21" : {
"vertex" : "
// glslv output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile glslv
// source file: deferred_render_color_normal_depth.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile glslv
//program vs
//semantic NormalMatrix
//semantic WorldViewProj
//semantic WorldView
//semantic World
//semantic DiffuseColor
//semantic AmbientColor
//semantic DiffusePower
//semantic SpecularPower
//semantic SpecularIntensity
//semantic Far
//semantic Near
//var float3x3 NormalMatrix :  : _NormalMatrix[0], 3 : -1 : 1
//var float4x4 WorldViewProj :  : _WorldViewProj[0], 4 : -1 : 1
//var float4x4 WorldView :  : _WorldView[0], 4 : -1 : 1
//var float4 position : $vin.POSITION : ATTR0 : 0 : 1
//var float4 normal : $vin.NORMAL : ATTR2 : 1 : 1
//var float4 vs.position : $vout.POSITION : HPOS : -1 : 1
//var float3 vs.normal : $vout.TEXCOORD0 : TEX0 : -1 : 1
//var float3 vs.depth : $vout.TEXCOORD1 : TEX1 : -1 : 1

#version 110

struct VOutput {
    vec4 _position2;
    vec3 _normal2;
    vec3 _depth;
};

struct POutput {
    vec4 _color;
    vec4 _normal3;
    vec4 _depth1;
};

float _TMP2;
float _TMP1;
vec4 _r0015;
vec3 _r0025;
vec4 _r0039;
uniform vec3 _NormalMatrix[3];
uniform vec4 _WorldViewProj[4];
uniform vec4 _WorldView[4];

 // main procedure, the original name was vs
void main()
{

    VOutput _OUT;

    _r0015.x = dot(_WorldViewProj[0], gl_Vertex);
    _r0015.y = dot(_WorldViewProj[1], gl_Vertex);
    _r0015.z = dot(_WorldViewProj[2], gl_Vertex);
    _r0015.w = dot(_WorldViewProj[3], gl_Vertex);
    _r0025.x = dot(_NormalMatrix[0], gl_Normal);
    _r0025.y = dot(_NormalMatrix[1], gl_Normal);
    _r0025.z = dot(_NormalMatrix[2], gl_Normal);
    _TMP1 = dot(_r0025, _r0025);
    _TMP2 = inversesqrt(_TMP1);
    _OUT._normal2 = _TMP2*_r0025;
    _OUT._depth.x = _r0015.z;
    _OUT._depth.y = _r0015.w;
    _r0039.z = dot(_WorldView[2], gl_Vertex);
    _OUT._depth.z = _r0039.z;
    gl_TexCoord[0].xyz = _OUT._normal2;
    gl_TexCoord[1].xyz = _OUT._depth;
    gl_Position = _r0015;
    return;
} // main end
",
"fragment" : "
// glslf output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile glslf
// source file: deferred_render_color_normal_depth.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile glslf
//program ps
//semantic NormalMatrix
//semantic WorldViewProj
//semantic WorldView
//semantic World
//semantic DiffuseColor
//semantic AmbientColor
//semantic DiffusePower
//semantic SpecularPower
//semantic SpecularIntensity
//semantic Far
//semantic Near
//var float3 DiffuseColor :  : _DiffuseColor : -1 : 1
//var float DiffusePower :  : _DiffusePower : -1 : 1
//var float SpecularPower :  : _SpecularPower : -1 : 1
//var float SpecularIntensity :  : _SpecularIntensity : -1 : 1
//var float Far :  : _Far : -1 : 1
//var float Near :  : _Near : -1 : 1
//var float3 normal : $vin.TEXCOORD0 : TEX0 : 1 : 1
//var float3 depth : $vin.TEXCOORD1 : TEX1 : 2 : 1
//var float4 ps.color : $vout.COLOR0 : COL : -1 : 1
//var float4 ps.normal : $vout.COLOR1 : COL1 : -1 : 1
//var float4 ps.depth : $vout.COLOR2 : COL2 : -1 : 1

#version 110

#extension GL_ARB_draw_buffers : enable

struct VOutput {
    vec3 _normal2;
    vec3 _depth2;
};

struct POutput {
    vec4 _color;
    vec4 _normal3;
    vec4 _depth3;
};

uniform vec3 _DiffuseColor;
uniform float _DiffusePower;
uniform float _SpecularPower;
uniform float _SpecularIntensity;
uniform float _Far;
uniform float _Near;

 // main procedure, the original name was ps
void main()
{

    POutput _OUT;
    float _depthNDC;
    float _depthLinear;

    _OUT._color = vec4(_DiffuseColor.x, _DiffuseColor.y, _DiffuseColor.z, 1.00000000E+00);
    _OUT._normal3 = vec4(gl_TexCoord[0].x, gl_TexCoord[0].y, gl_TexCoord[0].z, _DiffusePower);
    _depthNDC = gl_TexCoord[1].x/gl_TexCoord[1].y;
    _depthLinear = (-gl_TexCoord[1].z - _Near)/(_Far - _Near);
    _OUT._depth3 = vec4(_depthNDC, _depthLinear, _SpecularPower, _SpecularIntensity);
    gl_FragData[1] = _OUT._normal3;
    gl_FragData[2] = _OUT._depth3;
    gl_FragData[0] = _OUT._color;
    return;
} // main end
"
}
}
