//
//  PowerupManager.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 12/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PowerupManager__
#define __PlantsVersusZombies2__PowerupManager__

#include <string>
#include "Graphics.h"
#include "GameSubSystem.h"
#include "BasePowerup.h"
#include "MagentoService.h"		//PVZ2_CHINESE_START

class LevelPowerupSet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(LevelPowerupSet, PropertySheetBase, RtClass);

	std::vector<std::string> Powerups;
};

class PowerupManager : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(PowerupManager, GameSubSystem, RtClass);
	
	PowerupManager();
	//PVZ2_CHINESE_START
    ~PowerupManager();
    void OnLevelLoadComplete();
	//PVZ2_CHINESE_END
	virtual void Update() override;

	void SelectPowerup(const class PowerupType* i_powerupType, const bool i_ignoreCost=false);

	void ActivatePowerup();
	void DeactivatePowerup();
	void CancelActivePowerup();

    void AddPowerup(const std::string &i_powerupName, bool i_isLocked = false);
	void AddConveyorPowerup(const std::string &i_powerupName);
	void RemovePowerup(const std::string &i_powerupName);

	void RemoveAllPowerups();

	void SetMaxPurchasesAllowed(const int8 i_maxPurchases);

	void AddToRenderQueue(class RenderQueue* i_queue) override;
	
	void ShowWidgets();

	BasePowerup* GetSelectedPowerup() const { return m_selectedPowerup; }
	BasePowerup* GetActivePowerup() const { return m_activePowerup; }

	BasePowerup* GetBasePowerup(const class PowerupType* i_powerupType);
    
    const std::vector<RtWeakPtr<BasePowerup>>& GetPowerups() const;
    
    //PVZ2_CHINESE_START
    void LoadPropsFromMagento(class PowerupType* i_powerupType);
    int GetPowerUPTimes() const { return m_powerupTimes; }

    void OnServerGemCallBack(const bool& i_Success);

    int	 mCacheGemCost = 0;

    bool IsBlock();
    int	 mCacheConnectServer;
    
    int GetCurrentPowerCost(BasePowerup* powerup);
    int GetPowerAdditionCost(BasePowerup* powerup);
    int GetCurrentPowerAdditionDamage(BasePowerup* powerup);
	//PVZ2_CHINESE_END
    void AddDefaultPowerupsForLevel();
    
public:
    void onUseGemFinished(bool success);
    
private:
    void OnBuyItemFinish(class MsgResultInfo* io_result, const class S2C_ICloud_GetConsumeGemInfo* pInfo, const class S2C_PlayerInfo* pGemChanged);
	void onDrawSelectionOnBoard(Sexy::Graphics *i_g);
	void onDrawActivePowerup(Sexy::Graphics *i_g);
    void onNetworkError(int erroId, const std::string& requestID);

	void onUseGemCallback(const bool& success);

	void addPowerupSet(const std::string& levelPowerupSet);
    
	/// Serialized values
	std::vector<RtWeakPtr<BasePowerup> > m_powerups;
	RtWeakPtr<BasePowerup> m_selectedPowerup;
	RtWeakPtr<BasePowerup> m_activePowerup;

	bool m_ignoreCost;
    
	//PVZ2_CHINESE_START
	int m_powerupTimes;
	//PVZ2_CHINESE_END
};

namespace Message
{
	void PowerupSelected(BasePowerup* i_powerup);
	void PowerupActivated(BasePowerup* i_powerup, int i_cost,int costFreeGems);
	void PowerupDeactivated(BasePowerup* i_powerup);
	void PowerupDeselected(BasePowerup* i_powerup);
	void PowerupEquipped(const std::string& i_powerupName);
}

#endif /* defined(__PlantsVersusZombies2__PowerupManager__) */
