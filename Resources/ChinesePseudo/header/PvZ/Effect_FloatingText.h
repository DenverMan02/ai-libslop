//
//  Effect_FloatingText.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Effect_FloatingText_h
#define PlantsVersusZombies2_Effect_FloatingText_h

#include <string>

#include "Color.h"
#include "Point.h"
#include "RtObject.h"
#include "SexyString.h"
#include "SexyVector.h"
#include "StandaloneEffect.h"
#include "TimeLine.h"
#include "TimeMgr.h"

namespace Sexy {
    class Graphics;
    class PrimeTypeface;
}  // namespace Sexy

enum FloatingTextStyle
{
    FTS_None, 		// Default state, has no font and will not draw anything
    
    FTS_FailureOutro,
    FTS_FailureOutroSmaller,
    
    FTS_CannonScoreTracker,
    FTS_CannonScoreFloater,
    FTS_CannonComboMessage,
    
    FTS_LoDAwardFloater,
    
    FTS_ZenGardenTimeBonus,
    
    FTS_OlafStats,
    FTS_GameScore,
    FTS_InGameScore,

    FTS_JoustScoreFloater
};

class Effect_FloatingText : public StandaloneEffect
{
public:
	RT_CLASS_DEFINE(Effect_FloatingText, StandaloneEffect, RtClass);
	
    Effect_FloatingText();
    
	void SetText(const std::string& i_text);
    void SetText(const SexyString &i_text);
    void SetStyle(FloatingTextStyle i_style);
	void SetDuration(const pvztime_t i_duration);
	void SetFadeOutDuration(const pvztime_t i_duration);
	void SetFadeInDuration(const pvztime_t i_duration);
	void SetColor(const Color& i_color) override;
	void SetMotion(const SexyVector3& i_boardSpaceVelocity, const SexyVector3& i_boardSpaceAcceleration);
    void SetScale(float i_scale) override;
	void SetScale(FPoint i_scale);
	void SetFinalScale(FPoint i_scale);
    void SetInitScale(FPoint i_scale);
	void ClearFinalScale();
    void SetTextAsParagraph(Point size);
    
    // Note that the floating text will use PVZ_T() to sample these curves
    void SetPositionCurve(const CurveSequence_SexyVector3& i_positionCurve, bool i_inScreenSpace);
    void SetScaleCurve(const CurveSequence_SexyVector3& i_scaleCurve);
	
protected:
	virtual void onInitialized() override;
	virtual void onUpdate() override;
	virtual void onDraw(Graphics* i_g) override;

private:
    void DoEffectTimeline(char& alphaByte, FPoint& scale);
    void ensureFontSetFromStyle();
    
    // Serialized values
	pvztime_t m_createdTime;
	pvztime_t m_destroyTime;
	pvztime_t m_fadeOutDuration;
	pvztime_t m_fadeInDuration;
	
	SexyString m_text;
	Color m_color;
	
    FPoint m_initScale;
	FPoint m_scale;
	FPoint m_finalScale;
    bool m_scaleInitTransition;
	bool m_scaleFinalTransition;
    
    Point m_paragraphSize;
    bool m_isParagraph;
	
	SexyVector2 m_screenSpaceVelocity;
	SexyVector2 m_screenSpaceAcceleration;
    
    CurveSequence_SexyVector3 m_positionCurve;
    CurveSequence_SexyVector3 m_scaleCurve;
    bool m_positionCurveIsScreenSpace;
	
    FloatingTextStyle m_style;
    
    // Transient values
    PrimeTypeface* m_font;
    PrimeTypeface* m_outlineFont;
};
#endif
