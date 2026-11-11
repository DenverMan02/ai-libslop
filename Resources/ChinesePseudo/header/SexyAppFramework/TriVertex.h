#ifndef __TRIVERTEX_H__
#define __TRIVERTEX_H__

#include "Common.h"
#include "SexyVector.h"

namespace Sexy
{

enum SexyVF
{	
	//the Packed Format flag is reserved for Drivers to optimize away unnecessary vertex data
	// Packed format specs vary on each platform;
	SexyVF_PackedFormat				=			0x001,

	SexyVF_XYZ						=			0x002,
	SexyVF_XYZRHW					=			0x004,
	SexyVF_Normal					=			0x010,
	SexyVF_Diffuse					=			0x040,
	SexyVF_Specular					=			0x080,
	SexyVF_Tex1						=			0x100,
	SexyVF_Tex2						=			0x200,
	SexyVF_Tex3						=			0x300,
	SexyVF_Tex4						=			0x400,
	SexyVF_Tex5						=			0x500,
	SexyVF_Tex6						=			0x600,
	SexyVF_Tex7						=			0x700,	
	SexyVF_Tex8						=			0x800,
};

#define SEXY3DFVF_TEXTUREFORMAT1 3 // one floating point value
#define SEXY3DFVF_TEXTUREFORMAT2 0 // two floating point values
#define SEXY3DFVF_TEXTUREFORMAT3 1 // three floating point values
#define SEXY3DFVF_TEXTUREFORMAT4 2 // four floating point values

#define SexyVF_TexCoordSize1(CoordIndex) (SEXY3DFVF_TEXTUREFORMAT1 << (CoordIndex*2 + 16)) 
#define SexyVF_TexCoordSize2(CoordIndex) (SEXY3DFVF_TEXTUREFORMAT2) 
#define SexyVF_TexCoordSize3(CoordIndex) (SEXY3DFVF_TEXTUREFORMAT3 << (CoordIndex*2 + 16)) 
#define SexyVF_TexCoordSize4(CoordIndex) (SEXY3DFVF_TEXTUREFORMAT4 << (CoordIndex*2 + 16)) 

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class SexyVertex
{
public:
	enum { FVF = 0 };
};

#define MAX_TRIVERTEX_DATA_SIZE 128

class SexyVertex2D : public SexyVertex
{
public:	
	float x,y,z,rhw;
	uint32 color, specular; //ARGB (0 = use color specified in function call)
	float u,v;

public:
	enum { FVF = SexyVF_XYZRHW|SexyVF_Diffuse|SexyVF_Specular|SexyVF_Tex1 };

	SexyVertex2D() { z = 0; rhw = 1; color = 0; specular = 0; }
	SexyVertex2D(float theX, float theY) : x(theX), y(theY) { z = 0; rhw = 1; color = 0; specular = 0; }
	SexyVertex2D(float theX, float theY, float theU, float theV) : x(theX), y(theY), u(theU), v(theV) { z = 0; rhw = 1; color = 0; specular = 0; }
	SexyVertex2D(float theX, float theY, float theU, float theV, uint32 theColor) : x(theX), y(theY), u(theU), v(theV), color(theColor) { z = 0; rhw = 1; specular = 0; }	
	SexyVertex2D(float theX, float theY, float theZ, float theU, float theV, uint32 theColor) : x(theX), y(theY), z(theZ), u(theU), v(theV), color(theColor) { z = 0; rhw = 1; specular = 0; }	
};

// Old name
typedef SexyVertex2D TriVertex;

class SexyVertex3D : public SexyVertex
{
public:	
	float x,y,z;
	uint32 color;//, specular; //ARGB (0 = use color specified in function call)
	float u,v;

public:
	enum { FVF = SexyVF_XYZ|SexyVF_Diffuse|SexyVF_Tex1 };

	SexyVertex3D() { /*color = 0;*/ /*specular = 0;*/ }
	SexyVertex3D(float theX, float theY, float theZ) : x(theX), y(theY), z(theZ) { color = 0; /*specular = 0;*/ }
	SexyVertex3D(float theX, float theY, float theZ, float theU, float theV) : x(theX), y(theY), z(theZ), u(theU), v(theV) { color = 0; /*specular = 0;*/ }
	SexyVertex3D(float theX, float theY, float theZ, float theU, float theV, uint32 theColor) : x(theX), y(theY), z(theZ), u(theU), v(theV), color(theColor) { /*specular = 0;*/ }	
};

class SexyVertex3DLit : public SexyVertex
{
public:	
	MATH_TYPE x,y,z;
	MATH_TYPE nx,ny,nz;
	uint32 color;//, specular; //ARGB (0 = use color specified in function call)
	float u,v;

public:
	enum { FVF = SexyVF_XYZ|SexyVF_Normal|SexyVF_Diffuse|SexyVF_Tex1 };

	inline void MakeDefaultNormal() { SexyVector3 n(x,y,z); n = n.Normalize(); nx = n.x; ny = n.y; nz = n.z; }

	SexyVertex3DLit() { /*color = 0;*/ /*specular = 0;*/ }
	SexyVertex3DLit(const SexyVector3& thePos, const SexyVector3& theNormal) : x(thePos.x), y(thePos.y), z(thePos.z), nx(theNormal.x), ny(theNormal.y), nz(theNormal.z) { color = 0; /*specular = 0;*/ }
	SexyVertex3DLit(const SexyVector3& thePos, const SexyVector3& theNormal, float theU, float theV) : x(thePos.x), y(thePos.y), z(thePos.z), nx(theNormal.x), ny(theNormal.y), nz(theNormal.z), u(theU), v(theV) { color = 0; /*specular = 0;*/ }
	SexyVertex3DLit(const SexyVector3& thePos, const SexyVector3& theNormal, float theU, float theV, uint32 theColor) : x(thePos.x), y(thePos.y), z(thePos.z), nx(theNormal.x), ny(theNormal.y), nz(theNormal.z), u(theU), v(theV), color(theColor) { /*specular = 0;*/ }
	
	SexyVertex3DLit(const SexyVector3& thePos) : x(thePos.x), y(thePos.y), z(thePos.z) { MakeDefaultNormal(); color = 0; /*specular = 0;*/ }
	SexyVertex3DLit(const SexyVector3& thePos, float theU, float theV) : x(thePos.x), y(thePos.y), z(thePos.z), u(theU), v(theV) { MakeDefaultNormal(); color = 0; /*specular = 0;*/ }
	SexyVertex3DLit(const SexyVector3& thePos, float theU, float theV, uint32 theColor) : x(thePos.x), y(thePos.y), z(thePos.z), u(theU), v(theV), color(theColor) { MakeDefaultNormal(); /*specular = 0;*/ }
};

} // namespace Sexy


#endif
