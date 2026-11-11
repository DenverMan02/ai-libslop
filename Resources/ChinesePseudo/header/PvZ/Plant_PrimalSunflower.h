
#ifndef Plant_PrimalSunflower_h
#define Plant_PrimalSunflower_h

#include "PlantFramework.h"
#include "Plant_Sunflower.h"
#include "PlantAnimRig_Sunflower.h"
#include "GameEventMgr.h"

class PrimalSunflowerProps : public SunflowerProps
{
public:
    RT_CLASS_DEFINE(PrimalSunflowerProps, SunflowerProps, RtClass);
    
    PrimalSunflowerProps()
    {
        ExtraSmallSunCount = 5;
        ExtraSmallSunRate1 = 0.5;
        ExtraSmallSunRate2 = 1.0;
        HomeExtraCollectableTypeName =  "sun_medium";
    }
    int ExtraSmallSunCount;
    float ExtraSmallSunRate1;
    float ExtraSmallSunRate2;
    std::string HomeExtraCollectableTypeName;
    int Level5TotalSun;
};

enum
{
    LEVEL5_NONE = 0,
    LEVEL5_SUN1,
    LEVEL5_SUN2,
    LEVEL5_SUN3,
};

class PlantPrimalSunflower : public PlantSunflower
{
public:
    RT_CLASS_DEFINE(PlantPrimalSunflower, PlantSunflower, RtClass);
    
    virtual void    AddPot(PlantPot* pot) override;

    virtual void	Initialize() override;
    virtual void	ApplyPlantfood() override;
    virtual void	DoSpecial(int i_extraParam = 0) override;
    virtual void	ProduceSun(const PlantAction& i_fromAction) override;
    
    virtual void	UpdateActions() override;
    void GenerateLevel5Sun();
    void OnAnimStopped(const std::string &i_animName);
    void onKilled(bool i_instantKill) override {}
protected:
    int coinCount;
    int level5Idx;
};

class PlantAnimRig_PrimalSunflower : public PlantAnimRig_Sunflower
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_PrimalSunflower, PlantAnimRig_Sunflower, RtClass);
    PlantAnimRig_PrimalSunflower();
    
    void PlayLevel5Sun(int idx, AnimStoppedDelegate i_onStopDelegate);
    void PlayLevel5CoolDown(AnimStoppedDelegate i_onStopDelegate);
    
    std::string getLevel5Sun1();
    std::string getLevel5Sun2();
    std::string getLevel5Sun3();
    std::string getLevel5CoolDown();
    
    virtual bool PlayIdleLooped() override;
protected:
    virtual void onAnimStopped() override;
    
    int level5Idx;

};

#endif /* Plant_PrimalSunflower_hpp */
