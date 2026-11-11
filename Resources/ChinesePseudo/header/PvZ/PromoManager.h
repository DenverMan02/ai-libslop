//
//  PromoManager.h
//  PlantsVersusZombies2
//
//  Created by Alex Stajos on 4/4/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PromoManager__
#define __PlantsVersusZombies2__PromoManager__

#include "AdPlacementManager.h"

class PromoManager
{
    
public:
    PromoManager();
    ~PromoManager();

    void FetchAd(std::string i_adPlacement = "");
    bool DoCurrentAdAction();
    bool ShouldShowAd();
    bool IsAdReady();
    void ReleaseAd();
    
    Sexy::Image* GetAdImage();
	Sexy::StructuredData GetSentParams() {return m_adParams;}

private:
    void promoResponseHandler(const Sexy::AdResponse& inAdResponse);
    void prepareAdServerKeyValuePairs(Sexy::StructuredData& ioAdSelectionKeyValuePairs);
	void onFetchAction();
	void onGameLost();
	void onStarModuleGameplayEnded();
	void onGameplayEnded();
    
    int				getHighestLevelCompleted();
	int				getLastLevelCompleted();
	int				getStarCountLastLevel();
	std::string		getLastPlayedWorld();
    time_t			getTimeSinceProfileCreated();
    time_t			getTimeSinceLastSession();
    time_t			getTimeSinceLastPurchase();
    
    Sexy::AdResponse* mCurrentAdResponse;
	
	Sexy::StructuredData m_adParams;
	bool				 m_fetchingAd;
	bool				 m_lostLastGame;
};

#endif /* defined(__PlantsVersusZombies2__PromoManager__) */
