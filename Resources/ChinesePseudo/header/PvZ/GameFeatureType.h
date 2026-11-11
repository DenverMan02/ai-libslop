//
//  GameFeatureType.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 3/13/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GameFeatureType__
#define __PlantsVersusZombies2__GameFeatureType__

#include "RtDb.h"
#include "ObjectTypeDescriptor.h"
#include "LawnAppEnums.h"

typedef RtWeakPtr<class GameFeatureType> GameFeatureTypePtr;
typedef RtWeakPtr<class BonusType> BonusTypePtr;

class GameFeatureType : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(GameFeatureType, ObjectTypeDescriptor, RtClass);

	GameFeatureType()
	{
		IsAPowerup = false;
	}

	static GameFeatureTypePtr GetGameFeatureTypeFromUnlockString(const std::string i_unlockString);
	static GameFeatureTypePtr GetGameFeatureTypeFromEnum(const GameFeature i_feature);
	static const char* GetGameFeatureInternalStringFromEnum(const GameFeature i_feature);
	
	std::string LocalizedName;
	std::string LocalizedInfo;
	std::string UpgradeImage;
	std::string HomeWorld;
	GameFeature Feature;
	bool IsAPowerup;
	
	const char* ToString() const;
    
    bool IsFeatureEnabled() const;
    
    Sexy::ImagePtr GetUpgradeImage() const;
};

//PVZ2_CHINESE_BEGIN
class BonusType: public ObjectTypeDescriptor
{
public:
    RT_CLASS_DEFINE(BonusType, ObjectTypeDescriptor, RtClass);
    
    BonusType()
    {
        BonusNum = 1;
    }
    
    static BonusTypePtr GetBonusTypeFromUnlockString(const std::string i_unlockString, bool i_doCheckSign = true);
    static std::string CalBonusNumSign();
    static void ResetBonusNumSign();
    static bool CheckBonusNumSign();
    
    std::string LocalizedName;
	std::string LocalizedInfo;
	std::string BonusImage;
	GameBonus   Bonus;
    int         BonusNum;
    
	const char* ToString() const;
    
    static std::string AllBonusNumSign; //anti-hack.
};
//PVZ2_CHINESE_END


#endif /* defined(__PlantsVersusZombies2__GameFeatureType__) */
