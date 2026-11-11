#ifndef CardType_H
#define CardType_H

#include "PropertySheetBase.h"
#include "Utils.h"

//卡牌位置
enum CardSeat
{
    CardSeat_Hand,
    CardSeat_Ready,
    CardSeat_Graveyard,
    CardSeat_Exhaust,
};

//卡牌增益，减益效果
enum CardBuff
{
    CardBuff_Start = 0,

    CardBuff_CostAffect,

    CardBuff_Max,
};


//卡牌
enum CardTag
{
    CT_None = 0,

    CT_Kind_Zombie, //种类 僵尸卡
    CT_Kind_Plant, //种类 植物卡
    CT_Kind_Artifact, //种类 神器卡

    CT_Type_Creature,//类型 生物卡
    CT_Type_Skill,//类型 法术卡
    CT_Type_Curse,//类型 诅咒

    CT_Special_Derivative,//衍生物

    CT_Effect_Summon,//召唤

    CT_KeyWords_Exhaust,//消耗
};

struct CardUIInfo
{
	CardUIInfo()
	: CardBackgroundImgName("")
	, CardCostImgName("")
	, CardAttackImgName("")
	, CardLifeImgName("")
	, CardAvatarImgName("")
	, CardSelectImgName("")
	, CardTouchMoveImgName("")
	, CardHeadshotImgName("")
	{

	}

	std::string CardBackgroundImgName;
	std::string CardCostImgName;
	std::string CardAttackImgName;
	std::string CardLifeImgName;
	std::string CardAvatarImgName;
	std::string CardSelectImgName;
	std::string CardTouchMoveImgName;
	std::string CardHeadshotImgName;
};

struct CardAttributeData
{
	CardAttributeData()
	{
		Attack = 0;
		HitPoints = 0;
	}

	float Attack;
	float HitPoints;
};

enum CardTargetCursorType
{
	CardCursorType_None,
	CardCursorType_Plant,
	CardCursorType_Zombie,
	CardCursorType_GridItem,
	CardCursorType_Skill,
	CardCursorType_Special
};

struct CardTargetCursorAnim
{
	CardTargetCursorAnim()
	: Type(CardCursorType_None)
	, TypeName("")
	, DisplayCount(0)
	{

	}

	CardTargetCursorType Type;
	std::string TypeName;
	int DisplayCount;
	std::vector<ValueRange> AnimOffset;
	std::string AnimPlayTag;
};

struct CardTargetCursorConfig
{
    CardTargetCursorConfig()
    :TargetCursorClass("CardTargetCursor")
    {

    }

    std::string TargetCursorClass;
    CardTargetCursorAnim Anim;
};

class CardType : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(CardType, PropertySheetBase, RtClass);

    int CardID;
    std::string TypeName;
    int Cost;
    std::vector<CardTag> Tags;
    int Rarity;
    std::string Description;
    std::vector<RtEmbeddedPtr<class CardEffectProperty, PVZDB::TABLE_CARD_CONFIG>> EffectList;
    //CardTarget TargetType;
    RtWeakPtr<class CardTargetProperty> TargetProps;
    CardTargetCursorConfig TargetCursorConfig;
    std::vector<RtEmbeddedPtr<class CardRuleProperty, PVZDB::TABLE_CARD_CONFIG>> RuleList;
    CardUIInfo CardInfo;
    CardAttributeData Attribute;


    bool HasTag(CardTag i_tag);
};


class CardSettingProperty : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(CardSettingProperty, PropertySheetBase, RtClass);


    std::vector<std::string> MoveToEnemyBlackList;
    std::vector<std::string> MoveToBossBlackList;
	std::vector<std::string> GridItemPlaceCheckList;
};
#endif
