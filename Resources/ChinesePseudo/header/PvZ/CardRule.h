#ifndef CardRule_H
#define CardRule_H

#include "PropertySheetBase.h"
#include "BoardEntity.h"
#include "PVZTypes.h"
#include "CardType.h"

class CardObject;
typedef RtWeakPtr<class CardRuleProperty> CardRulePropsPtr;

class CardRuleProperty : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(CardRuleProperty, Sexy::RtObject, RtClass);

    virtual RtClass* GetCardRuleClass() const
    {
        DBG_HALT_MSG("CardEffect of class %s does not implement GetCardEffectClass!", GetClass()->GetName());
        return nullptr;
    }  
};

class CardRule : public GameObject
{
public:
	RT_CLASS_DEFINE(CardRule, GameObject, RtClass);

    virtual void InitializaRule(CardRulePropsPtr i_ruleProps, RtWeakPtr<CardObject> i_cardObject);
    virtual bool IsRulePass() { return true; };

public:
    RtWeakPtr<CardObject> mCardObject;
    CardRulePropsPtr mRuleProps;
};


class UnifiedCardRule: public CardRule
{
public:
	RT_CLASS_DEFINE(UnifiedCardRule, CardRule, RtClass);

    virtual bool IsRulePass() override;

};

class UnifiedCardRuleProperty : public CardRuleProperty
{
public:
	RT_CLASS_DEFINE(UnifiedCardRuleProperty, CardRuleProperty, RtClass);

    virtual RtClass* GetCardRuleClass() const
    {
        return UnifiedCardRule::StaticGetClass();
    }

    UnifiedCardRuleProperty()
    :HandCardNumberPass(0)
    {

    }


    int HandCardNumberPass;
};



#endif