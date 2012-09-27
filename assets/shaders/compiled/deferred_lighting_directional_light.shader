{
"dx11" : {
"vertex" : "
// vs_4_0 output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile vs_5_0
// source file: deferred_lighting_directional_light.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile vs_5_0
//program vs
//semantic NormalMap
//semantic DepthMap
//semantic NormalMatrix
//semantic LightDirection
//semantic LightColor
//var float4 position : $vin.POSITION : POSITION : 0 : 1
//var float2 texCoord : $vin.TEXCOORD0 : TEXCOORD0 : 1 : 1
//var float4 vs.position : $vout.POSITION :  : -1 : 1
//var float2 vs.texCoord : $vout.TEXCOORD0 :  : -1 : 1

#pragma pack_matrix(row_major)

struct VOutput {
    float4 _position1 : POSITION;
    float2 _texCoord1 : TEXCOORD0;
};

struct X1X {
    float4 _POSITION : SV_Position;
    float2 _TEXCOORD0 : TEXCOORD0;
};

static X1X cout;

 // main procedure, the original name was vs
X1X main(in float4 _position : POSITION, in float2 _texCoord : TEXCOORD0)
{

    VOutput _OUT;

    _OUT._position1 = _position;
    _OUT._texCoord1 = _texCoord;
    cout._POSITION = _OUT._position1;
    cout._TEXCOORD0 = _OUT._texCoord1;
    return cout;
} // main end
",
"fragment" : "
// ps_4_0 output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile ps_5_0
// source file: deferred_lighting_directional_light.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile ps_5_0
//program ps
//semantic NormalMap
//semantic DepthMap
//semantic NormalMatrix
//semantic LightDirection
//semantic LightColor
//var sampler2D NormalMap :  : _NormalMap : -1 : 1
//var sampler2D DepthMap :  : _DepthMap : -1 : 1
//var float4 LightDirection :  : _LightDirection : -1 : 1
//var float3 LightColor :  : _LightColor : -1 : 1
//var float2 texCoord : $vin.TEXCOORD0 :  : 1 : 1
//var float4 ps : $vout.COLOR0 : COLOR0 : -1 : 1

#pragma pack_matrix(row_major)

struct VOutput {
    float4 _position1 : SV_Position;
    float2 _texCoord1 : TEXCOORD0;
};

struct X1X {
    float4 _POSITION : SV_Position;
    float2 _TEXCOORD0 : TEXCOORD0;
};

static float _TMP3;
static float3 _TMP2;
static float3 _TMP1;
static float _TMP5;
static float _TMP4;
static float4 _TMP0;
Texture2D<float4> _TMP13;
Texture2D<float4> _TMP14;
SamplerState _NormalMap;
SamplerState _DepthMap;
uniform float4 _LightDirection;
uniform float3 _LightColor;

 // main procedure, the original name was ps
float4 main( in X1X cin) : SV_Target0
{

    float2 _texCoord;
    float4 _normalData;
    float3 _normal;
    float3 _lightVector;
    float _diffuseStrength;
    float3 _diffuseContribution;

    _texCoord = cin._TEXCOORD0;
    _TMP0 = _TMP13.Sample(_DepthMap, _texCoord);
    if (_TMP0.x ==   1.00000000000000000E00f) { // if begin
        return float4(   0.00000000000000000E00f,   0.00000000000000000E00f,   0.00000000000000000E00f,   0.00000000000000000E00f);
    } // end if
    _normalData = _TMP14.Sample(_NormalMap, _texCoord);
    _TMP4 = dot(_normalData.xyz, _normalData.xyz);
    _TMP5 = rsqrt(_TMP4);
    _normal = _TMP5*_normalData.xyz;
    _lightVector = -_LightDirection.xyz;
    _TMP4 = dot(_normal, _normal);
    _TMP5 = rsqrt(_TMP4);
    _TMP1 = _TMP5*_normal;
    _TMP4 = dot(_lightVector, _lightVector);
    _TMP5 = rsqrt(_TMP4);
    _TMP2 = _TMP5*_lightVector;
    _TMP3 = dot(_TMP1, _TMP2);
    _diffuseStrength = max(  0.00000000000000000E00f, _TMP3);
    _diffuseContribution = _LightColor*_diffuseStrength;
    return float4(_diffuseContribution.x, _diffuseContribution.y, _diffuseContribution.z,   0.00000000000000000E00f);
} // main end
"
}
,
"gl21" : {
"vertex" : "
// glslv output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile glslv
// source file: deferred_lighting_directional_light.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile glslv
//program vs
//semantic NormalMap
//semantic DepthMap
//semantic NormalMatrix
//semantic LightDirection
//semantic LightColor
//var float4 position : $vin.POSITION : ATTR0 : 0 : 1
//var float2 texCoord : $vin.TEXCOORD0 : ATTR8 : 1 : 1
//var float4 vs.position : $vout.POSITION : HPOS : -1 : 1
//var float2 vs.texCoord : $vout.TEXCOORD0 : TEX0 : -1 : 1

#version 110

struct VOutput {
    vec4 _position2;
    vec2 _texCoord2;
};


 // main procedure, the original name was vs
void main()
{


    gl_TexCoord[0].xy = gl_MultiTexCoord0.xy;
    gl_Position = gl_Vertex;
    return;
} // main end
",
"fragment" : "
// glslf output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile glslf
// source file: deferred_lighting_directional_light.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile glslf
//program ps
//semantic NormalMap
//semantic DepthMap
//semantic NormalMatrix
//semantic LightDirection
//semantic LightColor
//var sampler2D NormalMap :  : _NormalMap : -1 : 1
//var sampler2D DepthMap :  : _DepthMap : -1 : 1
//var float4 LightDirection :  : _LightDirection : -1 : 1
//var float3 LightColor :  : _LightColor : -1 : 1
//var float2 texCoord : $vin.TEXCOORD0 : TEX0 : 1 : 1
//var float4 ps : $vout.COLOR0 : COL : -1 : 1

#version 110

struct VOutput {
    vec2 _texCoord2;
};

vec4 _ret_0;
float _TMP3;
vec3 _TMP2;
vec3 _TMP1;
float _TMP5;
float _TMP4;
vec4 _TMP0;
uniform sampler2D _NormalMap;
uniform sampler2D _DepthMap;
uniform vec4 _LightDirection;
uniform vec3 _LightColor;

 // main procedure, the original name was ps
void main()
{

    vec4 _normalData;
    vec3 _normal;
    vec3 _lightVector;
    float _diffuseStrength;
    vec3 _diffuseContribution;

    _TMP0 = texture2D(_DepthMap, gl_TexCoord[0].xy);
    if (_TMP0.x == 1.00000000E+00) { // if begin
        gl_FragColor = vec4( 0.00000000E+00, 0.00000000E+00, 0.00000000E+00, 0.00000000E+00);
        return;
    } // end if
    _normalData = texture2D(_NormalMap, gl_TexCoord[0].xy);
    _TMP4 = dot(_normalData.xyz, _normalData.xyz);
    _TMP5 = inversesqrt(_TMP4);
    _normal = _TMP5*_normalData.xyz;
    _lightVector = -_LightDirection.xyz;
    _TMP4 = dot(_normal, _normal);
    _TMP5 = inversesqrt(_TMP4);
    _TMP1 = _TMP5*_normal;
    _TMP4 = dot(_lightVector, _lightVector);
    _TMP5 = inversesqrt(_TMP4);
    _TMP2 = _TMP5*_lightVector;
    _TMP3 = dot(_TMP1, _TMP2);
    _diffuseStrength = max(0.00000000E+00, _TMP3);
    _diffuseContribution = _LightColor*_diffuseStrength;
    _ret_0 = vec4(_diffuseContribution.x, _diffuseContribution.y, _diffuseContribution.z, 0.00000000E+00);
    gl_FragColor = _ret_0;
    return;
} // main end
"
}
}
