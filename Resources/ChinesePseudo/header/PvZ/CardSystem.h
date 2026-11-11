#ifndef CardSystem_H
#define CardSystem_H

#include "LevelModule.h"
#include "Core.h"
#include "PvZ2IDs.h"
#include "GameEventMgr.h"
#include "BoardEntity.h"
#include "GameSubSystem.h"
#include "PropertySheetBase.h"
#include "PlantBoostPropertySheet.h"
#include "CardTarget.h"
#include "CardEffect.h"
#include "CardInfluence.h"

typedef RtWeakPtr<class CardType> CardTypePtr;

class CardSystemMoudle : public LevelModule
{
public:
	RT_CLASS_DEFINE(CardSystemMoudle, LevelModule, RtClass);
    
	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	
private:
	void onLoadComplete();
};

class CardSystemMoudleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(CardSystemMoudleProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return CardSystemMoudle::StaticGetClass();
	}
};

class TempCard : public BoardEntity
{
    RT_CLASS_DEFINE(TempCard, BoardEntity, RtClass);
public:
    void CardInitialize(CardTypePtr i_cardType);

    virtual int CalcRenderOrder() const override;
    virtual void Draw(class Sexy::Graphics* i_g) override;
    virtual bool ShouldDrawShadow() const override { return false; }


    virtual Sexy::Rect calcCollisionRect() override;
protected:
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
    virtual void onUpdate() override;

	virtual bool onTouchEvent(const Sexy::Touch& i_touch);

    int m_canUseCard;
    int m_stateIndicator;
    RtWeakPtr<class CardObject> m_card;
};







//
//卡牌管理，及效果管理
//
class CardSystemManager : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(CardSystemManager, GameSubSystem, RtClass);

    CardSystemManager();
    ~CardSystemManager();

    virtual void Update() override;

    RtWeakPtr<CardObject> CreateCardByID(int i_cardID);
    RtWeakPtr<CardObject> CreateCardByType(RtWeakPtr<CardObject> i_cardType);
    void DeleteCard(RtWeakPtr<CardObject> i_cardObjectPtr);

    RtWeakPtr<InfluenceAura> RegisterAura(InfluenceAuraPropsPtr i_auraProps);
    InfluenceAuraManager* GetAuraManager() { return &mCardAuraMgr; }

public:
    std::vector<RtWeakPtr<CardObject>> mCardList;
    InfluenceAuraManager mCardAuraMgr;
};


namespace CardUtils
{
    CardTypePtr GetCardType(int i_cardId);
    CardTypePtr GetCardType(const std::string& i_cardName);
    std::vector<CardTypePtr> GetAllCardType();
    std::vector<CardTypePtr> GetAllCardTypeWithTag(CardTag i_tag);


    CardTypePtr GetRandomCardByTag(CardTag i_tag);
    std::vector<CardTypePtr> GetRandomCardsByTag(CardTag i_tag, int i_num, bool i_repeat = false);

    RtWeakPtr<CardSettingProperty> GetCardSettingProperty();
    void CheckZombieCardSettingProperty(Zombie* i_zombie);

}


#endif
