//
//  ActiveChristmasLotteryTab.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-12-7.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ActiveChristmasLotteryTab__
#define __PlantsVersusZombies2__ActiveChristmasLotteryTab__

#include "PlatformAutodetect.h"
#include "ActiveCenterTab.h"
#include "Effect_PopAnim.h"
#include "ActivityConfig.h"

class ActiveChristmasLotteryTab : public ActiveCenterTabBase
{
public:
	ActiveChristmasLotteryTab(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~ActiveChristmasLotteryTab();
    
    std::string GetTabContainerImageName() const override
    {
        return "IMAGE_UI_ACTIVETABCENTER_LOTTERY_BG";
    }
    SexyString  GetGoToButtonTitle() override;
    
	virtual void		OnButtonClicked(int i_id) override;
	virtual void		SetSelect(bool setting) override;
	virtual void        DrawForeground(class Sexy::Graphics* i_g) override;
	virtual void		Update() override;
	
protected:
	void                setupScreen();
    
    void                DoLottery();
    void                PickGachaReward(const std::vector<GachaRewardItem>& rewards);
    
    void                onAnimCommand(const std::string& i_animLabel,
                                      pvztime_t i_timeStamp,
                                      const std::string& i_animCommand,
                                      const std::string& i_animCommandParam);
    
    void                onGotChristmasLottery(bool i_success,int32 i_chipid,int32 i_count);
    
private:
    Rect                m_contentRect;
    Effect_PopAnim *    m_popAnimEffect;
    bool                m_bButtonCanClicked;
    
    ActivityTimeStatus  m_StatusActivity;
    
    time_t              m_endTime;
    SexyString          m_daysDes;
    SexyString          m_timeDes;
    
    int32               m_chipid;
    int32               m_count;
};

#endif /* defined(__PlantsVersusZombies2__ActiveChristmasLotteryTab__) */
