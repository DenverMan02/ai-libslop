//
//  ZombiePumpkin.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/10/22.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombiePumpkin__
#define __PlantsVersusZombies2__ZombiePumpkin__

#include <stdio.h>
#include "Precompile.h"
#include "Zombie.h"

class ZombiePumpkin : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombiePumpkin, Zombie, RtClass);
    
    virtual void onAnimStoppedCallback(const std::string &i_animLabel);
    
    virtual void setAncestor(const std::string& i_ancestor) { m_ancestor = i_ancestor; }
    
    virtual void setIsFromPlantfood(bool i_isFromPlantfood) { m_isFromPlantfood = i_isFromPlantfood; }
    
    virtual void setAncestorHitPoint(float i_hitPoint) { m_ancestorHitPoint = i_hitPoint; }
    
    virtual void setHitRate(float i_hitRate) { m_hitRate = i_hitRate; }
    
    virtual void setAncestorLevel(int i_level) { m_ancestorLevel = i_level; }
    
    virtual void setColor(const std::string& i_color);
    
protected:
    virtual void onZombieInitialize() override;
    
    virtual void onUpdate() override;
    
    virtual void onPlaceOnBoard() override;
    
    virtual void onLostHead() override;
    
    virtual float GetBaseEatDPS() override;
    
    virtual bool hasHeadParticle() const override;
    
    virtual void spawnAncestorZombie();
    
    virtual void createDropHeadEffect();
    
protected:
    
    std::string m_ancestor;
    
    float m_ancestorHitPoint;
    
    int m_ancestorLevel;
    
    bool m_isFromPlantfood;
    
    float m_hitRate;
    
    std::string m_color;
    
private:

};

class ZombiePumpkinImp : public ZombiePumpkin
{
public:
    RT_CLASS_DEFINE(ZombiePumpkinImp, Zombie, RtClass);
    
    void onAnimStoppedCallback(const std::string &i_animLabel) override;
    
    virtual void setColor(const std::string& i_color) override;
    
protected:
//    virtual void onZombieInitialize();
//    
    virtual void onUpdate() override;
//
    virtual void onPlaceOnBoard() override;
    
private:

};

#endif /* defined(__PlantsVersusZombies2__ZombiePumpkin__) */
