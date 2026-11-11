//
//  PVPSeedBankModule.h
//  PlantsVersusZombies2
//
//  Created by Emma on 2015.9.25
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVPSeedBankModule_h
#define PlantsVersusZombies2_PVPSeedBankModule_h

#include "SeedBankModule.h"
#include "PVPSeedBank.h"

enum PVPMode
{
    PVPMode_Plant = 0,
    PVPMode_Zombie = 1,
};

class PVPSkillEnergyUI;

class PVPSeedBankModule : public SeedBankModule
{
public:
	RT_CLASS_DEFINE(PVPSeedBankModule, SeedBankModule, RtClass);
    PVPSeedBankModule();

	virtual void			AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
   	virtual bool			UsesSeedChooser() const override;
    
    void                    ShowAllSeedBank(bool i_visible);

    PVPSeedBankPtr          GetPlantSeedBank() { return m_PlantSeedBank; }
    PVPSeedBankPtr          GetZombieSeedBank() { return m_ZombieSeedBank; }
    PVPSeedBankPtr          GetSkillSeedBank() {return m_SkillSeedBank;}
    RtWeakPtr<PVPSkillEnergyUI>  GetPVPSkillEnergyUI() {return m_SkillEnergyUI;}
    
    void                    renewSkillSeedBank();
protected:
	virtual void			initializeModule() override;
	virtual void			registerForEvents() override;
	
    virtual void			createSeedBank() override;
	virtual void			onLoadComplete() override;
    virtual void			onGameStarted() override;
    
    void                createSkillSeedBank();
    void                createPlantSeedBank();
    void                createZombieSeedBank();
    void                createTutorialZombieSeedBank();
    
    void                onAddToRenderQueue(class RenderQueue* i_queue);
    void                onDraw(Graphics* i_g);
    void                onPlantShoveled(Plant* i_plant);
    
    
protected:
    PVPMode             m_pvpMode;
    PVPSeedBankPtr         m_SkillSeedBank;
    PVPSeedBankPtr      m_PlantSeedBank;
    PVPSeedBankPtr       m_ZombieSeedBank;
    RtWeakPtr<PVPSkillEnergyUI> m_SkillEnergyUI;

};

struct PVPSeedSkill
{
    std::string SkillName;
    int InitEnergyCost;
    int MaxEnergyCost;
    PVPSeedSkill()
    : InitEnergyCost(5)
    , MaxEnergyCost(20)
    {}
};

struct PVPSeedPlant
{
    std::string PlantName;
    int MaxNum;
    int NeedZoneLevel;
    PVPSeedPlant()
    : NeedZoneLevel(0)
    , MaxNum(999)
    {}
};

struct PVPSeedZombie
{
    std::string ZombieName;
    int NeedZoneLevel;
    PVPSeedZombie()
    : NeedZoneLevel(0)
    {}
};



class PVPSeedBankProperties : public SeedBankProperties
{
public:
	RT_CLASS_DEFINE(PVPSeedBankProperties, SeedBankProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return PVPSeedBankModule::StaticGetClass();
	}
	
	virtual SeedBankType GetBankType() const override
	{
		return SEEDBANK_PVP;
	}
	
	PVPSeedBankProperties()
    : TotalBrains(50)
    , SkillEnergy(30)
    , LostPlantEnergy(5)
    , LostBrainEnergy(20)
	{
        ZombieMode = true;
	}
    
public:
    int     TotalBrains;
    int     SkillEnergy;
    int     LostPlantEnergy;
    int     LostBrainEnergy;
    std::vector<PVPSeedSkill>     SkillList;
    std::vector<PVPSeedPlant>       PlantList;
    std::vector<PVPSeedZombie>      ZombieList;

};


#endif
