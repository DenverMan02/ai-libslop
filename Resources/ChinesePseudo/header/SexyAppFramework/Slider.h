#ifndef __SLIDER_H__
#define __SLIDER_H__

#include "Widget.h"

namespace Sexy
{

class SliderListener;
class SoundResource;

class Slider : public Widget
{
	RT_CLASS_DEFINE(Slider, Widget, RtClass);
public:
    static const int             kKnob_InsideBar = 0;
    static const int             kKnob_OverlapEnds = 1;
    static const int             kKnob_JustOutsideEnd = 2;
    
public:		
	SliderListener*			mListener;
	double					mVal;
	int						mId;
	Image*					mTrackImage;
	Image*					mThumbImage;

	bool					mDragging;
	int						mRelX;
	int						mRelY;

    Image*                  mUsedFillImage;
    int                     mUsedFillGapFromZero;
    
	bool					mHorizontal;

    float                   mSlideSpeed;
	bool					mSlidingLeft;
	bool					mSlidingRight;

	float 					mKnobRotationRadsPerValUnit;

	bool					mStepMode;
	int						mNumSteps;
	int						mCurStep;
#if SEXY_IS_WWISE_ENABLED
	char const *			mStepSound;
#else
	SoundResource*			mStepSound;
#endif

	Color					mOutlineColor;	// These are only used if no image is specified
	Color					mBkgColor;
	Color					mSliderColor;

	int						mKnobSize; // Also only if no image is specified
    bool					mDrawKnobShadow;
	Point					mKnobShadowOffsets;
	
private:
    float                   mKnobInsideFactor;
    int                     mFillInset;
    
public:
	Slider();
	Slider(Image* theTrackImage, Image* theThumbImage, int theId, SliderListener* theListener);

	virtual void			SetValue(double theValue);
    
    // Sets an image to use to fill used area on the left / top
    void                    SetFillImage(Image* image, int gapFromZero);
    void                    SetFillInset(int x) { mFillInset = x; }

#if SEXY_IS_WWISE_ENABLED
	virtual void			SetStepMode(int num_steps, int cur_step, char const* step_sound=NULL);
#else	
	virtual void			SetStepMode(int num_steps, int cur_step, SoundResource* step_sound=NULL);
#endif

	virtual void			SetStepValue(int cur_step);

	virtual void			Update();
	virtual bool			HasTransparencies();
	virtual void			Draw(Graphics* g);	

	virtual void			MouseMove(int x, int y);
	virtual void			MouseDown(int x, int y, int theClickCount);
	virtual void			MouseDrag(int x, int y);
	virtual void			MouseUp(int x, int y);
	virtual void			MouseLeave();
    
    void                    SetKnobInside(int knobInsideFactor);
	// Rotation to apply to the knob, final rotation = slider_val * knobRotation
	void 					SetKnobRotationRate(float knobRotationRadiansPerSliderValUnit);
	void					SetDrawKnobShadow(bool drawShadow);
	void					SetKnobShadowOffsets(Point offsets);
    
private:
    void                    DrawThreeSliceImage(Graphics *g, Image* image, bool horizontal, Rect extents, bool hasEndCap);
    void                    GetDrawPositions(Rect& barRect, float& knobPos);

};

}

#endif //__SLIDER_H__
