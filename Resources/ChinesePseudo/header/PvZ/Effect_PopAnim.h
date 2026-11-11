//
//  Effect_PopAnim.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/19/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Effect_PopAnim_h
#define PlantsVersusZombies2_Effect_PopAnim_h

#include "StandaloneEffect.h"
#include "PopAnimRig.h"

struct AnimationSequenceEntry
{
public:
	AnimationSequenceEntry()
		: SelectionMethod(SELECT_EXACT), LoopingDuration(0.f)
	{}

	AnimationSequenceEntry(const std::string& i_animLabel, AnimSelectionMethod i_selectionMethod, pvztime_t i_loopingDuration)
		: AnimationLabel(i_animLabel), SelectionMethod(i_selectionMethod), LoopingDuration(i_loopingDuration)
	{}

	std::string 			AnimationLabel;
	AnimSelectionMethod 	SelectionMethod;
	pvztime_t 				LoopingDuration;
};

struct AnimationSequence
{
public:
	void AddSingleAnimation(const std::string& i_animLabel, AnimSelectionMethod i_selectMethod = SELECT_EXACT);
	void AddLoopingAnimation(const std::string& i_animLabel, pvztime_t i_duration = PVZ_EOT(), AnimSelectionMethod i_selectMethod = SELECT_EXACT);
	void AddDelay(pvztime_t i_duration);

	void Clear();

	int GetEntryCount() const;
	const AnimationSequenceEntry& GetEntry(int i_idx);

	std::vector<AnimationSequenceEntry> m_animationEntries;
};

class Effect_PopAnim : public StandaloneEffect
{
public:
	RT_CLASS_DEFINE(Effect_PopAnim, StandaloneEffect, RtClass);
    
    Effect_PopAnim();
	virtual ~Effect_PopAnim();

	void CreatePopAnimRig(const std::string& i_popAnim, const std::string& i_animRigClass);
	void CreatePopAnimRig(PopAnim* i_popAnim, RtClass* i_popAnimRigClass = NULL);
	PopAnimRig* GetPopAnimRig() const { return m_rig; };
	PopAnimRigPtr GetPopAnimRigPtr() const { return m_rig; };

	virtual void SetColor(const Color& i_color) override;
    
    void SetMultiplicativeOverlayColor(const Color& i_newColor);
    void ClearMultiplicativeOverlayColor();
    void SetShaderOverrideColor(const Color& i_newColor);
    void ClearShaderOverrideColor();
	
	// TODO -- Manual art offset
	// void SetArtOffset(const SexyVector2& i_artOffset);
	void SetCentered(bool i_centered);
    bool IsCentered() const { return (m_xFocusFraction == 0.5f && m_yFocusFraction == 0.5f); }
    void SetCenteredOnArtLocationInFractionOfArtDimensions(float i_xFractionCenter, float i_yFractionCenter);
	
	virtual void SetScale(float i_scale) override;
	virtual void SetScale(float i_x, float i_y);
	float GetXScale() { return m_xScale; }
	float GetYScale() { return m_yScale; }
	
	void SetOrientation(float i_radians);
	void SetOrientation(const SexyVector2& i_facing);
	
	void PlaySingleAnimation(const std::string& i_animLabel, AnimSelectionMethod i_selectMethod = SELECT_EXACT);
	void PlayLoopingAnimation(const std::string& i_animLabel, pvztime_t i_duration = PVZ_EOT(), AnimSelectionMethod i_selectMethod = SELECT_EXACT);
	void PlaySingleAndLoopingAnimation(const std::string& i_animLabel, const std::string& i_animLabel2, pvztime_t i_duration = PVZ_EOT(), AnimSelectionMethod i_selectMethod = SELECT_EXACT);
	void PlayAnimationSequence(const AnimationSequence& i_animSequence);
    
    void SetSkewTransform(SexyTransform2D i_transform);
    void SetTranslation(SexyVector2 i_translation);
    SexyVector2 GetDimensions() override;
    
    void SetPopAnimDelegates();

    void SetUpdateAnim(bool i_update) { m_updateAnim = i_update; }
    bool GetUpdateAnim() { return m_updateAnim; }
	
protected:
	virtual void onInitialized() override;
	virtual void onOriginChanged() override;
	virtual void onUpdate() override;
	virtual void onDraw(Graphics* i_g) override;
	
	virtual void onAnimStopped(const std::string& i_animLabel);
    
    virtual void OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) { }
    
	void setRigTransform();
	
	void clearAnimSequence();
	void startAnimSequence();
	void advanceAnimSequence();
    
private:
    
    void RecAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string &i_animCommand, const std::string &i_animCommandParam);

private:
	PopAnimRigPtr 		m_rig;
	
	AnimationSequence 	m_animSequence;
	int					m_animSequenceCurrentIndex;
	pvztime_t			m_animSequenceCurrentIndexStartTime;
	
	float		m_xFocusFraction;
	float		m_yFocusFraction;
	float		m_xScale;
	float		m_yScale;
	float		m_orientation;
    SexyVector2 m_translation;
    SexyMatrix3	m_skewTransform;
    bool 		m_updateAnim;
};

namespace Message
{
	void NotifyPopAnimCreated(class Effect_PopAnim* i_anim);
}

#endif
