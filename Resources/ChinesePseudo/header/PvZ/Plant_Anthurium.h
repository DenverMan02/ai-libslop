//
//  Plant_Anthurium.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-7-8.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Anthurium__
#define __PlantsVersusZombies2__Plant_Anthurium__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"

class AnthuriumProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(AnthuriumProps, PlantPropertySheet, RtClass);
    AnthuriumProps();
    
    int PlantfoodThunderCount;
    float PlantfoodThunderRadius;
    std::vector<float> AdvancedAttackProbability;
};


class AnthuriumThunderTarget : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(AnthuriumThunderTarget, RtObject, RtClass);
    Point hitPosition;
    BoardEntityPtr primaryTarget;
};

class AnthuriumThunderChain : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(AnthuriumThunderChain, RtObject, RtClass);
    AnthuriumThunderChain();
    AnthuriumThunderChain(const Point& _node1, const Point& _node2);
    bool OnSameGride(const AnthuriumThunderChain& other);
    Point node1;
    Point node2;
};

class PlantAnthurium : public PlantFramework
{
    enum Direction
    {
        Left = 0,
        Right,
        Top,
        Bottom,
        LeftTop,
        RightTop,
        LeftBottom,
        RightBottom,
        Center
    };
    enum ThunderEvent
    {
        ThunderEventHit = 0,
        ThunderEventBeginChain,
        ThunderEventChainHit,
        ThunderEventNone,
    };
public:
    RT_CLASS_DEFINE(PlantAnthurium, PlantFramework, RtClass);
    bool	 CanApplyPlantfood() override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    void	 UpdateActions() override;
    void	 ApplyPlantfood() override;
    DamageTypeFlags	GetDamageFlags(PlantWeapon i_plantWeapon) override;
    PlantAnthurium();
private:
    bool TrigerAdvancedAttack();
    bool FindElectricity(Plant*& plant1, Plant*& plant2);
    bool ChainExist(const std::vector<AnthuriumThunderChain>& searchVec, const AnthuriumThunderChain& chain);
    void PlayElectricityAborbEffect(Plant* plant);
    void PlayElectricityDispelEffect(Plant* plant);
    void UpdateIdle();
    void ThunderHit();
    void ThunderChain(BoardEntity* primaryTarget, Direction direction);
    void ThunderDown(const std::vector<BoardEntityPtr>& targets);
    void PlayChainEffect(const Point& start, Direction direction);
    void PlayThunderUpEffect();
    void PlayThunderHitEffect(const Point& position);
    void PlayThunderDownEffect(const BoardEntityPtr& target);
    void AbsorbAllElectricity();
    void OnEffectAnimCommand(const std::string& i_animLabel,
                             pvztime_t i_timeStamp,
                             const std::string& i_animCommand,
                             const std::string& i_animCommandParam);
    Direction CalcDirection(Plant* plant);
    std::vector<BoardEntityPtr> GetThunderTarget();
    std::vector<BoardEntity*> GetThunderSplashTarget(const Point& position,  float radius, BoardEntity* ignore);
private:
    ThunderEvent m_nextEffectEvent;
    std::vector<AnthuriumThunderChain> m_thunderChain;
    std::vector<BoardEntityPtr> m_thunderTarget;
};

class PlantAnimRig_Anthurium : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Anthurium, PlantAnimRig, RtClass);
    PlantAnimRig_Anthurium();
    bool PlayAdvancedAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
private:
};


#endif /* defined(__PlantsVersusZombies2__Plant_Anthurium__) */
