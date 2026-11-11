//
//  Plant_Asparagus.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-7-10.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAsparagus_h
#define PlantsVersusZombies2_PlantAsparagus_h

#include "PlantFramework.h"


class PlantAsparagus : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantAsparagus, PlantFramework, RtClass);
    
    PlantAsparagus() : m_iAttackRow(0), m_iAttackCount(0), m_iSleepTime(PVZ_T()) {}
    
    ~PlantAsparagus() {}
    
protected:
    
	void Initialize() override;
    
    bool CanApplyPlantfood() override { return true; };
    
	void ApplyPlantfood() override;
    
    bool CanEndPlantfood() override;
    
    void UpdateActions() override;
    
    int	 GetPlantFoodPlayCount() override;
    
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
    
    int ConfirmRow();
    
    int ConFirmPlantFoodType();
    
    void DoNormalDamage();
    
    void DrawEffect(MATH_TYPE iX, MATH_TYPE iY, int iRenderOrder, bool bPlantFood = false);
    
    bool CanDamageZombie(BoardEntity* pEntity);
    
    bool CanDamageGridItem(BoardEntity* pEntity);
    
    void TakeNormalDamage(std::vector<BoardEntity*>& vEntities, PlantWeapon weapon);
    
    bool IsSleeping();
    
    std::vector<BoardEntity*> GetValidEntities(int iGridx, int iGridy);
    
    BoardEntityPtr GetRowValidEntity(int iRow);
    
    void DoPlantFoodDamage();
    
    void CalcPlantFoodGrid();
    
    void RecordPush(ZombiePtr ptrz);
    
    bool CheckPushed(ZombiePtr ptrz);
    
    void AvatarPush(std::vector<BoardEntity*>& vEntities);
    
private:
    
    int m_iAttackRow;
    
    int m_iAttackCount;
    
    pvztime_t m_iSleepTime;
    
    std::vector<Point> m_vPlantFoodGrid;
    
    std::vector<BoardEntityPtr> m_vPushZombie;
    
};


class AsparagusPropertySheet : public PlantPropertySheet
{
    
public:
    
    RT_CLASS_DEFINE(AsparagusPropertySheet, PlantPropertySheet, RtClass);
    
    std::vector<float> StrikeRate;
    int ContinueCount;
    float IntervalTime;
    
};

enum ASPARAGUSANIMSTATE
{
    ASPARAGUS_SLEEP_READY = PLANTANIM_USERDEFINED + 1,
    ASPARAGUS_SLEEP_LOOP,
    ASPARAGUS_SLEEP_END
};


class PlantAnimRig_Asparagus : public PlantAnimRig
{
public:
    
    RT_CLASS_DEFINE(PlantAnimRig_Asparagus, PlantAnimRig, RtClass);
    
    PlantAnimRig_Asparagus()
    : m_iAttackDirect(1)
    , m_bBeginSleep(false)
    , m_iPlantFoodAttackType(1) {}
    
    void SetDirect(int iDirect) { m_iAttackDirect = iDirect; }
    
    void SetBeginSleep(bool bSleep) { m_bBeginSleep = bSleep; }
    
    void SetPlantFoodAttackType(int iType) { m_iPlantFoodAttackType = iType; }
    
    int GetPlantFoodPlayCountIndex() { return m_plantFoodPlayCount; }
    
    bool PlaySleepReady(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    
    bool PlaySleepEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

protected:
    
    std::string getPlantFoodOnAnimName() override;
    
    std::string getAttackAnimationName() override;
    
    std::string getPlantFoodMainAnimName() override;
    
    void onAnimStopped() override;
    
private:
    
    int m_iAttackDirect; //0 up, 1 mid, 2 down
    
    bool m_bBeginSleep;
    
    int m_iPlantFoodAttackType; //0 up mid; 1 up mid down; 2 mid down;
    
};

#endif
