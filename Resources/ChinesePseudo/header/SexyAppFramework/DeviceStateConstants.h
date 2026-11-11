#ifndef D3DSTATECONSTANTS_H
#define D3DSTATECONSTANTS_H

#include "Common.h"

typedef uint32 D3DCOLOR;
#ifndef RGBA_MAKE
#define RGBA_MAKE(r, g, b, a)   ((D3DCOLOR) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))
#endif

#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
((uint32)(uint8)(ch0) | ((uint32)(uint8)(ch1) << 8) |   \
 ((uint32)(uint8)(ch2) << 16) | ((uint32)(uint8)(ch3) << 24 ))
#endif


namespace Sexy
{
////////////////////////////////////////////////////////////////////////////////////

enum SEXY3DPOOL
{
    SEXY3DPOOL_DEFAULT                 = 0,
    SEXY3DPOOL_MANAGED                 = 1,
    SEXY3DPOOL_SYSTEMMEM               = 2,
    SEXY3DPOOL_SCRATCH                 = 3,

    SEXY3DPOOL_FORCE_DWORD             = 0x7fffffff
};

enum SEXY3DCUBEMAP_FACES
{
    SEXY3DCUBEMAP_FACE_POSITIVE_X     = 0,
    SEXY3DCUBEMAP_FACE_NEGATIVE_X     = 1,
    SEXY3DCUBEMAP_FACE_POSITIVE_Y     = 2,
    SEXY3DCUBEMAP_FACE_NEGATIVE_Y     = 3,
    SEXY3DCUBEMAP_FACE_POSITIVE_Z     = 4,
    SEXY3DCUBEMAP_FACE_NEGATIVE_Z     = 5,

    SEXY3DCUBEMAP_FACE_FORCE_DWORD    = 0x7fffffff
};

// these are the common formats between D3D 8 and 9; those which exist only in one version or the other have been removed
enum SEXY3DFORMAT
{
    SEXY3DFMT_UNKNOWN              =  0,

    SEXY3DFMT_R8G8B8               = 20,
    SEXY3DFMT_A8R8G8B8             = 21,
    SEXY3DFMT_X8R8G8B8             = 22,
    SEXY3DFMT_R5G6B5               = 23,
    SEXY3DFMT_X1R5G5B5             = 24,
    SEXY3DFMT_A1R5G5B5             = 25,
    SEXY3DFMT_A4R4G4B4             = 26,
    SEXY3DFMT_R3G3B2               = 27,
    SEXY3DFMT_A8                   = 28,
    SEXY3DFMT_A8R3G3B2             = 29,
    SEXY3DFMT_X4R4G4B4             = 30,
    SEXY3DFMT_A2B10G10R10          = 31,
    SEXY3DFMT_G16R16               = 34,

    SEXY3DFMT_A8P8                 = 40,
    SEXY3DFMT_P8                   = 41,

    SEXY3DFMT_L8                   = 50,
    SEXY3DFMT_A8L8                 = 51,
    SEXY3DFMT_A4L4                 = 52,

    SEXY3DFMT_V8U8                 = 60,
    SEXY3DFMT_L6V5U5               = 61,
    SEXY3DFMT_X8L8V8U8             = 62,
    SEXY3DFMT_Q8W8V8U8             = 63,
    SEXY3DFMT_V16U16               = 64,
    SEXY3DFMT_A2W10V10U10          = 67,

    SEXY3DFMT_UYVY                 = MAKEFOURCC('U', 'Y', 'V', 'Y'),
    SEXY3DFMT_YUY2                 = MAKEFOURCC('Y', 'U', 'Y', '2'),
    SEXY3DFMT_DXT1                 = MAKEFOURCC('D', 'X', 'T', '1'),
    SEXY3DFMT_DXT2                 = MAKEFOURCC('D', 'X', 'T', '2'),
    SEXY3DFMT_DXT3                 = MAKEFOURCC('D', 'X', 'T', '3'),
    SEXY3DFMT_DXT4                 = MAKEFOURCC('D', 'X', 'T', '4'),
    SEXY3DFMT_DXT5                 = MAKEFOURCC('D', 'X', 'T', '5'),

    SEXY3DFMT_D16_LOCKABLE         = 70,
    SEXY3DFMT_D32                  = 71,
    SEXY3DFMT_D15S1                = 73,
    SEXY3DFMT_D24S8                = 75,
    SEXY3DFMT_D16                  = 80,
    SEXY3DFMT_D24X8                = 77,
    SEXY3DFMT_D24X4S4              = 79,


    SEXY3DFMT_VERTEXDATA           =100,
    SEXY3DFMT_INDEX16              =101,
    SEXY3DFMT_INDEX32              =102,

    SEXY3DFMT_FORCE_DWORD          =0x7fffffff
};

// common lock flags between D3D 8 and 9
enum
{
	SEXY3DLOCK_READONLY				= 0x00000010,
	SEXY3DLOCK_NOSYSLOCK			= 0x00000800,
	SEXY3DLOCK_NOOVERWRITE			= 0x00001000,
	SEXY3DLOCK_DISCARD				= 0x00002000,
	SEXY3DLOCK_NO_DIRTY_UPDATE		= 0x00008000,

	SEXY3DLOCK_FORCE_DWORD			= 0x7fffffff
};

////////////////////////////////////////////////////////////////////////////////////
// !D3D RENDER STATE
////////////////////////////////////////////////////////////////////////////////////

enum SEXY3DSHADEMODE
{
    SEXY3DSHADE_FLAT               = 1,
    SEXY3DSHADE_GOURAUD            = 2,
    SEXY3DSHADE_PHONG              = 3,
    SEXY3DSHADE_FORCE_DWORD        = 0x7fffffff, /* force 32-bit size enum */
};

enum SEXY3DFILLMODE {
    SEXY3DFILL_POINT               = 1,
    SEXY3DFILL_WIREFRAME           = 2,
    SEXY3DFILL_SOLID               = 3,
    SEXY3DFILL_FORCE_DWORD         = 0x7fffffff, /* force 32-bit size enum */
};

enum SEXY3DBLENDMODE {
    SEXY3DBLEND_ZERO               = 1,
    SEXY3DBLEND_ONE                = 2,
    SEXY3DBLEND_SRCCOLOR           = 3,
    SEXY3DBLEND_INVSRCCOLOR        = 4,
    SEXY3DBLEND_SRCALPHA           = 5,
    SEXY3DBLEND_INVSRCALPHA        = 6,
    SEXY3DBLEND_DESTALPHA          = 7,
    SEXY3DBLEND_INVDESTALPHA       = 8,
    SEXY3DBLEND_DESTCOLOR          = 9,
    SEXY3DBLEND_INVDESTCOLOR       = 10,
    SEXY3DBLEND_SRCALPHASAT        = 11,
    SEXY3DBLEND_BOTHSRCALPHA       = 12,
    SEXY3DBLEND_BOTHINVSRCALPHA    = 13,
    SEXY3DBLEND_BLENDFACTOR        = 14, /* Only supported if D3DPBLENDCAPS_BLENDFACTOR is on */
    SEXY3DBLEND_INVBLENDFACTOR     = 15, /* Only supported if D3DPBLENDCAPS_BLENDFACTOR is on */
    SEXY3DBLEND_FORCE_DWORD        = 0x7fffffff, /* force 32-bit size enum */
};

enum SEXY3DBLENDOP {
    SEXY3DBLENDOP_ADD              = 1,
    SEXY3DBLENDOP_SUBTRACT         = 2,
    SEXY3DBLENDOP_REVSUBTRACT      = 3,
    SEXY3DBLENDOP_MIN              = 4,
    SEXY3DBLENDOP_MAX              = 5,
    SEXY3DBLENDOP_FORCE_DWORD      = 0x7fffffff, /* force 32-bit size enum */
};

enum SEXY3DTEXTUREADDRESS {
    SEXY3DTADDRESS_WRAP            = 1,
    SEXY3DTADDRESS_MIRROR          = 2,
    SEXY3DTADDRESS_CLAMP           = 3,
    SEXY3DTADDRESS_BORDER          = 4,
    SEXY3DTADDRESS_MIRRORONCE      = 5,
    SEXY3DTADDRESS_FORCE_DWORD     = 0x7fffffff, /* force 32-bit size enum */
};

enum SEXY3DCULL {
    SEXY3DCULL_NONE                = 1,
    SEXY3DCULL_CW                  = 2,
    SEXY3DCULL_CCW                 = 3,
    SEXY3DCULL_FORCE_DWORD         = 0x7fffffff, /* force 32-bit size enum */
};

enum SEXY3DCMPFUNC {
    SEXY3DCMP_NEVER                = 1,
    SEXY3DCMP_LESS                 = 2,
    SEXY3DCMP_EQUAL                = 3,
    SEXY3DCMP_LESSEQUAL            = 4,
    SEXY3DCMP_GREATER              = 5,
    SEXY3DCMP_NOTEQUAL             = 6,
    SEXY3DCMP_GREATEREQUAL         = 7,
    SEXY3DCMP_ALWAYS               = 8,
    SEXY3DCMP_FORCE_DWORD          = 0x7fffffff, /* force 32-bit size enum */
};

enum SEXY3DSTENCILOP {
    SEXY3DSTENCILOP_KEEP           = 1,
    SEXY3DSTENCILOP_ZERO           = 2,
    SEXY3DSTENCILOP_REPLACE        = 3,
    SEXY3DSTENCILOP_INCRSAT        = 4,
    SEXY3DSTENCILOP_DECRSAT        = 5,
    SEXY3DSTENCILOP_INVERT         = 6,
    SEXY3DSTENCILOP_INCR           = 7,
    SEXY3DSTENCILOP_DECR           = 8,
    SEXY3DSTENCILOP_FORCE_DWORD    = 0x7fffffff, /* force 32-bit size enum */
};

enum SEXY3DFOGMODE {
    SEXY3DFOG_NONE                 = 0,
    SEXY3DFOG_EXP                  = 1,
    SEXY3DFOG_EXP2                 = 2,
    SEXY3DFOG_LINEAR               = 3,
    SEXY3DFOG_FORCE_DWORD          = 0x7fffffff, /* force 32-bit size enum */
};

enum SEXY3DZBUFFERTYPE {
    SEXY3DZB_FALSE                 = 0,
    SEXY3DZB_TRUE                  = 1, // Z buffering
    SEXY3DZB_USEW                  = 2, // W buffering
    SEXY3DZB_FORCE_DWORD           = 0x7fffffff, /* force 32-bit size enum */
};

// Primitives supported by draw-primitive API
enum SEXY3DPRIMITIVETYPE {
    SEXY3DPT_POINTLIST             = 1,
    SEXY3DPT_LINELIST              = 2,
    SEXY3DPT_LINESTRIP             = 3,
    SEXY3DPT_TRIANGLELIST          = 4,
    SEXY3DPT_TRIANGLESTRIP         = 5,
    SEXY3DPT_TRIANGLEFAN           = 6,
    SEXY3DPT_FORCE_DWORD           = 0x7fffffff, /* force 32-bit size enum */
};

enum SEXY3DTRANSFORMSTATETYPE {
    SEXY3DTS_VIEW          = 2,
    SEXY3DTS_PROJECTION    = 3,
    SEXY3DTS_TEXTURE0      = 16,
    SEXY3DTS_TEXTURE1      = 17,
    SEXY3DTS_TEXTURE2      = 18,
    SEXY3DTS_TEXTURE3      = 19,
    SEXY3DTS_TEXTURE4      = 20,
    SEXY3DTS_TEXTURE5      = 21,
    SEXY3DTS_TEXTURE6      = 22,
    SEXY3DTS_TEXTURE7      = 23,
    SEXY3DTS_FORCE_DWORD     = 0x7fffffff, /* force 32-bit size enum */
};

enum SEXY3DTEXTURETRANSFORMFLAGS {
	SEXY3DTTFF_DISABLE		= 0,
	SEXY3DTTFF_COUNT1		= 1,
	SEXY3DTTFF_COUNT2		= 2,
	SEXY3DTTFF_COUNT3		= 3,
	SEXY3DTTFF_COUNT4		= 4,
	SEXY3DTTFF_PROJECTED	= 256,
	SEXY3DTTFF_FORCE_DWORD	= 0x7fffffff, /* force 32-bit size enum */
};

#define SEXY3DTS_WORLDMATRIX(index) (SEXY3DTRANSFORMSTATETYPE)(index + 256)
#define SEXY3DTS_WORLD  SEXY3DTS_WORLDMATRIX(0)
#define SEXY3DTS_WORLD1 SEXY3DTS_WORLDMATRIX(1)
#define SEXY3DTS_WORLD2 SEXY3DTS_WORLDMATRIX(2)
#define SEXY3DTS_WORLD3 SEXY3DTS_WORLDMATRIX(3)

enum SEXY3DRSS
{
    SEXY3DRS_ZENABLE				= 7,    /* SEXY3DZBUFFERTYPE (or TRUE/FALSE for legacy) */
    SEXY3DRS_FILLMODE				= 8,    /* SEXY3DFILLMODE */
    SEXY3DRS_SHADEMODE				= 9,    /* SEXY3DSHADEMODE */
    SEXY3DRS_ZWRITEENABLE			= 14,   /* TRUE to enable z writes */
    SEXY3DRS_ALPHATESTENABLE		= 15,   /* TRUE to enable alpha tests */
    SEXY3DRS_LASTPIXEL				= 16,   /* TRUE for last-pixel on lines */
    SEXY3DRS_SRCBLEND				= 19,   /* SEXY3DBLEND */
    SEXY3DRS_DESTBLEND				= 20,   /* SEXY3DBLEND */
    SEXY3DRS_CULLMODE				= 22,   /* SEXY3DCULL */
    SEXY3DRS_ZFUNC					= 23,   /* SEXY3DCMPFUNC */
    SEXY3DRS_ALPHAREF				= 24,   /* SEXY3DFIXED */
    SEXY3DRS_ALPHAFUNC				= 25,   /* SEXY3DCMPFUNC */
    SEXY3DRS_DITHERENABLE			= 26,   /* TRUE to enable dithering */
    SEXY3DRS_ALPHABLENDENABLE		= 27,   /* TRUE to enable alpha blending */
    SEXY3DRS_FOGENABLE				= 28,   /* TRUE to enable fog blending */
    SEXY3DRS_SPECULARENABLE			= 29,   /* TRUE to enable specular */
    SEXY3DRS_FOGCOLOR				= 34,   /* SEXY3DCOLOR */
    SEXY3DRS_FOGTABLEMODE			= 35,   /* SEXY3DFOGMODE */
    SEXY3DRS_FOGSTART				= 36,   /* Fog start (for both vertex and pixel fog) */
    SEXY3DRS_FOGEND					= 37,   /* Fog end      */
    SEXY3DRS_FOGDENSITY				= 38,   /* Fog density  */
    SEXY3DRS_RANGEFOGENABLE			= 48,   /* Enables range-based fog */
    SEXY3DRS_STENCILENABLE			= 52,   /* BOOL enable/disable stenciling */
    SEXY3DRS_STENCILFAIL			= 53,   /* SEXY3DSTENCILOP to do if stencil test fails */
    SEXY3DRS_STENCILZFAIL			= 54,   /* SEXY3DSTENCILOP to do if stencil test passes and Z test fails */
    SEXY3DRS_STENCILPASS			= 55,   /* SEXY3DSTENCILOP to do if both stencil and Z tests pass */
    SEXY3DRS_STENCILFUNC			= 56,   /* SEXY3DCMPFUNC fn.  Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
    SEXY3DRS_STENCILREF				= 57,   /* Reference value used in stencil test */
    SEXY3DRS_STENCILMASK			= 58,   /* Mask value used in stencil test */
    SEXY3DRS_STENCILWRITEMASK		= 59,   /* Write mask applied to values written to stencil buffer */
    SEXY3DRS_TEXTUREFACTOR			= 60,   /* SEXY3DCOLOR used for multi-texture blend */
    SEXY3DRS_WRAP0					= 128,  /* wrap for 1st texture coord. set */
    SEXY3DRS_WRAP1					= 129,  /* wrap for 2nd texture coord. set */
    SEXY3DRS_WRAP2					= 130,  /* wrap for 3rd texture coord. set */
    SEXY3DRS_WRAP3					= 131,  /* wrap for 4th texture coord. set */
    SEXY3DRS_WRAP4					= 132,  /* wrap for 5th texture coord. set */
    SEXY3DRS_WRAP5					= 133,  /* wrap for 6th texture coord. set */
    SEXY3DRS_WRAP6					= 134,  /* wrap for 7th texture coord. set */
    SEXY3DRS_WRAP7					= 135,  /* wrap for 8th texture coord. set */
    SEXY3DRS_CLIPPING				= 136,
    SEXY3DRS_LIGHTING				= 137,
    SEXY3DRS_AMBIENT				= 139,
    SEXY3DRS_FOGVERTEXMODE			= 140,
    SEXY3DRS_COLORVERTEX			= 141,
    SEXY3DRS_LOCALVIEWER			= 142,
    SEXY3DRS_NORMALIZENORMALS		= 143,
    SEXY3DRS_DIFFUSEMATERIALSOURCE	= 145,
    SEXY3DRS_SPECULARMATERIALSOURCE	= 146,
    SEXY3DRS_AMBIENTMATERIALSOURCE	= 147,
    SEXY3DRS_EMISSIVEMATERIALSOURCE	= 148,
    SEXY3DRS_VERTEXBLEND			= 151,
    SEXY3DRS_CLIPPLANEENABLE		= 152,
    SEXY3DRS_POINTSIZE				= 154,   /* float point size */
    SEXY3DRS_POINTSIZE_MIN			= 155,   /* float point size min threshold */
    SEXY3DRS_POINTSPRITEENABLE		= 156,   /* BOOL point texture coord control */
    SEXY3DRS_POINTSCALEENABLE		= 157,   /* BOOL point size scale enable */
    SEXY3DRS_POINTSCALE_A			= 158,   /* float point attenuation A value */
    SEXY3DRS_POINTSCALE_B			= 159,   /* float point attenuation B value */
    SEXY3DRS_POINTSCALE_C			= 160,   /* float point attenuation C value */
    SEXY3DRS_MULTISAMPLEANTIALIAS	= 161,  // BOOL - set to do FSAA with multisample buffer
    SEXY3DRS_MULTISAMPLEMASK		= 162,  // DWORD - per-sample enable/disable
    SEXY3DRS_PATCHEDGESTYLE			= 163,  // Sets whether patch edges will use float style tessellation
    SEXY3DRS_DEBUGMONITORTOKEN		= 165,  // DEBUG ONLY - token to debug monitor
    SEXY3DRS_POINTSIZE_MAX			= 166,   /* float point size max threshold */
    SEXY3DRS_INDEXEDVERTEXBLENDENABLE = 167,
    SEXY3DRS_COLORWRITEENABLE		= 168,  // per-channel write enable
    SEXY3DRS_TWEENFACTOR			= 170,   // float tween factor
    SEXY3DRS_BLENDOP				= 171,   // SEXY3DBLENDOP setting
    SEXY3DRS_POSITIONDEGREE			= 172,   // NPatch position interpolation degree. SEXY3DDEGREE_LINEAR or SEXY3DDEGREE_CUBIC (default)
    SEXY3DRS_NORMALDEGREE			= 173,   // NPatch normal interpolation degree. SEXY3DDEGREE_LINEAR (default) or SEXY3DDEGREE_QUADRATIC
    SEXY3DRS_SCISSORTESTENABLE		= 174,
    SEXY3DRS_SLOPESCALEDEPTHBIAS	= 175,
    SEXY3DRS_ANTIALIASEDLINEENABLE	= 176,
    SEXY3DRS_MINTESSELLATIONLEVEL	= 178,
    SEXY3DRS_MAXTESSELLATIONLEVEL	= 179,
    SEXY3DRS_ADAPTIVETESS_X			= 180,
    SEXY3DRS_ADAPTIVETESS_Y			= 181,
    SEXY3DRS_ADAPTIVETESS_Z			= 182,
    SEXY3DRS_ADAPTIVETESS_W			= 183,
    SEXY3DRS_ENABLEADAPTIVETESSELLATION = 184,
    SEXY3DRS_TWOSIDEDSTENCILMODE	= 185,   /* BOOL enable/disable 2 sided stenciling */
    SEXY3DRS_CCW_STENCILFAIL		= 186,   /* SEXY3DSTENCILOP to do if ccw stencil test fails */
    SEXY3DRS_CCW_STENCILZFAIL		= 187,   /* SEXY3DSTENCILOP to do if ccw stencil test passes and Z test fails */
    SEXY3DRS_CCW_STENCILPASS		= 188,   /* SEXY3DSTENCILOP to do if both ccw stencil and Z tests pass */
    SEXY3DRS_CCW_STENCILFUNC		= 189,   /* SEXY3DCMPFUNC fn.  ccw Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
    SEXY3DRS_COLORWRITEENABLE1		= 190,   /* Additional ColorWriteEnables for the devices that support SEXY3DPMISCCAPS_INDEPENDENTWRITEMASKS */
    SEXY3DRS_COLORWRITEENABLE2		= 191,   /* Additional ColorWriteEnables for the devices that support SEXY3DPMISCCAPS_INDEPENDENTWRITEMASKS */
    SEXY3DRS_COLORWRITEENABLE3		= 192,   /* Additional ColorWriteEnables for the devices that support SEXY3DPMISCCAPS_INDEPENDENTWRITEMASKS */
    SEXY3DRS_BLENDFACTOR			= 193,   /* SEXY3DCOLOR used for a constant blend factor during alpha blending for devices that support SEXY3DPBLENDCAPS_BLENDFACTOR */
    SEXY3DRS_SRGBWRITEENABLE		= 194,   /* Enable rendertarget writes to be DE-linearized to SRGB (for formats that expose SEXY3DUSAGE_QUERY_SRGBWRITE) */
    SEXY3DRS_DEPTHBIAS				= 195,
    SEXY3DRS_WRAP8					= 198,   /* Additional wrap states for vs_3_0+ attributes with SEXY3DDECLUSAGE_TEXCOORD */
    SEXY3DRS_WRAP9					= 199,
    SEXY3DRS_WRAP10					= 200,
    SEXY3DRS_WRAP11					= 201,
    SEXY3DRS_WRAP12					= 202,
    SEXY3DRS_WRAP13					= 203,
    SEXY3DRS_WRAP14					= 204,
    SEXY3DRS_WRAP15					= 205,
    SEXY3DRS_SEPARATEALPHABLENDENABLE  = 206,  /* TRUE to enable a separate blending function for the alpha channel */
    SEXY3DRS_SRCBLENDALPHA			= 207,  /* SRC blend factor for the alpha channel when SEXY3DRS_SEPARATEDESTALPHAENABLE is TRUE */
    SEXY3DRS_DESTBLENDALPHA			= 208,  /* DST blend factor for the alpha channel when SEXY3DRS_SEPARATEDESTALPHAENABLE is TRUE */
    SEXY3DRS_BLENDOPALPHA			= 209,  /* Blending operation for the alpha channel when SEXY3DRS_SEPARATEDESTALPHAENABLE is TRUE */


    SEXY3DRS_FORCE_DWORD			= 0x7fffffff, /* force 32-bit size enum */
};

////////////////////////////////////////////////////////////////////////////////////
// !D3D TEXTURE STAGE STATE
////////////////////////////////////////////////////////////////////////////////////

enum SEXY3DTEXTURESTAGESTATETYPE
{
	SEXY3DTSS_COLOROP        =  1, /* D3DTEXTUREOP - per-stage blending controls for color channels */
	SEXY3DTSS_COLORARG1      =  2, /* D3DTA_* (texture arg) */
	SEXY3DTSS_COLORARG2      =  3, /* D3DTA_* (texture arg) */
	SEXY3DTSS_ALPHAOP        =  4, /* D3DTEXTUREOP - per-stage blending controls for alpha channel */
	SEXY3DTSS_ALPHAARG1      =  5, /* D3DTA_* (texture arg) */
	SEXY3DTSS_ALPHAARG2      =  6, /* D3DTA_* (texture arg) */
	SEXY3DTSS_BUMPENVMAT00   =  7, /* float (bump mapping matrix) */
	SEXY3DTSS_BUMPENVMAT01   =  8, /* float (bump mapping matrix) */
	SEXY3DTSS_BUMPENVMAT10   =  9, /* float (bump mapping matrix) */
	SEXY3DTSS_BUMPENVMAT11   = 10, /* float (bump mapping matrix) */
	SEXY3DTSS_TEXCOORDINDEX  = 11, /* identifies which set of texture coordinates index this texture */
	SEXY3DTSS_BUMPENVLSCALE  = 22, /* float scale for bump map luminance */
	SEXY3DTSS_BUMPENVLOFFSET = 23, /* float offset for bump map luminance */
	SEXY3DTSS_TEXTURETRANSFORMFLAGS = 24, /* D3DTEXTURETRANSFORMFLAGS controls texture transform */
	SEXY3DTSS_COLORARG0      = 26, /* D3DTA_* third arg for triadic ops */
	SEXY3DTSS_ALPHAARG0      = 27, /* D3DTA_* third arg for triadic ops */
	SEXY3DTSS_RESULTARG      = 28, /* D3DTA_* arg for result (CURRENT or TEMP) */
	SEXY3DTSS_CONSTANT       = 32, /* Per-stage constant D3DTA_CONSTANT */


	SEXY3DTSS_FORCE_DWORD   = 0x7fffffff, /* force 32-bit size enum */
};

#define SEXY3DTSS_TCI_PASSTHRU                             0x00000000
#define SEXY3DTSS_TCI_CAMERASPACENORMAL                    0x00010000
#define SEXY3DTSS_TCI_CAMERASPACEPOSITION                  0x00020000
#define SEXY3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR          0x00030000
#define SEXY3DTSS_TCI_SPHEREMAP                            0x00040000

/*
 * Enumerations for COLOROP and ALPHAOP texture blending operations set in
 * texture processing stage controls in D3DTSS.
 */
enum SEXY3DTEXTUREOP
{
    // Control
    SEXY3DTOP_DISABLE              = 1,      // disables stage
    SEXY3DTOP_SELECTARG1           = 2,      // the default
    SEXY3DTOP_SELECTARG2           = 3,

    // Modulate
    SEXY3DTOP_MODULATE             = 4,      // multiply args together
    SEXY3DTOP_MODULATE2X           = 5,      // multiply and  1 bit
    SEXY3DTOP_MODULATE4X           = 6,      // multiply and  2 bits

    // Add
    SEXY3DTOP_ADD                  =  7,   // add arguments together
    SEXY3DTOP_ADDSIGNED            =  8,   // add with -0.5 bias
    SEXY3DTOP_ADDSIGNED2X          =  9,   // as above but left  1 bit
    SEXY3DTOP_SUBTRACT             = 10,   // Arg1 - Arg2, with no saturation
    SEXY3DTOP_ADDSMOOTH            = 11,   // add 2 args, subtract product
                                        // Arg1 + Arg2 - Arg1*Arg2
                                        // = Arg1 + (1-Arg1)*Arg2

    // Linear alpha blend: Arg1*(Alpha) + Arg2*(1-Alpha)
    SEXY3DTOP_BLENDDIFFUSEALPHA    = 12, // iterated alpha
    SEXY3DTOP_BLENDTEXTUREALPHA    = 13, // texture alpha
    SEXY3DTOP_BLENDFACTORALPHA     = 14, // alpha from D3DRS_TEXTUREFACTOR

    // Linear alpha blend with pre-multiplied arg1 input: Arg1 + Arg2*(1-Alpha)
    SEXY3DTOP_BLENDTEXTUREALPHAPM  = 15, // texture alpha
    SEXY3DTOP_BLENDCURRENTALPHA    = 16, // by alpha of current color

    // Specular mapping
    SEXY3DTOP_PREMODULATE            = 17,     // modulate with next texture before use
    SEXY3DTOP_MODULATEALPHA_ADDCOLOR = 18,     // Arg1.RGB + Arg1.A*Arg2.RGB
                                            // COLOROP only
    SEXY3DTOP_MODULATECOLOR_ADDALPHA = 19,     // Arg1.RGB*Arg2.RGB + Arg1.A
                                            // COLOROP only
    SEXY3DTOP_MODULATEINVALPHA_ADDCOLOR = 20,  // (1-Arg1.A)*Arg2.RGB + Arg1.RGB
                                            // COLOROP only
    SEXY3DTOP_MODULATEINVCOLOR_ADDALPHA = 21,  // (1-Arg1.RGB)*Arg2.RGB + Arg1.A
                                            // COLOROP only

    // Bump mapping
    SEXY3DTOP_BUMPENVMAP           = 22, // per pixel env map perturbation
    SEXY3DTOP_BUMPENVMAPLUMINANCE  = 23, // with luminance channel

    // This can do either diffuse or specular bump mapping with correct input.
    // Performs the function (Arg1.R*Arg2.R + Arg1.G*Arg2.G + Arg1.B*Arg2.B)
    // where each component has been scaled and offset to make it signed.
    // The result is replicated into all four (including alpha) channels.
    // This is a valid COLOROP only.
    SEXY3DTOP_DOTPRODUCT3          = 24,

    // Triadic ops
    SEXY3DTOP_MULTIPLYADD          = 25, // Arg0 + Arg1*Arg2
    SEXY3DTOP_LERP                 = 26, // (Arg0)*Arg1 + (1-Arg0)*Arg2

    SEXY3DTOP_FORCE_DWORD = 0x7fffffff,
};

/*
 * Values for COLORARG0,1,2, ALPHAARG0,1,2, and RESULTARG texture blending
 * operations set in texture processing stage controls in D3DRENDERSTATE.
 */
#define SEXY3DTA_SELECTMASK        0x0000000f  // mask for arg selector
#define SEXY3DTA_DIFFUSE           0x00000000  // select diffuse color (read only)
#define SEXY3DTA_CURRENT           0x00000001  // select stage destination register (read/write)
#define SEXY3DTA_TEXTURE           0x00000002  // select texture color (read only)
#define SEXY3DTA_TFACTOR           0x00000003  // select D3DRS_TEXTUREFACTOR (read only)
#define SEXY3DTA_SPECULAR          0x00000004  // select specular color (read only)
#define SEXY3DTA_TEMP              0x00000005  // select temporary register color (read/write)
#define SEXY3DTA_CONSTANT          0x00000006  // select texture stage constant
#define SEXY3DTA_COMPLEMENT        0x00000010  // take 1.0 - x (read modifier)
#define SEXY3DTA_ALPHAREPLICATE    0x00000020  // replicate alpha to color components (read modifier)

////////////////////////////////////////////////////////////////////////////////////
// !D3D SAMPLER STATE
////////////////////////////////////////////////////////////////////////////////////

enum SEXY3DTEXTUREFILTERTYPE
{
    SEXY3DTEXF_NONE            = 0,    // filtering disabled (valid for mip filter only)
    SEXY3DTEXF_POINT           = 1,    // nearest
    SEXY3DTEXF_LINEAR          = 2,    // linear interpolation
    SEXY3DTEXF_ANISOTROPIC     = 3,    // anisotropic
    SEXY3DTEXF_PYRAMIDALQUAD   = 6,    // 4-sample tent
    SEXY3DTEXF_GAUSSIANQUAD    = 7,    // 4-sample gaussian
    SEXY3DTEXF_FORCE_DWORD     = 0x7fffffff,   // force 32-bit size enum
};

enum SEXY3DSAMPLERSTATETYPE
{
	SEXY3DSAMP_ADDRESSU       = 1,  /* D3DTEXTUREADDRESS for U coordinate */
	SEXY3DSAMP_ADDRESSV       = 2,  /* D3DTEXTUREADDRESS for V coordinate */
	SEXY3DSAMP_ADDRESSW       = 3,  /* D3DTEXTUREADDRESS for W coordinate */
	SEXY3DSAMP_BORDERCOLOR    = 4,  /* D3DCOLOR */
	SEXY3DSAMP_MAGFILTER      = 5,  /* D3DTEXTUREFILTER filter to use for magnification */
	SEXY3DSAMP_MINFILTER      = 6,  /* D3DTEXTUREFILTER filter to use for minification */
	SEXY3DSAMP_MIPFILTER      = 7,  /* D3DTEXTUREFILTER filter to use between mipmaps during minification */
	SEXY3DSAMP_MIPMAPLODBIAS  = 8,  /* float Mipmap LOD bias */
	SEXY3DSAMP_MAXMIPLEVEL    = 9,  /* DWORD 0..(n-1) LOD index of largest map to use (0 == largest) */
	SEXY3DSAMP_MAXANISOTROPY  = 10, /* DWORD maximum anisotropy */
	SEXY3DSAMP_SRGBTEXTURE    = 11, /* Default = 0 (which means Gamma 1.0,
                                       no correction required.) else correct for
                              Gamma = 2.2 */
	SEXY3DSAMP_ELEMENTINDEX   = 12, /* When multi-element texture is assigned to sampler, this
                                    indicates which element index to use.  Default = 0.  */
	SEXY3DSAMP_DMAPOFFSET     = 13, /* Offset in vertices in the pre-sampled displacement map.
                                    Only valid for D3DDMAPSAMPLER sampler  */
	SEXY3DSAMP_FORCE_DWORD   = 0x7fffffff, /* force 32-bit size enum */
};

}

#endif // #ifndef SEXY3DSTATECONSTANTS_H
