#ifndef CardEffectCommon_H
#define CardEffectCommon_H

#include "CardEffect.h"
#include "CardInfluence.h"

typedef RtWeakPtr<class Zombie> ZombiePtr;

//召唤僵尸
class SummonZombieEffect : public CardEffect
{
public:
	RT_CLASS_DEFINE(SummonZombieEffect, CardEffect, RtClass);

    virtual void DoEffect() override;
protected:
    int GetZombieSpawnRate();
    void SummonEffectFinish();
    virtual ZombiePtr SpawnZombie(class ZombieSummonPacket& i_packet, const Sexy::SexyVector3& i_position);
}; 

struct ZombieSummonPacket
{
    ZombieSummonPacket()
    :Multiple(1),
    OffRangeX(-10, 10),
    Regular(false)
    {
    }

    ZombieTypePtr ZombieType;
    int Multiple;
    Sexy::SexyVector2 OffRangeX;
    bool Regular;
};

class SummonZombieEffectProperty : public CardEffectProperty
{
public:
	RT_CLASS_DEFINE(SummonZombieEffectProperty, CardEffectProperty, RtClass);

    SummonZombieEffectProperty()
    {

    }

    virtual RtClass* GetCardEffectClass() const override
    {
        return SummonZombieEffect::StaticGetClass();
    }

    std::vector<ZombieSummonPacket> ZombieList;
}; 



//添加Condition
class AddConditionEffect : public CardEffect
{
public:
	RT_CLASS_DEFINE(AddConditionEffect, CardEffect, RtClass);

    virtual void DoEffect() override;
    pvztime_t GetConditionDuration();
}; 

class AddConditionEffectProperty : public CardEffectProperty
{
public:
	RT_CLASS_DEFINE(AddConditionEffectProperty, CardEffectProperty, RtClass);

    AddConditionEffectProperty()
    :Duration(-1),
    Team(TEAM_PLANTS)
    {

    }

    virtual RtClass* GetCardEffectClass() const override
    {
        return AddConditionEffect::StaticGetClass();
    }

    ZombieConditions Codition;
    float Duration;
    TeamFlags Team;
}; 



//获得卡牌
class ObtainCardEffect : public CardEffect
{
public:
	RT_CLASS_DEFINE(ObtainCardEffect, CardEffect, RtClass);

    virtual void DoEffect() override;
}; 

class ObtainCardEffectProperty : public CardEffectProperty
{
public:
	RT_CLASS_DEFINE(ObtainCardEffectProperty, CardEffectProperty, RtClass);

    ObtainCardEffectProperty()
    :NewCost(-1),
    Number(1),
    Tag(CT_None)
    {

    }

    virtual RtClass* GetCardEffectClass() const override
    {
        return ObtainCardEffect::StaticGetClass();
    }

    int NewCost;
    int Number;
    CardTag Tag;
    std::vector<RtWeakPtr<CardType>> CardPool;
}; 



//生成GridItem
class AddGridItemCardEffect : public CardEffect
{
public:
	RT_CLASS_DEFINE(AddGridItemCardEffect, CardEffect, RtClass);

    virtual void DoEffect() override;
}; 

class AddGridItemCardEffectProperty : public CardEffectProperty
{
public:
	RT_CLASS_DEFINE(AddGridItemCardEffectProperty, CardEffectProperty, RtClass);

    AddGridItemCardEffectProperty()
    {

    }

    virtual RtClass* GetCardEffectClass() const override
    {
        return AddGridItemCardEffect::StaticGetClass();
    }

    GridItemTypePtr GridItemType;
}; 



//移动卡牌
class MoveSeatCardEffect : public CardEffect
{
public:
	RT_CLASS_DEFINE(MoveSeatCardEffect, CardEffect, RtClass);

    virtual void DoEffect() override;
}; 

class MoveSeatCardEffectProperty : public CardEffectProperty
{
public:
	RT_CLASS_DEFINE(MoveSeatCardEffectProperty, CardEffectProperty, RtClass);

    MoveSeatCardEffectProperty()
    :FromSeat(CardSeat_Hand),
    ToSeat(CardSeat_Graveyard),
    CardNumber(1)
    {

    }

    virtual RtClass* GetCardEffectClass() const override
    {
        return MoveSeatCardEffect::StaticGetClass();
    }

    CardSeat FromSeat;
    CardSeat ToSeat;
    int CardNumber;
};



//添加光环类型效果
class AddAuraCardEffect : public CardEffect
{
public:
	RT_CLASS_DEFINE(AddAuraCardEffect, CardEffect, RtClass);

    virtual void DoEffect() override;
}; 

class AddAuraCardEffectProperty : public CardEffectProperty
{
public:
	RT_CLASS_DEFINE(AddAuraCardEffectProperty, CardEffectProperty, RtClass);

    AddAuraCardEffectProperty()
    {

    }

    virtual RtClass* GetCardEffectClass() const override
    {
        return AddAuraCardEffect::StaticGetClass();
    }

    RtWeakPtr<InfluenceAuraProperty> AuraProperty;
}; 


//升级墓碑
class UpgradeGravestoneCardEffect : public CardEffect
{
public:
	RT_CLASS_DEFINE(UpgradeGravestoneCardEffect, CardEffect, RtClass);

    virtual void DoEffect() override;
}; 

class UpgradeGravestoneCardEffectProperty : public CardEffectProperty
{
public:
	RT_CLASS_DEFINE(UpgradeGravestoneCardEffectProperty, CardEffectProperty, RtClass);

    UpgradeGravestoneCardEffectProperty()
    {

    }

    virtual RtClass* GetCardEffectClass() const override
    {
        return UpgradeGravestoneCardEffect::StaticGetClass();
    }
}; 


#endif