//
//  LevelOfTheDayRewardBanner.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 10/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LevelOfTheDayRewardBanner__
#define __PlantsVersusZombies2__LevelOfTheDayRewardBanner__

#include "RtObject.h"
#include "SexyString.h"
#include "ResourceHelpers.h"
#include "TimeLine.h"

#include "Widget.h"

namespace Sexy {
class Graphics;
class Image;
class PrimeTextWidget;
}  // namespace Sexy

class LevelOfTheDayRewardBanner : public Sexy::Widget
{
public:

	LevelOfTheDayRewardBanner();
	~LevelOfTheDayRewardBanner();

	void Initialize(const std::string& i_imageName, const SexyString& i_headingText, const SexyString& i_mainText, const Color& i_fontColor);
	
	void Update() override;
	void Draw(Sexy::Graphics* i_g) override;

	void AnimateDown();

private:
	RtWeakPtr<Sexy::Image> m_bannerImage;
	PrimeTextWidget* m_heading;
	PrimeTextWidget* m_description;
	
	CurveSequence<float> m_movementSequence;
	bool m_animating;
};

class LevelOfTheDayRewardFooter : public Sexy::Widget
{
public:
	
	LevelOfTheDayRewardFooter();
	~LevelOfTheDayRewardFooter();
	
	void Initialize(const std::string& i_holiday, const std::string& i_imageName, const SexyString& i_headingText, const SexyString& i_mainText, const Color& i_fontColor);
	
	void Update() override;
	void Draw(Sexy::Graphics* i_g) override;
	
	void AnimateUp();
	
private:
	RtWeakPtr<Sexy::Image> m_bannerImage;
	RtWeakPtr<Sexy::Image> m_floatingBackground;
	PrimeTextWidget* m_heading;
	PrimeTextWidget* m_description;
	
	CurveSequence<float> m_movementSequence;
	bool m_animating;
    bool m_use3SliceForFooterImage;
};

#endif /* defined(__PlantsVersusZombies2__LevelOfTheDayRewardBanner__) */
