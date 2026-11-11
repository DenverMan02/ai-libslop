//
//  Playback.h
//  PlantsVersusZombies2
//
//  Created by Emma on 2015.10.23
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlaybackModule_h
#define PlantsVersusZombies2_PlaybackModule_h

#include "LevelModule.h"
#include "PVZTypes.h"
#include "PlaybackData.h"
#include "PlaybackController.h"

class PlaybackModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(PlaybackModule, LevelModule, RtClass);
    PlaybackModule();
    virtual ~PlaybackModule();

	virtual void			AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
protected:
	virtual void			initializeModule() override;
	virtual void			registerForEvents() override;
    virtual void         unregisterForEvents() override;
    
    void                addTrigger(class PTrigger* pTrigger);
    void                endPlaying();
    void                setSeedBankClickable(class PVPSeedBank* pSeedBank, bool bClickable);
    
    void                onGameStarted();
    void                onGameEnded();
    void                onEndLevel();
    void                onUpdate();
    void                onNotifyBattleStart();
    void                onNotifyBattleEnd(bool i_success, int i_errorCode);
    void                onNotifyBattleEndingNetworkError();
    void                onZombiePlanted(class Zombie* i_zombie);
	void                onZombiePlaybackAddParams(class Zombie* i_zombie, int i_type);
    void                onPVPSkillUsed(class Zombie* pSkill, int iCost);
    void                onNotifyPlantfoodUsed(class Plant* i_plant);
    void                onMessageBoxCallback(class UIMessageBox* pDlg, int i_id);
    void                onArenaEndingButtonPressed();
    
protected:
    std::vector<class PTrigger*>    m_cachedTriggers;
    BattleID            m_recordID = 0;
	int						m_zombieIndex = 1;
};


class PlaybackProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(PlaybackProperties, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return PlaybackModule::StaticGetClass();
    }
};


#endif
