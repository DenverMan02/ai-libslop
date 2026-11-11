#ifndef CardObject_H
#define CardObject_H

#include "GameObject.h"
#include "CardInfluence.h"


class CardObject : public GameObject
{
    RT_CLASS_DEFINE(CardObject, GameObject, RtClass);
public:
    CardObject();
    ~CardObject();

    void initializeCardObject(RtWeakPtr<class CardType> i_cardType);

    int GetCost();
    bool HasTag(CardTag i_tag);

    bool IsTargeted();
    void SetTargetPosition(const Sexy::Point i_position);
    bool IsValidTargetPosition(const Sexy::Point i_position);

    bool TryToAddCursor(const Sexy::Touch& i_touch);

    bool IsExhaust();
    bool CanUseCard();
    void UseCard();
    void CancelUseCard();

    void onDestoryCard();

    const CardUIInfo& GetCardUIInfo();

    const CardAttributeData& GetCardAttribute();
    const std::string& GetCardName();
    const std::string& GetCardDescription();
    const std::vector<CardTag>& GetCardTags();
    int GetRarity();
    const CardTargetCursorAnim& GetCursorAnim();

    void SetCursorVisible(bool i_visible);

protected:
    void ActionBeforePlayerDiscard();
    
public:
    //card actions
    void onDrawn(){};
    void onExhaust(){};
    void onMoveToDeck(){};
    
public:
    RtWeakPtr<class CardType> mCardType;
    class CardTargetAdaptor* mTargetAdaptor;
private:
    bool mTargeted;
    std::vector<CardTag> mTags;
    CardBuffTracker mBuffTracker;
    std::vector<RtWeakPtr<class CardRule>> mRuleList;
    class CardTargetCursor* m_cursor;
};

namespace Message
{
    void BeforePlayerDiscard_ForCardObject();
}

#endif
