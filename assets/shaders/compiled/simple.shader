{
"dx11" : {
"vertex" : "
// vs_4_0 output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile vs_5_0
// source file: simple.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile vs_5_0
//program vs
//semantic WorldViewProj
//var float4x4 WorldViewProj :  : _WorldViewProj[0], 4 : -1 : 1
//var float4 position : $vin.POSITION : POSITION : 0 : 1
//var float4 normal : $vin.NORMAL :  : 1 : 0
//var float4 vs.position : $vout.POSITION :  : -1 : 1

#pragma pack_matrix(row_major)

struct VOutput {
    float4 _position1 : POSITION;
};

struct X1X {
    float4 _POSITION : SV_Position;
};

static float4 _r0001;
static X1X cout;
uniform float4x4 _WorldViewProj;

 // main procedure, the original name was vs
X1X main(in float4 _position : POSITION)
{

    VOutput _output;

    _r0001.x = dot(_WorldViewProj._11_12_13_14, _position);
    _r0001.y = dot(_WorldViewProj._21_22_23_24, _position);
    _r0001.z = dot(_WorldViewProj._31_32_33_34, _position);
    _r0001.w = dot(_WorldViewProj._41_42_43_44, _position);
    _output._position1 = _r0001;
    cout._POSITION = _output._position1;
    return cout;
} // main end
",
"fragment" : "
// ps_4_0 output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile ps_5_0
// source file: simple.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile ps_5_0
//program ps
//semantic WorldViewProj
//var float4 ps : $vout.COLOR0 : COLOR0 : -1 : 1

#pragma pack_matrix(row_major)

struct VOutput {
    float4 _position : SV_Position;
};

struct X1X {
    int dummy;
};


 // main procedure, the original name was ps
float4 main() : SV_Target0
{


    return float4(  1.00000000000000000E000f,  1.00000000000000000E000f,  1.00000000000000000E000f,  1.00000000000000000E000f);
} // main end
"
}
,
"gl21" : {
"vertex" : "
// glslv output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile glslv
// source file: simple.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile glslv
//program vs
//semantic WorldViewProj
//var float4x4 WorldViewProj :  : _WorldViewProj[0], 4 : -1 : 1
//var float4 position : $vin.POSITION : ATTR0 : 0 : 1
//var float4 normal : $vin.NORMAL :  : 1 : 0
//var float4 vs.position : $vout.POSITION : HPOS : -1 : 1

#version 110

struct VOutput {
    vec4 _position2;
};

vec4 _r0002;
uniform vec4 _WorldViewProj[4];

 // main procedure, the original name was vs
void main()
{


    _r0002.x = dot(_WorldViewProj[0], gl_Vertex);
    _r0002.y = dot(_WorldViewProj[1], gl_Vertex);
    _r0002.z = dot(_WorldViewProj[2], gl_Vertex);
    _r0002.w = dot(_WorldViewProj[3], gl_Vertex);
    gl_Position = _r0002;
    return;
} // main end
",
"fragment" : "
// glslf output by Cg compiler
// cgc version 3.1.0013, build date Apr 18 2012
// command line args: -q -profile glslf
// source file: simple.cg
//vendor NVIDIA Corporation
//version 3.1.0.13
//profile glslf
//program ps
//semantic WorldViewProj
//var float4 ps : $vout.COLOR0 : COL : -1 : 1

#version 110

struct VOutput {
    int dummy;
};


 // main procedure, the original name was ps
void main()
{


    gl_FragColor = vec4( 1.00000000E+000, 1.00000000E+000, 1.00000000E+000, 1.00000000E+000);
    return;
} // main end
"
}
,
"gcm" : {
"vertex" : "
[ 0@PAÿÿÿÿ© Cÿÿÿÿ¹²(‚Àÿÿÿÿ‚Îÿÿÿÿ‚ßÿÿÿÿ‚ğÿÿÿÿ‚ÿÿÿÿÃÿÿÿÿÿÿÿÿPOSITIONpositionNORMALnormalWorldViewProjWorldViewProj[0]WorldViewProj[1]WorldViewProj[2]WorldViewProj[3]POSITIONvs.position@œlĞ0ÀÃ`@?€@œlĞ ÀÃ`@_€@œlĞÀÃ`@Ÿ€@œlĞÀÃ`A",
"fragment" : "
\ğ  0À(¸ÿÿÿÿ@ÿÿÿÿ¸ÿÿÿÿNÿÿÿÿ¸ÿÿÿÿ_ÿÿÿÿ¸ÿÿÿÿpÿÿÿÿ¸ÿÿÿÿÿÿÿÿ
Åÿÿÿÿ™’ÿÿÿÿWorldViewProjWorldViewProj[0]WorldViewProj[1]WorldViewProj[2]WorldViewProj[3]COLOR0psÿÿ~~ÈÈÈœÈÈ?€"
}
}
