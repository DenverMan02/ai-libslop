#ifndef CardEffectSummonZombieWithPtero_H
#define CardEffectSummonZombieWithPtero_H

#include "CardEffectCommon.h"
#include "CardInfluence.h"

class Zombie;

#pragma mark - PteroFlyWithZombieEntity

class PteroFlyWithZombieEntity : public BoardEntity
{
public:
    RT_CLASS_DEFINE(PteroFlyWithZombieEntity, BoardEntity, RtClass);

    PteroFlyWithZombieEntity();
    virtual ~PteroFlyWithZombieEntity();

    virtual void        onUpdate() override ;
    virtual void        onDestroy() override;
    
    void                initialize(float i_targetX);
    void                SetTargetZombie(RtWeakPtr<Zombie> i_zombiePtr);
    
protected:
    void                onArrive();

    float               m_speed;
    float               m_targetX;
    StandaloneEffectPtr m_renderEffect;
    RtWeakPtr<Zombie>   m_targetZombie;
};

//翼龙携带僵尸
class SummonZombieWithPteroEffect : public SummonZombieEffect
{
public:
	RT_CLASS_DEFINE(SummonZombieWithPteroEffect, SummonZombieEffect, RtClass);

    virtual void DoEffect() override;
private:
    virtual ZombiePtr SpawnZombie(class ZombieSummonPacket& i_packet, const Sexy::SexyVector3& i_position) override;
}; 

class SummonZombieWithPteroEffectProperty : public SummonZombieEffectProperty
{
public:
	RT_CLASS_DEFINE(SummonZombieWithPteroEffectProperty, SummonZombieEffectProperty, RtClass);

    SummonZombieWithPteroEffectProperty()
    :MoveGridRange(1, 13)
    {
        
    }

    virtual RtClass* GetCardEffectClass() const override
    {
        return SummonZombieWithPteroEffect::StaticGetClass();
    }

    Sexy::Point MoveGridRange;
}; 



#endif