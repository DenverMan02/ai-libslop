//
//  Plant_IceShroom.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-8-28.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_IceShroom_h
#define PlantsVersusZombies2_Plant_IceShroom_h

#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"

class IceShroomProps : public PlantPropertySheet
{
public:
    
    struct IceShroomGrowthStates
	{
        ProjectilePropertySheetPtr Projectile;
		float TimeToGrowInSeconds;
        float ProjectileHeightFactor;
        SexyVector2 SpawnOffset;
        ProjectilePropertySheetPtr SuperProjectile;
	};
    
    struct AdvanceInfo
    {
        float GrowthFactor;
        float EffectFactor;
        
        AdvanceInfo() : GrowthFactor(1.0), EffectFactor(0.0)
        {
            
        }
    };
    
    struct FallingStoneInfo
    {
        float BaseDamage;
        float SplashDamage;
    };
    
	RT_CLASS_DEFINE(IceShroomProps, PlantPropertySheet, RtClass);
    
	IceShroomProps()
    :FireShroomLV5Rate(0)
	{
		
	}
    
    std::vector<IceShroomGrowthStates> GrowthStages;
    std::vector<AdvanceInfo>           AppendAdvanceInfo;
    FallingStoneInfo                   FireShroomFallingStoneInfo;
    
    ProjectilePropertySheetPtr SplitOneProjectile;
    ProjectilePropertySheetPtr SplitTwoProjectile;
    ProjectilePropertySheetPtr SuperSplitOneProjectile;
    ProjectilePropertySheetPtr SuperSplitTwoProjectile;
    float FireShroomLV5Rate;
};

class PlantIceShroom : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantIceShroom, PlantFramework, RtClass);
    PlantIceShroom();
    
	virtual ~PlantIceShroom();
    void	Initialize() override;
	void	UpdateActions() override;
    bool	CanApplyPlantfood() override;
    void	CancelPlantfood() override;
	void	ApplyPlantfood() override;
	void	NotifySetHidden(bool i_newValue, bool i_oldValue) override;
    bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    Projectile*	   Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    const IceShroomProps* GetIceShroomProps() { return GetProps<IceShroomProps>(); }
    int GetCurLevel() { return GetCurrentLevel(); }
    void InitPooyanShooter(float i_damage);
    void Idle() override;
    bool CanBeWatered() override;
    void onSetDuplicate(bool i_duplicate) override { };

    virtual pvztime_t GetTheLeastAttactDuration() override;
protected:
    void			onPlantGrowthPaused();
    void			onPlantGrowthResumed();
    const int		getMaxGrowthStage();
    void			setGrowthStage(int i_growthStage, PopAnimRig::AnimStoppedReflectionDelegate i_onGrowthAnimComplete = PopAnimRig::AnimStoppedReflectionDelegate());
	bool			isFullyGrown();
	
private:
    
    Projectile*     FireProjectile(IceShroomProps::IceShroomGrowthStates growthStates, int iPierceCount = 0, bool i_super = false);
    void            GenerateIceHole();
    
protected:
	
	pvztime_t m_swapForOtherPlantTime;
	pvztime_t m_growthPauseStartTime;
	uint8 m_currentGrowthStage;
};

class PlantAnimRig_IceShroom : public PlantAnimRig
{
public:
	
	RT_CLASS_DEFINE(PlantAnimRig_IceShroom, PlantAnimRig, RtClass);
    
    PlantAnimRig_IceShroom()
	{
		m_currentGrowthStage = 0;
	}
    
	void SetGrowthStage(uint8 i_stage, PopAnimRig::AnimStoppedReflectionDelegate i_onGrowthAnimComplete = PopAnimRig::AnimStoppedReflectionDelegate());
    std::string GetPriviewAnim();
    bool PlayPreviewAnim(bool bHideLayer = false) override;
    
protected:
    
    bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
    
    void onPopAnimCommand(pvztime_t i_atTime, const std::string &i_command, const std::string &i_param) override;
	
protected:
	std::string getIdleAnimationName() override;
	std::string getSpecialAnimName();
    std::string getWaterAnimName() override;
	std::string getPlantFoodMainAnimName() override;
	
	void growthAnimComplete(const std::string& i_anim);
	
	uint8 m_currentGrowthStage;
    
};

class IceShroomGreatShotProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(IceShroomGreatShotProjectile, Projectile, RtClass);
    
    IceShroomGreatShotProjectile()
    {
        m_iSplitStep = 0;
        m_iSplitCount = 0;
    }
    
    bool OnCollideEntity(BoardEntity* i_entity) override;
    
    void SetSplitStep(int iStep) { m_iSplitStep = iStep; }
    
protected:
    
    void onDestroy() override;
    
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity) override;
    
private:
    
    int m_iSplitCount;
    
    int m_iSplitStep;
    
    RtWeakPtr<BoardEntity> m_pParentBoardEntity;
};


class IceShroomNormalShotProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(IceShroomNormalShotProjectile, Projectile, RtClass);
    
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity) override;
};



#endif
