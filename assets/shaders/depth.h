// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Pack Unit Float [0,1] into RGB24
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
float3 UnitToColor24New(in float depth) {

  // Constants
  const float3 scale      = float3(1.0, 256.0, 65536.0);
  const float2 ogb        = float2(65536.0, 256.0) / 16777215.0;
  const float normal      = 256.0 / 255.0;

  // Avoid Precision Errors
  float3 unit                     = (float3)depth;
  unit.gb                         -= floor(unit.gb / ogb) * ogb;

  // Scale Up
  float3 color            = unit * scale;

  // Use Fraction to emulate Modulo
  color                           = frac(color);

  // Normalize Range
  color                           *= normal;

  // Mask Noise
  color.rg                        -= color.gb / 256.0;

  return color;
        
}//function

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Unpack RGB24 into Unit Float [0,1]
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
float ColorToUnit24New(in float3 color) {
  const float3 scale = float3(65536.0, 256.0, 1.0) / 65793.0;
  return dot(color, scale);
}//function


float3 PackDepth24(float depth)
{
  //
  // Calculate the integer and fractional parts of the depth
  //
  float depthInteger = floor(depth);
  
  float depthFraction = frac(depth);
  
  //
  // Calculate the upper and lower 8 bits
  //
  float depthUpper = floor(depthInteger / 256.0f);
  
  float depthLower = depthInteger - (depthUpper * 256.0f);

  //
  // Pack the values in a float3 which will be converted to 8bit RGB later
  //
  return float3(depthUpper / 256.0f, depthLower / 256.0f, depthFraction);
}

float UnpackDepth24(float3 depth)
{
  //
  // Unpacking multiplier
  //
  const float3 unpack = {65536.0f, 256.0f, 1.0f};
  
  //
  // Unpack the depth
  //
  return dot(unpack, depth);
}


float3 packDepth(float depth) {
  return UnitToColor24New(depth); 
}

float unpackARGB8Depth(sampler2D depthSampler, float2 texCoord) {
    float3 color = tex2D(depthSampler, texCoord).rgb;
    return ColorToUnit24New(color);
}

float unpackDepth(sampler2D depthSampler, float2 texCoord) {
#ifdef GCM
    // float3 depthColor = tex2D(depthSampler, texCoord).arg;
    // float3 depthFactor = float3(65536.0/16777215.0, 256.0/16777215.0, 1.0/16777215.0);
    // float depth = dot(round(depthColor * 255.0), depthFactor);
    // return depth;
  return texDepth2D_precise(depthSampler, texCoord).r;
#else
     return tex2D(depthSampler, texCoord).r;
#endif
}
