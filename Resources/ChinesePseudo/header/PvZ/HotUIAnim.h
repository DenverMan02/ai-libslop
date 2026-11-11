//
//  HotUIAnim.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 8/4/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIAnim__
#define __PlantsVersusZombies2__HotUIAnim__

#include <string>

#include "HotUIWidget.h"
#include "HotUIImage.h"
#include "PopAnimRig.h"

namespace Sexy
{
	class Graphics;
}
class PopAnimRig;

class HotUIAnim : public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUIAnim, HotUIWidget, RtClass);
	HotUIAnim();
	virtual ~HotUIAnim();

	void	Update() override;
	AnimHandle	PlayAndStop(const std::string& i_animLabel, AnimSelectionMethod i_select = SELECT_EXACT, PopAnimRig::AnimStoppedDelegate i_onAnimStopped = {});
	AnimHandle	PlayAndContinue(const std::string& i_animLabel, AnimSelectionMethod i_select = SELECT_EXACT, PopAnimRig::LoopingAnimContinuedDelegate i_loopingAnimContinued = {});
    
    std::string GetDefaultAnimation() const;
    
	PopAnimRig*	GetAnimRig() { return m_popAnimRig; }
	
	void		SetScaleOverride(float i_scale);
	float		GetScaleOverride() { return m_scaleOverride; }

	void 		SetImageGrayscale(bool i_grayscale) { m_drawGrayscale = i_grayscale; }
	bool 		GetImageGrayscale() { return m_drawGrayscale; }

protected:

	void	onInitializeWidget() override;
	void	onLayoutFinalized() override;
	void	onReadyForOverrideScale();
	void    layoutAnim();

	void	onDraw(Graphics* i_g) override;

	virtual Point GetAnimOffset() { return {0, 0}; }

	SexyTransform2D m_rigTransform;
	class PopAnimRig*		m_popAnimRig;
private:
	float			m_scaleOverride;
	bool			m_drawGrayscale;
};

enum HotUIAnimPlayStyle
{
    HUIAPS_PlayAndContinue,
    HUIAPS_PlayAndStop,
    HUIAPS_None,
};

class HotUIAnimProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIAnimProperties, HotUIWidgetProperties, RtClass);

	RtClass* GetWidgetClass() const override
	{
		return HotUIAnim::StaticGetClass();
	}

	HotUIAnimProperties()
	{
		OffsetPercentX = 0;
		OffsetPercentY = 0;
		ScaleOverride = 1;
		PopAnimRigClass = "PopAnimRig";
        PlayStyle = HUIAPS_PlayAndContinue;
	}

	std::string			PopAnimName;
	std::string			PopAnimRigClass;
	float				OffsetPercentX;
	float				OffsetPercentY;
	float				ScaleOverride;
	std::string			InitialAnimationName;
	std::vector<std::string>	AnimLayersToDisable;
	UIImageDrawStyle	DrawStyle;
    HotUIAnimPlayStyle  PlayStyle;
};

#endif /* defined(__PlantsVersusZombies2__HotUIAnim__) */
