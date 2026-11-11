/*
 * PlantLevelUpIconWidget.h
 *
 *  Created on: 2014-6-23
 *      Author: jianglc
 */

#ifndef PLANTLEVELUPICONWIDGET_H_
#define PLANTLEVELUPICONWIDGET_H_

#include "PVZ2UIStarLevelUp.h"

enum IconAnimType
{
	ZoomIn,
	ZoomOut,
	FadeIn,
};

class PlantLevelUpIconWidget : public Widget
{
public:

	PlantLevelUpIconWidget(IconData i_data, PVZ2UIStarLevelUp* i_starUi);
    virtual ~PlantLevelUpIconWidget();

    virtual void	Update();
    virtual void	Draw(Sexy::Graphics* i_g);

    void			RequestForUpdate(bool isFastFinish = false);
    void			UpdateComplete(bool isFastFinish = false);

    void			CompleteAllAnim();

protected:
    void 			onAnimStopped(const std::string &i_animName);

private:
    void    InitView();
    SkillPropertySheetPtr	  GetSkillSheet();
    void	InitSkillData(SkillPropertySheetPtr i_sheet);

    void	PlayZoomAnim(bool isZoomIn);

    void	InitAnim();

    void	NotifyAnimEnd(IconAnimType i_type);

    void	CreateArrowEffect();

    void	NotifyColorChange();

    void 	PlayFadeInAnim();

    void	CreateIconEffect();

//    PVZ2UIButton * m_pButtonCallTips;
    //SkillPropertySheetPtr m_pSkillSheet;
    Image * m_pIcon;

    int  m_level;
    bool m_bRefresh;
    bool m_isLevelIcon;
    bool m_isProperty;
    std::string		m_plantName;
    std::string 	m_skillName;

    PVZ2UIStarLevelUp*	m_starUi;

    bool			mAnimRuning;
    float           mCurAnimScale;
    int             mCurAnimFrame;
    float           mFrameTime;
    uint64          mLastFrameTime;
    int				mTotalAnimFrame;
    float			mMinAnimScale;
    float			mMaxAnimScale;
    IconAnimType	mAnimType;

    Effect_PopAnim * m_arrowAnimEffect;
    int				mColorFrameCount;
    bool			mIsColorChange;
    bool			mShouldColorChange;
    float			mCurAnimAlpha;
    float           mMinAnimAlpha;
    float           mMaxAnimAlpha;

    Effect_PopAnim *   m_levelEffectFg;
};


#endif /* PLANTLEVELUPICONWIDGET_H_ */
