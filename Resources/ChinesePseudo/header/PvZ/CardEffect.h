#ifndef CardEffect_H
#define CardEffect_H

#include "PropertySheetBase.h"
#include "BoardEntity.h"
#include "PVZTypes.h"
#include "CardType.h"
#include <queue>

class CardObject;
class CardType;
typedef RtWeakPtr<class CardEffectProperty> CardEffectPropsPtr;
typedef RtWeakPtr<class CardEffect> CardEffectPtr;

//卡牌效果
//-----------------------------------------卡牌效果代码::开始-----------------------------------------

enum CardEffectType
{
    CET_UseCard = 0,
    CET_BeforePlayerDiscard, //PlayerRoundEnd
};

class CardEffectProperty : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(CardEffectProperty, Sexy::RtObject, RtClass);

    CardEffectProperty()
    :EffectType(CET_UseCard)
    {

    }

    virtual RtClass* GetCardEffectClass() const
    {
        DBG_HALT_MSG("CardEffect of class %s does not implement GetCardEffectClass!", GetClass()->GetName());
        return nullptr;
    }

    CardEffectType EffectType;
};

enum CardEffectState
{
    CES_Invalid,
    CES_Initializa,
    CES_Starting,
    CES_Finish,
};

class CardEffect : public GameObject
{
public:
	RT_CLASS_DEFINE(CardEffect, GameObject, RtClass);

    CardEffect();

    virtual void InitializaEffect(CardEffectPropsPtr i_effectProps, RtWeakPtr<CardObject> i_cardObject);
    virtual void DoEffect();
    virtual void Interrupt();

    CardEffectState GetEffctState();

protected:
    RtWeakPtr<CardObject> mCardObject;
    CardEffectPropsPtr mEffectProps;
    CardEffectState mEffectState;
}; 


//-----------------------------------------卡牌效果代码::结束-----------------------------------------

//卡牌效果处理器

class CardEffectProcessor : public BoardEntity
{
    RT_CLASS_DEFINE(CardEffectProcessor, BoardEntity, RtClass);
public:
    void PushEffect(RtWeakPtr<CardEffect> i_effect);

	virtual void onUpdate() override;

    std::queue<RtWeakPtr<CardEffect>> m_effectList;
};

#endif
