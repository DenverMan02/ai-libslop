//
//  PopAnimRig.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 2/12/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  A general purpose animation rig that handles animation sequencing and provides
// feedback to its owner through delegates.
//
//  Can be used on its own, but the ideal usage is through derived rigs that handle
// more complicated behavior and sequencing behind a simple interface.
//
#ifndef PlantsVersusZombies2_PopAnimRig_h
#define PlantsVersusZombies2_PopAnimRig_h

#include <cstddef>
#include <map>
#include <string>

#include "Color.h"
#include "GameObject.h"
#include "PopAnimListener.h"
#include "Rect.h"
#include "RtDb.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"
#include "SexyAppFramework/SexyMatrix.h"
#include "TimeMgr.h"
#include "dtypes.h"

namespace Sexy {
class Graphics;
class Image;
class PAObjectInst;
class PASpriteInst;
class PATransform;
class PopAnim;
class RtId;
class RtSerializeContext;
class SexyVector2;
}  // namespace Sexy

// If true, PopAnimRig will DBG_ASSERT if onInitialized() is not called up the
// entire chain (all the way back to PopAnimRig::onInitialized).
// Turn off for final builds to save a bool and a couple ops per AnimRig
#define VERIFY_FULL_INITIALIZATION (1)

typedef RtWeakPtr<class PopAnimRig> PopAnimRigPtr;

enum AnimHandle
{
	ANIMHANDLE_NONE = -1,
};

enum AnimPlayStyle
{
	PLAY_ONCE,
	PLAY_CONTINUOUS,
};

enum AnimSelectionMethod
{
	// Play only the exact anim label passed in to Play()
	SELECT_EXACT,
	// Play index 0, and when the anim finishes, advance to the next variation in the series
	SELECT_INORDER,
	// Play a random index, and when the anim finishes, play another variation at random
	SELECT_RANDOM_INDEX,
	// Play a random index, and when the anim finishes, play another variation at random, ignoring the most recent variation
	SELECT_RANDOM_INDEX_NOREPEAT,
	// Play a random index from the distribution (weight) table, and when the anim finishes, pick another weighted variation
	SELECT_RANDOM_DISTRIBUTION,
};

class PopAnimRig : public GameObject, public PopAnimListener
{
public:
	RT_CLASS_DEFINE(PopAnimRig, GameObject, RtClass);

	/// Delegate prototypes

	// void AnimStoppedDelegate(const std::string& i_animName);
	//	- Fired when an animation finishes with the exact name of the animation that was played
	typedef Delegate1<const std::string&> AnimStoppedDelegate;
	typedef RtReflectionDelegate<PopAnimRig::AnimStoppedDelegate> AnimStoppedReflectionDelegate;

	// void LoopingAnimContinuedDelegate(const std::string& i_endingAnimName, const std::string& i_newAnimName, int i_animEndCount)
	//	- Fired when a continuous (looping) animation goes on to a new anim in its sequence
	//	- The names of each animation (the one that just ended and the one that just started) are passed in
	//	- Also included is the number of animations that have ENDED so far in this sequence (ie: the first callback will get '1', the second '2', etc.)
	typedef Delegate3<const std::string&, const std::string&, int> LoopingAnimContinuedDelegate;
	typedef RtReflectionDelegate<PopAnimRig::LoopingAnimContinuedDelegate> LoopingAnimContinuedReflectionDelegate;

	// void PopAnimCommandDelegate(const std::string& i_animName, pvztime_t i_time, const std::string& i_command, const std::string& i_params)
	//	- Fired whenever we get an anim command that is not handled by a derived class
	typedef Delegate4<const std::string&, pvztime_t, const std::string&, const std::string&> PopAnimCommandDelegate;
	typedef RtReflectionDelegate<PopAnimRig::PopAnimCommandDelegate> PopAnimCommandReflectionDelegate;


	/// Construction/Destruction

protected:
	PopAnimRig();

public:
	virtual ~PopAnimRig();

	/// Public Interface

	// static CreateInstance
	//	- Creates a new popanimrig
	static PopAnimRig* CreateRig(const PopAnim* i_pam, RtClass* i_class = PopAnimRig::StaticGetClass());
	template<typename T> static T* CreateRig(const PopAnim* i_pam)
	{
		return CreateRig(i_pam, T::StaticGetClass())->template CastChecked<T>();
	}

	static PopAnimRig* CreateRigOutsideTable(const PopAnim* i_pam, RtClass* i_class = PopAnimRig::StaticGetClass());
	template<typename T> static T* CreateRigOutsideTable(const PopAnim* i_pam)
	{
		return CreateRigOutsideTable(i_pam, T::StaticGetClass())->template CastChecked<T>();
	}

	bool Serialize(const RtSerializeContext& i_serializeContext) override;

private:
	void popAnimInitialize(PopAnim* i_pam, bool i_manageDeletion = false);
public:

	void ClearPopAnimCommandDelegate();
	void SetPopAnimCommandDelegate(PopAnimCommandDelegate i_onPopAnimCommand);
    void SetPopAnimCommandDelegate(PopAnimCommandReflectionDelegate i_onPopAnimCommand);
	float GetDrawScale() const;
	void SetDrawScale(const float i_drawScale);

	// PlayAndStop
	//	- Takes a frame label to play and a selection method. Stops when the animation has finished.
	//	- AnimSelectionMethod i_select:
	//		SELECT_EXACT			- Only the exact animation label passed in to Play() will be selected
	//		SELECT_INORDER			- Each animation variation will be played in order ('idle' -> 'idle2' -> 'idle3' -> 'idle', etc)
	//		SELECT_RANDOM_INDEX		- A random variation will be selected each time
	//		SELECT_RANDOM_INDEX_NOREPEAT - A random variation that is NOT the last selected variation will be used
	//	- Any existing delegates will be cleared!
	//	- i_onAnimStopped: If specified, triggered when this animation FULLY finishes
	//	- i_onAnimInterrupted: If specified, triggered if this animation is interrupted before it's fully finished
	//	- Returns a handle to the currently playing anim, this can be used to query whether we're still playing it later
	AnimHandle PlayAndStop(const std::string& i_animLabel, AnimSelectionMethod i_select = SELECT_EXACT, AnimStoppedDelegate i_onAnimStopped = AnimStoppedDelegate());
	AnimHandle PlayAndStop(const std::string& i_animLabel, AnimSelectionMethod i_select, AnimStoppedReflectionDelegate i_onAnimStopped);

	// PlayAndContinue
	//	- Takes a frame label to play and a selection method. When the animation has finished, a new one is selected and played.
	//	- (See PlayAndStop for more information on the selection method)
	//	- Any existing delegates will be cleared!
	//	- i_onAnimContinued : If specified, triggered whenever we finish one animation and play another
	//	- i_onAnimInterrupted : If specified, triggered when another call to Play...() interrupts us
	AnimHandle PlayAndContinue(const std::string& i_animLabel, AnimSelectionMethod i_select = SELECT_EXACT, LoopingAnimContinuedDelegate i_onLoopingAnimContinued = {});
	AnimHandle PlayAndContinue(const std::string& i_animLabel, AnimSelectionMethod i_select, LoopingAnimContinuedReflectionDelegate i_onLoopingAnimContinued);

	// Play
	//	- Bare bones, no delegate Play function.
	virtual AnimHandle Play(const std::string& i_animLabel, AnimPlayStyle i_playStyle = PLAY_ONCE, AnimSelectionMethod i_select = SELECT_EXACT, const std::vector<int> i_randomDistribution = std::vector<int>());

	// BlendTo
	// - Blend to the specified animation
	AnimHandle BlendTo(const std::string& i_animLabel, float i_blendTime, float i_blendDelay, AnimPlayStyle i_playStyle = PLAY_ONCE, AnimSelectionMethod i_select = SELECT_EXACT, AnimStoppedDelegate i_onAnimStopped = {});
	AnimHandle BlendTo(const std::string& i_animLabel, float i_blendTime, float i_blendDelay, AnimPlayStyle i_playStyle, AnimSelectionMethod i_select, AnimStoppedReflectionDelegate i_onAnimStopped);

	// IsAnimActive
	//	- Takes an AnimHandle returned from a previous Play() call
	//	- Returns 'true' if the given handle is still the active animation
	//	- This is the case when the animation is still the last call to Play(), and includes
	//	paused, completed and stopped, looping, etc.
	bool IsAnimActive(AnimHandle i_animHandle) const;

	// IsAnimStringActive
	// - Takes a string for the name of the animation to check
	// - Returns if the last played animation uses this animation string
	bool IsAnimStringActive(const std::string& i_animName);

	// IsAnimFinished
	//	- Takes an AnimHandle returned from a previous Play() call
	//	- Returns 'true' if the given handle is Active and Finished, OR, no longer the active anim
	bool IsAnimFinished(AnimHandle i_animHandle) const;

	// UpdateAnim
	void UpdateAnim(pvztime_t i_t, pvztime_t i_dt);

	// Draw
	void SetRenderTransform(const SexyTransform2D& i_transform);
	void Draw(Graphics* i_g);
	void Draw(Graphics* i_g, const SexyTransform2D& i_transform);
	void DrawSprite(Graphics* i_g, PASpriteInst* i_spriteInst, const SexyTransform2D& i_transform);

	void DrawReplaceLayerWithImage(Graphics* i_g, const SexyTransform2D& i_transform, const std::string& i_layerName, Image* i_replaceImage);
	void DrawReplaceLayerWithImage(Graphics* i_g, const std::string& i_layerName, Image* i_replaceImage);

	// Effects Overlay functions
	void SetAdditiveDraw(bool i_useAdditive);

	// Color override
	Color GetPAMColor() const;
	void SetPAMColor(const Color& i_newColor);
	void SetShaderOverrideColor(const Color& i_newColor);
	void ClearShaderOverrideColor();
	void SetSaturation(float i_state);

	void SetMultiplicativeOverlayColor(const Color& i_newColor);
	void ClearMultiplicativeOverlayColor();

	// Jumps us to a random frame in the currently playing animation
	void RandomizeCurrentAnimFrame();

	// Passed to the audio system whenever we play an animation event keyed sound
	void SetAudioObject(RtWeakPtr<class BoardEntity> i_audioObj);

	/// Public utility functions

	// CalcAnimLength
	//	- Given an animation label name, return the number of flash animation frames
	//	- Returns -1 if the animation is not found
	int CalcAnimLength(const std::string& i_frameLabel);

	// DoesAnimationLabelExist
	//  - Given an animation label name, return if it exists or not.
	bool DoesAnimationLabelExist(const std::string& i_frameLabel);

	// CalcAnimSeconds
	pvztime_t CalcAnimLengthSeconds(const std::string& i_frameLabel);

	// GetCurrentFrameInAnimation
	//  - Returns the current frame in the animation, with 0.0f representing
	//    the start of the animation (instead of the animation's label starting position
	const float GetCurrentFrameInAnimation() const;

	// AdvanceToLastFrameInAnimation
	//  - Sets the current frame in the animation to the last frame.
	void AdvanceToLastFrameInAnimation();

	// SetCurrentFrameInAnimation
	//  - Sets the current frame in the animation, with 0.0f representing
	//    the start of the animation (instead of the animation's label starting position
	void SetCurrentFrameInAnimation(const float i_animationFrame);

	// CalcPlayingAnimLabelName
	//	- Returns the label that was last played in our PAM
	std::string CalcPlayingAnimLabelName() const;

	// SetAnimRateOverride
	//	- Causes us to run at the given rate. 1.0 is normal speed, 2.0 is twice as fast, etc.
	virtual void SetAnimRateOverride(float i_multiplier);
	virtual void ClearAnimRateOverride();

	// CalcLayerTranslation
	//	- Given a layer name, returns the CURRENT offset of that layer from our local origin
	bool CalcLayerTranslation(const std::string& i_layerName, float &o_posX, float &o_posY);
	bool CalcLayerTranslation(const std::string& i_layerName, SexyVector2 &o_pos);
	bool CalcLayerTransformScreenSpace(const std::string& i_layerName, SexyMatrix3 &o_transform);
	PASpriteInst* CalcSymbolRect(const std::string& i_layerName, Sexy::Rect &o_rect);
	virtual void CalcRigDrawingRect(Sexy::Rect &o_rect);

	float ConvertPAMCoordinateToLogicSpace(float i_value);	// Converts a PAM coordinate value to a logic space coordinate value. PAM values are always in the highest resolution the PAM is spit out at, even if you're using it at a lower resolution
	float ConvertPAMCoordinateToScreenSpace(float i_value);	// Converts a PAM coordinate value to a screen space coordinate value. PAM values are always in the highest resolution the PAM is spit out at, even if you're using it at a lower resolution

	/// PopAnimListener interface

	void PopAnimStopped(int i_id) override;
	void PopAnimCommand(int i_id, const std::string& i_command, const std::string& i_param) override;
	void PopAnimPlaySample(const std::string& i_sampleName, int i_pan, double i_volume, double i_numSteps) override;

	bool GetMirrorX() const;
	void SetMirrorX(bool i_mirror);

	void SetForceAdditive(bool i_additive);

	bool SetLayerVisibility(const std::string& i_layerName, bool i_visible);
	void SetLayerVisibility(const std::vector<std::string>& i_layerNames, bool i_visible);
	void SetLayerVisibilityByIndex(const std::vector<std::string>& i_layers, int i_index);
	void SetLayerVisibilityByIndex(const std::vector<std::vector<std::string>>& i_layers, int i_index);
	void SetLayerVisibilityByPercent(const std::vector<std::vector<std::string>>& i_layers, float i_percent);

	void SetPaused(bool i_state);
	void SetDisabled(bool i_state);
	bool GetIsDisabled() const;
	bool IsPlayingAnything() const;

	// External, const PAM accessor. This might be a pipe dream, but try to keep this const
	// and try not to do anything too egregious. I'm watching you.
	inline const PopAnim* GetPAM() const
	{
		return m_pam;
	}

    SexyVector2 GetPAMSize(float fScale = 1.0f) const;
    
	// Helper function to take a PAM, a specified layer name, and a frame number. Will return its transform.
	static PASpriteInst* GetTransformFromPAM(const PopAnim* i_PAM, const std::string i_layerName, int i_frameNumber,  Sexy::SexyMatrix3 &o_transform, PASpriteInst* i_spriteInst = NULL);

	void DebugPrintLayerNames();

	void SetGoldLization(bool i_flag) { m_goldLization = i_flag; }
	bool GetGoldLization() { return m_goldLization; }

protected:

	/// Internal interface
	///		- These are the functions you want to override in your derived class

	virtual void onPostPlayCalled()
	{}

	virtual void onPopAnimInitialized();
	virtual void onAnimStopped();
	virtual void onAnimSequenceContinued();
	virtual void onAnimInterrupted();
	virtual void onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param);

	virtual void onPreDraw(Graphics* i_g);
	virtual void onPostDraw(Graphics* i_g);

	virtual void onUpdate();

	// Internal PAM accessor
	//	- Use with caution, with any luck this will go away some day.
	inline PopAnim* getPAM()
	{
		return m_pam;
	}

	// CalcAnimVariationCount
	//	- Sees how many variations on the given animation label there are in this anim
	//	- e.g.: If the SWF contains frame labels 'idle' 'idle2' 'idle3' and 'idle4', this will return 4
	//	- Will stop if there is a gap. In the example above, if 'idle6' also exists, it will still return 4
	//	- If no labels with the given name exist, returns 0
	int CalcAnimVariationCount(const std::string& i_animLabelBase);

	// CalcVariationLabelName
	//	- Simple helper function to turn a base animation label (eg: 'idle' or 'walk') and
	//	a variation index into an actual animation name
	//	- Follows the general rules we have for animation labeling, i.e. ("idle", 0) --> "idle", ("idle", 1) --> "idle2", etc.
	std::string CalcVariationLabelName(const std::string& i_animLabelBase, int i_variationIndex) const;

    
	// getCurrentTranslation
	//	- Legacy code, GetCurrentTransform function ported from PopAnimPlus
	//	- Hidden to the public as it exposes more stuff than anyone really needs
	PASpriteInst* getCurrentTranslation(const std::string& i_layerName, float &i_posX, float &i_posY, PASpriteInst* i_spriteInst);

	// getCurrentTransform
	//	- Semi-legacy code, a modified version of GetCurrentTransform from PopAnimPlus
	//	- Unlike 'getCurrentTranslation,' this returns the full PATransform for the given layer name
	PASpriteInst* getCurrentTransformPAMSpace(const std::string& i_layerName, PATransform& o_transform, PASpriteInst* i_spriteInst);

	PASpriteInst* getSymbolRect(const std::string &i_layerName, Sexy::Rect& o_rect, PASpriteInst* i_spriteInst, PATransform* i_parentTransform, bool layerFound);

	// getOverlayEffectsColor
	//  - Returns the calculated overlay effects color to use
	virtual const Color getOverlayEffectsColor();

	// hasColorizeOverlay
	//	- Return 'true' if we need to use a pixel shader for our Colorize overlay
	//	- When overriding, derived class should query base and factor that in to its return value
	virtual bool hasColorizeOverlay();

	// hasMultiplicativeOverlay
	//	- Return 'true' if we need to use a pixel shader for our Multiplicative overlay
	//	- When overriding, derived class should query base and factor that in to its return value
	virtual bool hasMultiplicativeOverlay();
	
	float m_saturation;

private:

	/// PopAnimRig private utility functions
	void setPtr(const RtId& i_id);

	// selectNextVariationIndex
	//	- Given our AnimSelectionMethod and last played index, return a (potentially random) new variation index
	int selectNextVariationIndex();

	// clearDelegates
	//	- Clears any stopped/interrupted/etc delegates we have
	void clearPlaybackDelegates();

	void fireInterrupts(const std::string& i_labelToPlay, int i_lastPlayedVariation);
	bool selectVariation(const std::string& i_animLabel, AnimSelectionMethod i_select, std::string& o_labelToPlay, int& o_variationIndex, const std::vector<int> i_randomDistribution = std::vector<int>());

	void internalDrawSprite(Graphics *i_g, PASpriteInst* i_spriteToDrawInst, PASpriteInst* i_spriteInst, PATransform *i_parentTransform);

	/// Private member variables

	PopAnim*		m_pam;				// Our controlled PAM

	/// Serialized
	PopAnimRigPtr	m_selfPtr;

	// Active animation info
	AnimHandle		m_activeAnim;
	std::string		m_activeAnimBaseLabel;		// The base label of our currently active animation
	AnimPlayStyle	m_activeAnimPlayStyle;		// Whether we're playing just this animation or playing a sequence
	int				m_activeAnimSeqEndCount;	// Number of times we've finished an animation in a sequence
	std::vector<int>	m_animRandomDistribution;

	AnimSelectionMethod	m_activeAnimSelectMethod;			// How we selected our current animation
	int					m_activeAnimLastPlayedVariation;	// The variation index of our current animation

	// Passed to the audio system when we play a sound triggered by animation notifications
	RtWeakPtr<class BoardEntity>	m_audioObject;

	// Overlay effect variables
	bool			m_manageDeletion;	// If 'true,' when we are deleted we will delete m_pam as well
	bool 			m_mirrorX;
	bool			m_disabled;
	bool			m_useShaderOverrideColor;
	bool			m_useMultiplicativeOverlayColor;
	Color			m_shaderOverrideColor;
	Color			m_multiplicativeOverlayColor;
	bool			m_goldLization;

	// Delegates
	AnimStoppedDelegate				m_onAnimStopped;
	LoopingAnimContinuedDelegate	m_onLoopingAnimContinued;
	PopAnimCommandDelegate			m_onPopAnimCommand;

	AnimStoppedReflectionDelegate			m_serialOnAnimStopped;
	LoopingAnimContinuedReflectionDelegate	m_serialOnLoopingAnimContinued;
    PopAnimCommandReflectionDelegate        m_serialOnPopAnimCommand;

	// Whenever we do an animation update, we're winding forward a little bit at a time.
	// Before each update STEP, this value is set to the actual game time for the new frame of animation.
	// This is passed along to our m_onAnimStopped and m_onAnimCommand delegates when they are hit.
	pvztime_t		m_virtualStepTime;

#if	VERIFY_FULL_INITIALIZATION
	bool			m_properlyInitialized;
#endif
};

#endif
