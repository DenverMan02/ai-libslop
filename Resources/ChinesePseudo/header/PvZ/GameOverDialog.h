//
//  GameOverDialog.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 5/1/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GameOverDialog__
#define __PlantsVersusZombies2__GameOverDialog__

#include "PVZ2UIDialog.h"
#include "TimeMgr.h"
#include "core.h"

enum GameOverDialogType
{
    PVZ_BEGIN_ENUM(GAME_OVER_DIALOG_),
    GAME_OVER_DIALOG_None,
    GAME_OVER_DIALOG_Brain,
    GAME_OVER_DIALOG_NoBrain,
    GAME_OVER_DIALOG_Airship,
    PVZ_END_ENUM(GAME_OVER_DIALOG_),
};

class GameOverDialog : public PVZ2UIDialog
{
public:
	GameOverDialog(GameOverDialogType gameOverDialogType);
	virtual ~GameOverDialog();
    
    virtual void Draw(Sexy::Graphics* i_g);
    
    void SetTaskFailed(bool i_taskfailed);
    
protected:
    virtual void LayoutElements();
    virtual Rect GetButtonRegion();

private:
    void InitBrain();
    
	void StartImageFade(float time, uint8 alphaStart, uint8 alphaEnd);
    void UpdateBrainFade();
    void UpdateFade();
    
    void StartImageScale(float duration, float scaleStart, float scaleEnd);
    void UpdateBrainScale();
    void UpdateScale();

    uint8 mImageFadeAlphaStart;
    uint8 mImageFadeAlphaEnd;
    uint8 mImageFadeCurrent;

    pvztime_t mFadeStartTime;
    pvztime_t mFadeEndTime;
    
//PVZ2_CHINESE_BEGIN
    float mImageScaleStart;
    float mImageScaleCurrent;
    float mImageScaleEnd;
    
    pvztime_t mScaleStartTime;
    pvztime_t mScaleEndTime;
//PVZ2_CHINESE_END
    
    bool mShowBrain;
    bool mTaskFailed;
    bool mAirship;
};


#endif /* defined(__PlantsVersusZombies2__GameOverDialog__) */
