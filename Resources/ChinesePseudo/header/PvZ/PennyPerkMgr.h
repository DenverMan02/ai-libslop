//
//  PennyPerkMgr.hpp
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 6/4/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef PennyPerkMgr_h
#define PennyPerkMgr_h

#include "BasicPerks.h"
#include "Singleton.h"

class AdaptorPerkSelectionDialog;

namespace Message
{
	void PerkSelected(std::string& i_perkName, bool i_needsAnimation, Point& i_startPoint);
	void PerkDeselected(std::string& i_perkName);
	void PerkScreenCreated(AdaptorPerkSelectionDialog* i_perkScreen);
	
	//Metrics
	void PerksFinalized();
	void PerksPurchased(int i_gemsSpent, const std::string& i_perkTypes, const char* i_source);
}

struct PerkData
{
	PerkData()
	{
		PropsPtr = PennyPerkPropertiesPtr();
		PerkLevel = 0;
	}
	PennyPerkPropertiesPtr PropsPtr;
	int PerkLevel;
};

class PennyPerkMgr : public LazySingleton<PennyPerkMgr>
{
public:
	PennyPerkMgr();
	virtual ~PennyPerkMgr();
	
	std::vector<PerkData> GetUnlockedPerkList();
	std::vector<PerkData> GetSelectedPerkList();
	void SelectPerk(std::string i_perkName, bool i_needsAnimation = false, Point i_startPoint = Point());
	void DeselectPerk(std::string i_perkName);
	void DeselectAllPerks();
	SexyString GetSelectedPerkWarnings(MapEventSubType i_levelSubType);
	bool IsPerkSupportedInLevelType(PennyPerkPropertiesPtr i_perk, MapEventSubType i_levelSubType);
	GemCurrency GetTotalCostOfSelectedPerks();
	
	int CalcNextPerkLevelThreshold(std::string i_perkName);
	int GetCurrentPerkLevel(std::string i_perkName);
	PerkData CreatePerkData(std::string i_perkName, int i_level);
	
	std::string CheatGetPerkInfoString();
	bool CheatIsPerkToggleActive(std::string i_perkClassName);
	
	void SyncPerkList(const std::vector<struct RiftPerkData>& i_list);
	std::vector<PerkData> GetSelectedPerks() { return m_selectedPerks; }

private:
	void createUnlockedPerkList(int i_difference);
	void addUnlockedPerk(std::string i_perkName, int i_level);
	
	std::vector<PerkData> m_unlockedPerkList;
	std::vector<PerkData> m_selectedPerks;
};

#endif /* PennyPerkMgr_h */
