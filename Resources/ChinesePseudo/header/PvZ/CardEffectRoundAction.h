#ifndef CardEffectRoundAction_H
#define CardEffectRoundAction_H

#include "CardEffect.h"
#include "CardInfluence.h"

//回合结束时，伤害玩家
class RoundActionHurtPlayer : public CardEffect
{
public:
	RT_CLASS_DEFINE(RoundActionHurtPlayer, CardEffect, RtClass);

    virtual void DoEffect() override;
protected:

}; 

class RoundActionHurtPlayerProperty : public CardEffectProperty
{
public:
	RT_CLASS_DEFINE(RoundActionHurtPlayerProperty, CardEffectProperty, RtClass);

    RoundActionHurtPlayerProperty()
    :DamageRate(0.1f)
    {

    }

    virtual RtClass* GetCardEffectClass() const override
    {
        return RoundActionHurtPlayer::StaticGetClass();
    }

    float DamageRate;;
}; 


#endif