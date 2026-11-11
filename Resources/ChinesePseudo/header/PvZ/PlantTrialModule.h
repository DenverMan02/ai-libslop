//
//  PlantTrialModule.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-4-5.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantTrialModule_h
#define PlantsVersusZombies2_PlantTrialModule_h

#include "LevelModule.h"
#include "UIWidget.h"
#include "Plant.h"
#include "WaveGenerator.h"
#include "GridItem.h"
#include "Effect_BouncingArrow.h"
#include "BaseCursor.h"

class PlantTrialModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(PlantTrialModule, LevelModule, RtClass);
    
    PlantTrialModule();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    
private:

    void            AddToRenderQueue(class RenderQueue* i_queue);
    void            RenderInfos(Graphics* i_g);
    void            OnUpdate();
    
    void            onNarrationFinished();
    void            onWaveStarted(int iWaves);
    
    bool            IsZombieAllDie();
    
    void            SeedPacketGenerator();
    void            OnNpcDraw(Graphics* i_g);
    
    Sexy::SexyVector2     GetDesPacketPos();
	bool			IsTrialEnabled();
    
    void            ControlShowZombie(bool bControl);
    void            MakeGridItemTargetable(bool tagetable);
    void            ZombieController(bool bControl);
    
    void            UpdateCheck();
    
    bool            CanStartNarrationActive();
    
    bool            CanSeedPacketVisibleEnable();
    
    void            SetZombieGeneraterPause(bool bPause);
    
    void            SetAppendObjPause(bool bPause);
    void            EndTutorial();
    void            SetIntroState(int state);
    void            OnCursorAdded(BaseCursor* i_cursor);
    void            OnCursorDestroyed(BaseCursor* i_cursor);
    void            DrawHighlight(Graphics* g);
    void		        OnPlantPlanted(class Plant* i_plant);
    Effect_BouncingArrow * AddBouncingArrow(const Sexy::SexyVector2& screenLocation);
private:
    int             m_introState;
    bool            m_bWavePause;
    bool            m_bSeedMoving;
    
    Effect_BouncingArrowPtr	m_bouncingArrow;
    RtWeakPtr<class SeedPacket> m_ptrSeedPacket;
    RtWeakPtr<class Zombie>     m_ptrZombie;
    std::vector<GridItemPtr> m_gridItem;
    pvztime_t       m_iStarMovingTime;
};


class PlantTrialProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PlantTrialProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return PlantTrialModule::StaticGetClass();
	}
    
    PlantTrialProperties()
    {
    }
};

namespace Message
{
    void WavesNotify(int iWaves);
}


#endif
