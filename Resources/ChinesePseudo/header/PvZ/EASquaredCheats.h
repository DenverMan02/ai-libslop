//
//  EASquaredCheats.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 3/18/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EASquaredCheats__
#define __PlantsVersusZombies2__EASquaredCheats__

#include "AdProviderFactory.h"

namespace EASquaredCheats
{
	void DrawEA2Diagnostic(Graphics* i_g, Sexy::Rect i_drawRect);
	void FakeShowAd();
	void FakeEndAd();
    
#pragma mark
#pragma mark SuperSonic
    void LabelSuperSonicFolder(std::string &o_label);
    void LabelSuperSonicEnabled(std::string &o_label);
    void LabelSuperSonicDemoCampaigns(std::string &o_label);
    void CycleSuperSonicEnabled();
    void ToggleSuperSonicDemoCampaigns();
	
#pragma mark
	void labelAdProviderFolder(const std::string& i_providerName, bool i_enabled, bool i_usingDemoCampaigns, std::string& o_label);
	void labelAdProviderEnabled(bool i_configValue, AdProviderEnabledOverrideState i_overrideThisSession, AdProviderEnabledOverrideState i_overrideNextSession, std::string& o_label);
	void labelToggleDemoCampaigns(bool i_usingDemoThisSession, bool i_usingDemoNextSession, std::string& o_label);
	void cycleAdProviderEnabled(const std::string& i_key);
	void toggleUserPrefsBool(const std::string& i_key);
};

#endif /* defined(__PlantsVersusZombies2__EASquaredCheats__) */
