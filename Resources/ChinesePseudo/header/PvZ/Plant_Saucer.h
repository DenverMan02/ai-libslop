//
//  Plant_Saucer.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-7-17.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantSaucer_h
#define PlantsVersusZombies2_PlantSaucer_h

#include "PlantFramework.h"


class PlantSaucer : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSaucer, PlantFramework, RtClass);
    
    PlantSaucer() : m_iEndConditionTime(PVZ_T()) {}
    
    virtual ~PlantSaucer() {}
    
protected:
    
	void Initialize() override;
    
	void ApplyPlantfood() override;
    
    bool CanEndPlantfood() override;
    
    bool CanApplyPlantfood() override;
    
    bool CanBeTargeted() override { return GetRig()->GetState() == PLANTANIM_IDLE; }
    
    bool CanBeTargetedBy(const BoardEntity* i_entity) override { return GetRig()->GetState() == PLANTANIM_IDLE; }
    
    void UpdateActions() override;
    
    int CalcRenderOrder() override;
    
    void onAnimStoppedCallback(const std::string &i_animLabel) override;
    
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
private:
    
    std::vector<BoardEntity*> GetValidTarget();
    
    void DoNormalDamage(std::vector<BoardEntity*>& vEntities);
    
    void FillStunedCache(std::vector<BoardEntity*>& vEntities);
    
    bool CheckStunedCache(Zombie* pZombie);
    
    bool ConditionCheck();
    
    void DoPlantFoodDamage();
    
    void WhiteScreen();
    
private:
    
    std::vector<BoardEntityPtr> m_vStunedCache;
    
    pvztime_t m_iEndConditionTime;
    
};


class SaucerPropertySheet : public PlantPropertySheet
{
    
public:
    
    RT_CLASS_DEFINE(SaucerPropertySheet, PlantPropertySheet, RtClass);
    
    SaucerPropertySheet() : StunTime(10), AvatarStunTime(20) {}
    
    float StunTime;
    
    float AvatarStunTime;
    std::vector<int> AbsorbHp;
};

enum SAUCERANIMSTATE
{
    ATTACK_BEGIN = PLANTANIM_USERDEFINED + 1,
    ATTACK_LOOP,
    ATTACK_END
};


class PlantAnimRig_Saucer : public PlantAnimRig
{
public:
    
    RT_CLASS_DEFINE(PlantAnimRig_Saucer, PlantAnimRig, RtClass);
    
    PlantAnimRig_Saucer() {}
    
    void SetParentPtr(BoardEntityPtr ptr) { m_ptrSaucer = ptr; }
    
    void PlayLight();
    
    void PlayAway();
    
protected:
    
    void onAnimStopped() override;;
    
private:
    
    RtWeakPtr<class BoardEntity> m_ptrSaucer;
    
};

#endif
