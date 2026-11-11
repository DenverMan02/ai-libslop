#pragma once
#ifndef __D3DSTATEMANAGER_H__
#define __D3DSTATEMANAGER_H__
//****************************************************************************
//**
//**  File     :  D3DSTATEMANAGER.H
//**  Summary  :  Header - RenderStateManager for Direct3D 8/9
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************
//============================================================================
//    HEADERS
//============================================================================
#include "RenderStateManager.h"
#include "Graphics.h"
#include "SexyMatrix.h"

namespace Sexy {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
/*
	D3DStateManager

	StateManager for Direct3D 8/9.
*/
class D3DStateManager
: public RenderStateManager
{
protected:
	enum EStateGroup
	{
		SG_RS, // [D3DRS] (uses SetRenderState)
		SG_TSS, // [D3DTSS][stage index] (uses SetTextureStageState)
		SG_SS, // [D3DSAMP][sampler index] (uses SetSamplerState)
		SG_LIGHT, // [ELightState][light index] (uses LightEnable and SetLight)
		SG_MATERIAL, // [EMaterialState] (uses SetMaterial)
		SG_STREAM, // [EStreamState][stream number] (uses SetStreamSource and SetStreamSourceFreq)
		SG_TRANSFORM, // [D3DTS][row number 0-3] (uses SetTransform)
		SG_VIEWPORT, // [EViewportState] (uses SetViewport)
		SG_MISC, // [EMiscState][variable, see individual state]

		SG_COUNT
	};

	enum
	{
		ST_COUNT_RS = 256, // (dword)
		ST_COUNT_TSS = 48, // (dword)
		ST_COUNT_SS = 16, // (dword)
		ST_COUNT_TRANSFORM = 512 // (vector) accounts for the up to 256 D3DTS_WORLDMATRIX(index) transforms
	};

	enum ELightState
	{
		ST_LIGHT_ENABLED, // (dword bool)
		ST_LIGHT_TYPE, // (dword D3DLIGHT_)
		ST_LIGHT_DIFFUSE, // (vector RGBA)
		ST_LIGHT_SPECULAR, // (vector RGBA)
		ST_LIGHT_AMBIENT, // (vector RGBA)
		ST_LIGHT_POSITION, // (vector XYZ)
		ST_LIGHT_DIRECTION, // (vector XYZ)
		ST_LIGHT_RANGE, // (float)
		ST_LIGHT_FALLOFF, // (float)
		ST_LIGHT_ATTENUATION, // (vector Atten0 Atten1 Atten2)
		ST_LIGHT_ANGLES, // (vector Theta Phi)

		ST_COUNT_LIGHT
	};
	enum EMaterialState
	{
		ST_MAT_DIFFUSE, // (vector RGBA)
		ST_MAT_AMBIENT, // (vector RGBA)
		ST_MAT_SPECULAR, // (vector RGBA)
		ST_MAT_EMISSIVE, // (vector RGBA)
		ST_MAT_POWER, // (float)

		ST_COUNT_MAT
	};
	enum EStreamState
	{
		ST_STREAM_DATA, // (ptr)
		ST_STREAM_OFFSET, // (dword)
		ST_STREAM_STRIDE, // (dword)
		ST_STREAM_FREQ, // (dword)

		ST_COUNT_STREAM
	};
	enum EViewportState
	{
		ST_VIEWPORT_X, // (dword)
		ST_VIEWPORT_Y, // (dword)
		ST_VIEWPORT_WIDTH, // (dword)
		ST_VIEWPORT_HEIGHT, // (dword)
		ST_VIEWPORT_MINZ, // (float)
		ST_VIEWPORT_MAXZ, // (float)

		ST_COUNT_VIEWPORT
	};
	enum EMiscState
	{
		// single states
		ST_MISC_FVF, // (dword) [0] (uses SetFVF)
		ST_MISC_FVFSIZE, // (dword) [0] (internal; automatically updated when FVF is set)
		ST_MISC_INDICES, // (ptr) [0] (uses SetIndices)
		ST_MISC_PIXELSHADER, // (ptr) [0] (uses SetPixelShader)
		ST_MISC_VERTEXSHADER, // (ptr) [0] (uses SetVertexShader)
		ST_MISC_TEXTUREPALETTE, // (dword) [0] (uses SetCurrentTexturePalette)
		ST_MISC_SCISSORRECT, // (vector left top right bottom) [0] (uses SetScissorRect)
		ST_MISC_NPATCHMODE, // (float) [0] (uses SetNPatchMode)
		//ST_MISC_VERTEXDECL, // (ptr) [0] (uses SetVertexDeclaration) // commented out; not using non-fvf vertex declarations, for compat reasons
		ST_MISC_SRCBLENDOVERRIDE, // (dword) [0] (internal; Graphics3D::EBlendMode mode incase user wants to override default blend mode behavior)
		ST_MISC_DESTBLENDOVERRIDE, // (dword) [0] (internal; Graphics3D::EBlendMode mode incase user wants to override default blend mode behavior)
		ST_MISC_BLTDEPTH, // (float) [0] (internal; depth buffer value used for 2D blt functions)

		// array states
		ST_MISC_TEXTURE, // (ptr) [sampler number] (uses SetTexture)
		ST_MISC_PIXELSHADERCONST, // (vector) [register] (uses SetPixelShaderConstantF)
		ST_MISC_VERTEXSHADERCONST, // (vector) [register] (uses SetVertexShaderConstantF)
		ST_MISC_CLIPPLANE, // (vector) [clip plane index] (uses SetClipPlane)
		ST_MISC_TEXTUREREMAP, // (int) [sampler number] (internal; index of logical texture state that is actually used for this physical sampler)
		ST_MISC_ATLASENABLEDANDBASE, // (vector) [sampler number] (internal; x = 1.0 for atlas enabled or 0.0 for disabled, y = unused, z = base.x, w = base.y)
		ST_MISC_ATLASUV, // (vector) [sampler number] (internal; atlasing vectors, u.x, u.y, v.x, v.y)

		ST_COUNT_MISC,
		ST_COUNT_MISC_SINGLE = ST_MISC_TEXTURE // first of the array states
	};

	typedef std::vector<State> StateVector;
	std::vector<State> mRenderStates;
	std::vector<StateVector> mTextureStageStates;
	std::vector<StateVector> mSamplerStates;
	std::vector<StateVector> mLightStates;
	std::vector<State> mMaterialStates;
	std::vector<StateVector> mStreamStates;
	std::vector<StateVector> mTransformStates;
	std::vector<State> mViewportStates;
	std::vector<StateVector> mMiscStates;

	void InitRenderState(uint32_t inIndex, const std::string& inStateName, uint32_t inHardwareDefaultValue, bool inHasContextDefault=false, uint32_t inContextDefaultValue=0, const char* inValueEnumName=0);
	void InitRenderStateFloat(uint32_t inIndex, const std::string& inStateName, float inDefaultValue);
	void InitTextureStageState(uint32_t inFirstStage, uint32_t inLastStage, uint32_t inIndex, const std::string& inStateName, uint32_t inDefaultValue, bool inHasContextDefault=false, uint32_t inContextDefaultValue=0, const char* inValueEnumName=0);
	void InitTextureStageStateFloat(uint32_t inFirstStage, uint32_t inLastStage, uint32_t inIndex, const std::string& inStateName, float inDefaultValue);
	void InitSamplerState(uint32_t inFirstStage, uint32_t inLastStage, uint32_t inIndex, const std::string& inStateName, uint32_t inDefaultValue, bool inHasContextDefault=false, uint32_t inContextDefaultValue=0, const char* inValueEnumName=0);

	void InitStates();
	void ResetStates();

	static StateValue MakeLightColorStateValue(const Color& inColor, float inAutoScale);
	static Color MakeStateValueLightColor(const State& inState);
	static uint32_t MakeFVFSize(uint32_t inFVF);

public:
	D3DStateManager()
	{}

	virtual void Init() override
	{
		InitStates();
	}
	virtual void Reset() override
	{
		ResetStates();
	}

	void SetRenderState(uint32_t inRS, uint32_t inValue);
	void SetTextureStageState(uint32_t inStage, uint32_t inTSS, uint32_t inValue);
	void SetSamplerState(uint32_t inSampler, uint32_t inSS, uint32_t inValue);
	void SetLightEnabled(uint32_t inLightIndex, bool inEnabled);
	void SetPointLight(int inLightIndex, const SexyVector3& inPos, const Graphics3D::LightColors& inColors, float inRange, const SexyVector3& inAttenuation);
	void SetDirectionalLight(int inLightIndex, const SexyVector3& inDir, const Graphics3D::LightColors& inColors);
	void SetMaterialAmbient(const Color& inColor, int inVertexColorComponent = -1);
	void SetMaterialDiffuse(const Color& inColor, int inVertexColorComponent = -1);
	void SetMaterialSpecular(const Color& inColor, int inVertexColorComponent = -1, float inPower = 0.f);
	void SetMaterialEmissive(const Color& inColor, int inVertexColorComponent = -1);
	void SetStreamSource(uint32_t inStreamIndex, void* inVertexBuffer, uint32_t inOffset, uint32_t inStride, uint32_t inFreq = 1);
	void SetTransform(uint32_t inTS, const SexyMatrix4* inMatrix);
	void SetViewport(uint32_t inX, uint32_t inY, uint32_t inWidth, uint32_t inHeight, float inMinZ, float inMaxZ);
	void SetFVF(uint32_t inFVF);
	void SetIndices(void* inIndexBuffer);
	void SetPixelShader(void* inShader);
	void SetVertexShader(void* inShader);
	void SetCurrentTexturePalette(uint32_t inPaletteIndex);
	void SetScissorRect(const RECT* inRect);
	void SetNPatchMode(float inSegments);
	void SetTexture(uint32_t inSampler, void* inTexture);
	void SetTextureRemap(uint32_t inLogicalSampler, uint32_t inPhysicalSampler);
	void SetPixelShaderConstantF(uint32_t inStartRegister, const float* inConstantData, uint32_t inVector4fCount);
	void SetVertexShaderConstantF(uint32_t inStartRegister, const float* inConstantData, uint32_t inVector4fCount);
	void SetClipPlane(uint32_t inIndex, const float* inPlane);
	void SetBlendOverride(Graphics3D::EBlendMode inSrcBlend, Graphics3D::EBlendMode inDestBlend);
	void SetBltDepth(float inDepth);
	void SetAtlasState(uint32_t inSampler, bool inEnabled, const SexyVector2* inBase = NULL, const SexyVector2* inU = NULL, const SexyVector2* inV = NULL);
	
	uint32_t GetRenderState(uint32_t inRS) const;
	uint32_t GetTextureStageState(uint32_t inStage, uint32_t inTSS) const;
	uint32_t GetSamplerState(uint32_t inSampler, uint32_t inSS) const;
	void GetTransform(uint32_t inTS, SexyMatrix4* inMatrix) const;
	uint32_t GetFVF() const;
	uint32_t GetFVFSize() const;
	void* GetTexture(uint32_t inSampler) const;
	uint32_t GetTextureRemap(uint32_t inLogicalSampler) const;
	void GetLightInfo(int inLightIndex, Graphics3D::LightColors& outColors, SexyVector3& outPos, SexyVector3& outDir, SexyVector3& outAttenuation, float& outRange);
	void GetMaterialInfo(Color& outAmbient, Color& outDiffuse, Color& outSpecular, Color& outEmissive, float& outSpecularPower);
	void GetBlendOverride(Graphics3D::EBlendMode& outSrcBlend, Graphics3D::EBlendMode& outDestBlend);
	float GetBltDepth();
	bool GetAtlasState(uint32_t inSampler, SexyVector2& outBase, SexyVector2& outU, SexyVector2& outV);
};

//============================================================================
//    GLOBAL DATA
//============================================================================
//============================================================================
//    GLOBAL FUNCTIONS
//============================================================================
//============================================================================
//    INLINE CLASS METHODS
//============================================================================
//============================================================================
//    TRAILING HEADERS
//============================================================================

} // namespace Sexy
//****************************************************************************
//**
//**    END HEADER D3DSTATEMANAGER.H
//**
//****************************************************************************
#endif // __D3DSTATEMANAGER_H__
