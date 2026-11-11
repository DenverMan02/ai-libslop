//
//  TipsManager.h
//  PlantsVersusZombies2
//
//	Description:
//		It is now attached to BusyAnimationManager.
//	You can consider it as a feature class.
//
//  Created by hanj on 1/20/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TipsManager__
#define __PlantsVersusZombies2__TipsManager__

#include "Singleton.h"
#include "TimeMgr.h"
#include "UIHelper.h"


enum TipsState
{
	TipsInvalid,
	TipsFadeIn,
	TipsDisplay,
	TipsFadeOut
};

class TipsManager : public LazySingleton<TipsManager>
{
public:
	TipsManager();
	~TipsManager();

	void Update();
	void Draw(Graphics* i_g);
	void StartNewTip(const SexyString& i_tipBaseName, int i_baseIndex, int i_tipsCount, const Sexy::Color& i_color);
    void StartNewTipFromAcitvityConfig();
	void StopTip();

private:
	void setState(TipsState i_state);
	void increaseUIGroupRefCount();
	void decreaseUIGroupRefCount();

private:
	SexyString 		m_currentTip;
	TipsState 		m_state;
	pvztime_t		m_fadeStartTime;
	Sexy::Color		m_color;
    int             m_randNum;
    Image *         m_pBannerImg;
    short           m_tipsRefCount;
};

#endif /* defined(__PlantsVersusZombies2__TipsManager__) */
