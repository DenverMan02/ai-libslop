//
//  AdaptorRiftZombossProgress.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/13/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AdaptorRiftZombossProgress__
#define __PlantsVersusZombies2__AdaptorRiftZombossProgress__

#include "Curve.h"
#include "HotUIAdaptor.h"
#include "RtReflectionDelegate.h"

class MapEventItem;

enum RiftZombossLevelSetupButtons
{
    BUTTON_RIFT_ZOMBOSS_PROGRESS_CLOSE,
	BUTTON_RIFT_ZOMBOSS_PROGRESS_CONTINUE
};

typedef RtReflectionDelegate<Delegate0> ButtonDelegate;

struct ZombossProgressDisplayData
{
	ZombossProgressDisplayData() {}
	
	std::vector<bool> Won;
	std::vector<bool> Played;
	
	int GetNumWins();
};

struct AdaptorRiftZombossProgressParams
{
    AdaptorRiftZombossProgressParams()
    : Win(false),
    LevelEnd(false),
    EventEnd(false),
    Attempt(0),
    Difficulty(0)
    {}
    
    int Attempt;
    int Difficulty;
    bool Win;
    bool LevelEnd;
    bool EventEnd;
    ButtonDelegate DismissFunction;
    Sexy::Delegate0 SexyDismissFunction;
	ZombossProgressDisplayData ProgressDisplay;
};

class AdaptorRiftZombossProgress : public HotUIAdaptor
{
public:

	RT_CLASS_DEFINE(AdaptorRiftZombossProgress, HotUIAdaptor, Sexy::RtClass);
	
	AdaptorRiftZombossProgress()
	{
		m_animating = false;
	}
    
    ~AdaptorRiftZombossProgress();
    
    // HUMAN INPUT
	void ButtonDepress(int i_buttonID) override;
    bool OnBackButtonPressed() override;
    
    // NON-HUMAN INPUT
    void SetParams(AdaptorRiftZombossProgressParams& i_params) { m_params = i_params; }
    
    void Update() override;
    void Close();

protected:

	// UI View Link Handling
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;

    void doAccept();
    
private:

    void addRewardList();
	void updateRewardList();
    void clearRewardList();
    
    void startLevel();
    
    AdaptorRiftZombossProgressParams m_params;
    std::vector<class AdaptorMultiPurchaseItem*> m_itemWidgets;
	std::vector<Curve<int>> m_itemQuantityCurves;
	bool m_animating;
};

#endif
