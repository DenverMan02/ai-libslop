//
//  LawnMowerModule.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/16/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LawnMowerModule_h
#define PlantsVersusZombies2_LawnMowerModule_h

#include "LevelModule.h"
#include "GameEventMgr.h"

class LawnMower;

namespace Message
{
	void BuyItemOK(int i_type);
	void BuyItemCancel(int i_type);
}
 
class LawnMowerModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(LawnMowerModule, LevelModule, RtClass);

	float GetEntryAnimDuration();
	void AwardMowers(int i_mowerCount, bool i_createNow = false);
	void AddMowerToSaveData(uint8 i_rowIndex);
	LawnMower* GetUntriggeredMowerInRow(uint8 i_rowIndex);
	bool HasUntriggeredMowerInRow(uint8 i_rowIndex);

	void			CancelBuyMower();
	PopAnim* getMowerAnim();
	bool     ShouldRespawnMower(uint8 i_rowIndex);
     
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
    void		 postInitialize() override;
     
private:
	void onUpdate();
	void onReadyForMowers();
	void onLawnMowerDie(class LawnMower* i_mower);
	void onBuyItemOK(int i_type);
	void onBuyItemCancel(int i_type);
	
	void createMowers();
	bool isNeedBuyMower(int i_row);
	
	bool canTriggerNormalADMower();

    const std::vector<int>				getIdleAnimWeights();
	const std::string&                  getMowerAudio();

	void addPreparedMowers();
	std::vector<LawnMower*> getMowerBoardEntitiesInRow(uint8 i_rowIndex);
	bool hasMowerInSaveData(uint8 i_rowIndex);
	void prepareMowerForRow(int i_rowIndex);
	bool shouldCreateMowerInRow(uint8 i_rowIndex);
	bool rowCanAcceptNewMower(int i_rowIndex);

	void                                initializeMowerRespawn();

	int			m_bonusLawnMowersRemaining;
	float			m_fBuyMowerCoolDown;
	int			m_iBuyMowerRow;
	std::vector<int>                    m_respawnsRemaining;
	int m_adsMowerTimes;
};
 
class LawnMowerProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(LawnMowerProperties, LevelModuleProperties, RtClass);
     
    virtual RtClass* GetModuleClass() const override
    {
        return LawnMowerModule::StaticGetClass();
    }
 
    LawnMowerProperties()
    {
		MowerEntryAnimDuration = 2.5f;
        MowerExplodeAtGridX = -1;
        UnlimitedMowers = false;
    }
	
	float               MowerEntryAnimDuration;
	std::string         MowerPopAnim;
    std::string         MowerActivatedAudioEvent;
    std::vector<int>	MowerIdleAnimWeights;
    int                 MowerExplodeAtGridX;
    bool				UnlimitedMowers;
};

#endif
