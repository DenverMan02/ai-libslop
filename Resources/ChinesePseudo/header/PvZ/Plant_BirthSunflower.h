//
//  PlantBirthSunflower.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-9-2.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantBirthSunflower__
#define __PlantsVersusZombies2__PlantBirthSunflower__

#include "PlantFramework.h"
#include "RestrictionSet.h"
#include "Collectable.h"

class BirthSunflowerProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(BirthSunflowerProps, PlantPropertySheet, RtClass);
    
    BirthSunflowerProps();

    std::vector<float> AttackUpPercent;
    std::vector<float> AttackUpDuration;
    std::string CollectibleTypeName;
    std::string PlantfoodCollectibleTypeName;
    PlantRestrictionSet PlantCanbeAttackup;
};

class PlantBirthSunflower : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantBirthSunflower, PlantFramework, RtClass);
    
    void	 Initialize() override;
    void	 UpdateActions() override;
    bool	 CanApplyPlantfood() override;
    void	 ApplyPlantfood() override;
    void	 CancelPlantfood() override;
    void	 UpdatePlantfood() override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    void Idle() override;
    PlantBirthSunflower();
private:
    void ApplyPlantfoodSongEffect();
    void	 ProduceSun(const PlantAction& i_fromAction) override;
    void	 onGroundCherryApplyPlantFood();
    void registerForEvents() override;
    void unregisterForEvents() override;
    void AttackUpPlant();
    void PlaySpotLightEffect();
    void PlaySunDanceEffect();
    void StopWaterPlant();
    void ApplyAccompaniment();
    bool HavePlantfoodSinger();
    std::string getCollectableTypeName();
};

class PlantAnimRig_BirthSunflower : public PlantAnimRig
{
public:
    enum STATE {
        STATE_SPAWN = PLANTANIM_USERDEFINED,
        STATE_ACCOMPANIMENT,
    };
public:
    RT_CLASS_DEFINE(PlantAnimRig_BirthSunflower, PlantAnimRig, RtClass);
    bool PlaySing();
    bool PlayAccompaniment();
protected:
    void onAnimStopped() override;
};

class LoveTwoSun : public Effect_PopAnim
{
public:
    class LoveTwoSunDropItem
    {
    public:
        pvztime_t MoveTime;
        SexyVector3 Acceleration;
        RtWeakPtr<Collectable> Sun;
        LoveTwoSunDropItem();
        LoveTwoSunDropItem(pvztime_t moveTime, const SexyVector3& acceleration, const RtWeakPtr<Collectable>& sun);
    };
public:
    RT_CLASS_DEFINE(LoveTwoSun, Effect_PopAnim, RtClass);
    void PlayDance();
    void SetBoardPos(const SexyVector3& boardPos);
    void SetSunType(const std::string& typeName);
    LoveTwoSun();
protected:
    void onUpdate() override;
    void onAnimStopped(const std::string& i_animLabel) override;
private:
    void BeginDrop();
    void DropSun(const LoveTwoSunDropItem& item);
    RtWeakPtr<Collectable> CreateSun(SexyVector3 position);
private:
    bool m_beginDrop;
    SexyVector3 m_boardPos;
    std::string m_typeName;
    std::vector<LoveTwoSunDropItem> m_dropItem;
};

#endif /* defined(__PlantsVersusZombies2__PlantBirthSunflower__) */
