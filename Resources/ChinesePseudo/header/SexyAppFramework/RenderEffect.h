#pragma once
#ifndef __RENDEREFFECT_H__
#define __RENDEREFFECT_H__
//****************************************************************************
//**
//**  File     :  RENDEREFFECT.H
//**  Summary  :  Header - Low-level rendering effect definitions
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
#include "Common.h"
#include "Graphics.h"
#include "ResourceTypes.h"

namespace Sexy {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
class RenderEffectDefinition;
class RenderEffect;
namespace ResourceInfoTypes { class RenderEffectRes; }

// forward declarations
class RenderDevice3D;

/*
	RenderEffectDefinition

	This represents the resource definition of an effect, as supplied by the
	resource generator.  Its contents are opaque, however it can be supplied
	to a render device at runtime to create a RenderEffect usable with that device.
	Game developers themselves should rarely if ever have to mess with the contents
	of this structure directly within their game code; it's intended to be a
	framework implementation detail.
*/
class RenderEffectDefinition
: public BaseResource
{
public:
	RT_CLASS_DEFINE(RenderEffectDefinition, BaseResource, ResourceClass);
	typedef ResourceInfoTypes::RenderEffectRes InfoClass;

public:
	std::vector<uchar> mData;
	std::string mSrcFileName;
	std::string mDataFormat;

	bool LoadFromMem(uint32 inDataLen, const void* inData, const char* inSrcFileName, const char* inDataFormat);
	bool LoadFromFile(const char* inFileName, const char* inSrcFileName);
};

/*
	RenderEffect
*/
class RenderEffect
{
protected:
	// Destructor is protected, as these are not intended to be deleted in game code.
	// The render device that creates an effect will handle its deletion.
	virtual ~RenderEffect() {}

public:
	typedef void* HRunHandle;

	// General effect information
	virtual RenderDevice3D* GetDevice() = 0; // get the render device this effect is bound to
	virtual RenderEffectDefinition* GetDefinition() = 0; // get the source definition for this effect; may be null if code-driven

	// Set a float parameter (scalar float, vector, or matrix) to a given value; the parameter
	// may be used by any technique within the effect.
	virtual void SetParameter(const std::string& inParamName, const float* inFloatData, uint32 inFloatCount) = 0;
	inline void SetFloat(const std::string& inParamName, float inValue) { SetParameter(inParamName, &inValue, 1); }
	inline void SetVector4(const std::string& inParamName, const float* inValue) { SetParameter(inParamName, inValue, 4); }
	inline void SetVector3(const std::string& inParamName, const float* inValue)
	{
		float temp[4];
		temp[0] = inValue[0];
		temp[1] = inValue[1];
		temp[2] = inValue[2];
		temp[3] = 1.0f;
		SetVector4(inParamName, temp);
	}
	
	//SetMatrix has to be virtual because matrices have to be transposed on some platforms
	virtual void SetMatrix(const std::string& inParamName, const float* inValue) { SetParameter(inParamName, inValue, 16); }

	// Get a float parameter (scalar float, vector, or matrix) by standard semantic.  Generally only used
	// during code-side workarounds when shaders are unavailable.
	virtual void GetParameterBySemantic(uint32/*EStandardConstantSemantic*/ inSemantic, float* outFloatData, uint32 inMaxFloatCount) = 0;

	// Set the current technique by name.  If inCheckValid is true, a fallback chain
	// may be followed, validating the technique and its fallbacks against the device
	// until a usable fallback is found and set.  If inCheckValid is false, then
	// no validation is performed and the technique with the given name is used directly.
	// Note that if the effect has a technique named "Default" (case-sensitive), then it
	// will be set as the current technique when the effect is first constructed.
	virtual void SetCurrentTechnique(const std::string& inName, bool inCheckValid = true) = 0;

	// Get the name of the current technique.  This can be used after setting a technique
	// by name with validation enabled, if you wish to find which technique was actually used
	// within the fallback chain.
	virtual std::string GetCurrentTechniqueName() = 0;

	// Run the current technique.  This will provide a "run handle" which is used for
	// subsequent calls to Begin, BeginPass, EndPass, and End.  The context handle will be
	// bound to a specific render context on the backing device; if the default (null) is used,
	// then the context will be the device's current context.

	// Begin using the current technique for drawing; returns the number of passes to iterate.
	// This method also provides a "run handle" which is then used for subsequent calls to
	// BeginPass, EndPass, and End.  The run handle will be bound to a specific render context
	// of the device which is provided; if the default (null) context is given, then the device's
	// current context will be used.  All device states affected by the technique will then be
	// applied within this context.
	virtual int Begin(HRunHandle& outRunHandle, const HRenderContext& inRenderContext = HRenderContext((void*)0)) = 0;
	
	// Begin a specific pass of the current technique, by zero-based pass index.  At a minimum,
	// this should internally call PushState on the device, before changing any state.
	virtual void BeginPass(const HRunHandle& inRunHandle, int inPass) = 0;
	
	// Finish a specific pass of the current technique.  At a minimum, this should internally call
	// PopState on the device, to restore previous state.
	virtual void EndPass(const HRunHandle& inRunHandle, int inPass) = 0;
	
	// Finish using the current technique for drawing; must be called as a pair with Begin().
	// The run handle will become invalid after this call.
	virtual void End(const HRunHandle& inRunHandle) = 0;

	// Determine whether a given pass of the current technique uses a vertex or pixel
	// shader; used for additional code-side processing of input vertices etc.
	virtual bool PassUsesVertexShader(int inPass) = 0;
	virtual bool PassUsesPixelShader(int inPass) = 0;
};

/*
	RenderEffectAutoState
*/
class RenderEffectAutoState
{
protected:
	RenderEffect* mEffect;
	RenderEffect::HRunHandle mRunHandle;
	int mPassCount;
	int mCurrentPass;

public:
	RenderEffectAutoState(Graphics* inGraphics = NULL, RenderEffect* inEffect = NULL, int inDefaultPassCount = 1)
	: mEffect(inEffect)
	, mPassCount(inDefaultPassCount)
	, mCurrentPass(0)
	{
		if (!mEffect)
			return;
		mPassCount = mEffect->Begin(mRunHandle, inGraphics ? inGraphics->GetRenderContext() : HRenderContext((void*)NULL));
		if (mCurrentPass < mPassCount)
			mEffect->BeginPass(mRunHandle, mCurrentPass);
	}
	~RenderEffectAutoState()
	{
		if (!mEffect)
			return;
		if (mCurrentPass < mPassCount)
			mEffect->EndPass(mRunHandle, mCurrentPass);
		mEffect->End(mRunHandle);
	}
	void Reset(Graphics* inGraphics = NULL, RenderEffect* inEffect = NULL, int inDefaultPassCount = 1)
	{
		if (mEffect)
		{
			if (mCurrentPass < mPassCount)
				mEffect->EndPass(mRunHandle, mCurrentPass);
			mEffect->End(mRunHandle);
		}
		mEffect = inEffect;
		mPassCount = inDefaultPassCount;
		mCurrentPass = 0;
		if (mEffect)
		{
			mPassCount = mEffect->Begin(mRunHandle, inGraphics ? inGraphics->GetRenderContext() : HRenderContext((void*)NULL));
			if (mCurrentPass < mPassCount)
				mEffect->BeginPass(mRunHandle, mCurrentPass);
		}
	}

	void NextPass()
	{
		if (mEffect)
		{
			if (mCurrentPass < mPassCount)
				mEffect->EndPass(mRunHandle, mCurrentPass);
		}
		++mCurrentPass;
		if (mEffect)
		{
			if (mCurrentPass < mPassCount)
				mEffect->BeginPass(mRunHandle, mCurrentPass);
		}
	}
	inline bool IsDone() const { return mCurrentPass >= mPassCount; }

	bool PassUsesVertexShader() { return mEffect ? mEffect->PassUsesVertexShader(mCurrentPass) : false; }
	bool PassUsesPixelShader() { return mEffect ? mEffect->PassUsesPixelShader(mCurrentPass) : false; }

	inline operator bool () const { return !IsDone(); }
	inline bool operator ! () const { return IsDone(); }
	inline RenderEffectAutoState& operator ++ (void) { NextPass(); return *this; }
	inline RenderEffectAutoState& operator ++ (int) { NextPass(); return *this; } // technically this isn't proper postfix behavior, but I doubt it matters for our usage
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
//**    END HEADER RENDEREFFECT.H
//**
//****************************************************************************
#endif // __RENDEREFFECT_H__
