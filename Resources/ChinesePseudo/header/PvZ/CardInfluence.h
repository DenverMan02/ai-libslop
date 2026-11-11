#ifndef CardInfluence_H
#define CardInfluence_H

#include "GameObject.h"
#include "CardType.h"
#include <vector>
#include <deque>


typedef RtWeakPtr<class InfluenceAuraProperty> InfluenceAuraPropsPtr;
typedef RtWeakPtr<class InfluenceAura> InfluenceAuraPtr;

class CardBuffObject
{
    CardBuffObject()
    :Priority(0),
    RemainingRounds(-1),
    AdditionalDataValue(0)
    {}

    int Priority;
    int RemainingRounds;
    float AdditionalDataValue;
};

class CardBuffTracker
{
public:
    CardBuffTracker();
    ~CardBuffTracker();

    const CardBuffObject& AddBuff(CardBuff i_condition, int i_priority = 0, int i_remainRound = -1);

    void RoundStart();
    void RoundEnd();
    //其他流程 

private:
    std::deque<CardBuffObject> m_cardBuffs;
};



//光环类型效果，主要通过注册回调实现

class InfluenceAura : public GameObject
{
    RT_CLASS_DEFINE(InfluenceAura, GameObject, RtClass);
public:
    virtual void InitializaAura(InfluenceAuraPropsPtr i_auraProps);
    virtual bool ShouldMergeAura();
    virtual void MergeAura(InfluenceAuraPtr i_newAura);
protected:
	virtual void registerForEvents() override {}
	virtual void unregisterForEvents() override {}

public:
    InfluenceAuraPropsPtr mAuraProps;
};

class InfluenceAuraProperty : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(InfluenceAuraProperty, Sexy::RtObject, RtClass);

    virtual RtClass* GetAuraClass() const
    {
        DBG_HALT_MSG("InfluenceAuraProperty of class %s does not implement GetAuraClass!", GetClass()->GetName());
        return nullptr;
    }
};


//每回合给玩家一张随机牌
class GiveFreeZombieCardAura : public InfluenceAura
{
    RT_CLASS_DEFINE(GiveFreeZombieCardAura, InfluenceAura, RtClass);
public:
    GiveFreeZombieCardAura()
    {

    }

    void InitializaAura(InfluenceAuraPropsPtr i_auraProps) override;

protected:
	virtual void registerForEvents() override;

private:
    void OnRoundStart();
};

class GiveFreeZombieCardAuraProperty : public InfluenceAuraProperty
{
    RT_CLASS_DEFINE(GiveFreeZombieCardAuraProperty, InfluenceAuraProperty, RtClass);
public:
    GiveFreeZombieCardAuraProperty()
    :GiveNumber(1)
    {

    }

    virtual RtClass* GetAuraClass() const
    {
        return GiveFreeZombieCardAura::StaticGetClass();
    }

    int GiveNumber;
};


//下次召唤僵尸牌的召唤数量翻倍
class DoubledSummonZombieAura : public InfluenceAura
{
    RT_CLASS_DEFINE(DoubledSummonZombieAura, InfluenceAura, RtClass);
public:
    DoubledSummonZombieAura();
    virtual void InitializaAura(InfluenceAuraPropsPtr i_auraProps) override;
    virtual bool ShouldMergeAura() override { return true; }
    virtual void MergeAura(InfluenceAuraPtr i_newAura) override;

    int GetSummonRate();
    void ConsumeTimes();

protected:
	virtual void registerForEvents() override;

private:
    int DoubledCounter;
};

class DoubledSummonZombieAuraProperty : public InfluenceAuraProperty
{
    RT_CLASS_DEFINE(DoubledSummonZombieAuraProperty, InfluenceAuraProperty, RtClass);
public:
    DoubledSummonZombieAuraProperty()
    :DoubledTimes(1)
    {

    }

    virtual RtClass* GetAuraClass() const
    {
        return DoubledSummonZombieAura::StaticGetClass();
    }

    int DoubledTimes;
};




class InfluenceAuraManager
{
public:
    InfluenceAuraPtr RegisterAura(InfluenceAuraPtr i_auraObject);
    void UnRegisterAura(InfluenceAuraPtr i_auraObject);

    template<class T>
    std::vector<RtWeakPtr<T>> GetTypeAuraList()
    {
        std::vector<RtWeakPtr<T>> result;
        for (size_t i = 0; i < m_auraList.size(); i++)
        {
            T* t = m_auraList[i]->Cast<T>();
            if(t)
            {
                result.push_back(t->GetPtr());
            }
        }
        return result;
    }

private:
    void AddAura(InfluenceAuraPtr i_auraObject);

    std::vector<InfluenceAuraPtr> m_auraList;
};

namespace Message
{
    void AfterPlayerActionStart();
};

#endif