struct SexyVertex2D
{
    float4 Position   : SV_POSITION;
    float4 Color	  : COLOR;
    float2 TexCoords  : TEXCOORD0;
    float2 TexCoords2 : TEXCOORD1;
};

struct SexyFragment2D
{
    float4 Position   : SV_POSITION;
    float4 Color	  : COLOR;
    float2 TexCoords  : TEXCOORD0;
    float2 TexCoords2 : TEXCOORD1;
};


//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
						     
Texture2D 	t0 : register(t0);
Texture2D 	t1 : register(t1);
Texture2D 	t2 : register(t2);

SamplerState 	s0 : register(s0);
SamplerState 	s1 : register(s1);
SamplerState 	s2 : register(s2);

