{
"dx11" : {
"vertex" : "
// vs_4_0 output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile vs_5_0
// source file: deferred_fullscreen_texture.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile vs_5_0
//program vs
//semantic texture
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
// source file: deferred_fullscreen_texture.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile ps_5_0
//program ps
//semantic texture
//var sampler2D texture :  : _texture : -1 : 1
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

Texture2D<float4> _TMP0;
uniform SamplerState _texture;

 // main procedure, the original name was ps
float4 main( in X1X cin) : SV_Target0
{

    float2 _texCoord;

    _texCoord = cin._TEXCOORD0;
    return _TMP0.Sample(_texture, _texCoord);
} // main end
"
}
,
"gl21" : {
"vertex" : "
// glslv output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile glslv
// source file: deferred_fullscreen_texture.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile glslv
//program vs
//semantic texture
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
// source file: deferred_fullscreen_texture.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile glslf
//program ps
//semantic texture
//var sampler2D texture :  : _texture : -1 : 1
//var float2 texCoord : $vin.TEXCOORD0 : TEX0 : 1 : 1
//var float4 ps : $vout.COLOR0 : COL : -1 : 1

#version 110

struct VOutput {
    vec2 _texCoord2;
};

vec4 _ret_0;
uniform sampler2D _texture;

 // main procedure, the original name was ps
void main()
{


    _ret_0 = texture2D(_texture, gl_TexCoord[0].xy);
    gl_FragColor = _ret_0;
    return;
} // main end
"
}
,
"gcm" : {
"vertex" : "
[� p �A����I����,"*�����5���������F=���������\R����POSITIONpositionTEXCOORD0texCoordtexturePOSITIONvs.positionTEXCOORD0vs.texCoord@@�l@���`A��@�l@��`A��",
"fragment" : "
\ ��������*���������
�����������TEXCOORD0texCoordtextureCOLOR0ps@�������?�"
}
}
