//
//  CollectableSpring.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 1/9/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectableSpring_h
#define PlantsVersusZombies2_CollectableSpring_h

#include "Collectable.h"
//PVZ2_CHINESE_BEGIN
#include "WorldData.h"
#include "PlantEnums.h"
//PVZ2_CHINESE_END

class CollectableSpringCoinType : public CollectableType
{
public:
	RT_CLASS_DEFINE(CollectableSpringCoinType, CollectableType, RtClass);
	
	CollectableSpringCoinType()
	{
		CoinValue = 0;
	}
	
	int CoinValue;
};

//=============================================================================

//class CollectableSpringGemType : public CollectableType
//{
//public:
//	RT_CLASS_DEFINE(CollectableSpringGemType, CollectableType, RtClass);
//	
//	CollectableSpringGemType()
//	{
//		GemValue = 0;
//	}
//	
//	int GemValue;
//};

//=============================================================================

class CollectablePlantPieceType : public CollectableType
{
public:
	RT_CLASS_DEFINE(CollectablePlantPieceType, CollectableType, RtClass);
	
	CollectablePlantPieceType()
    {
        PlantName = "";
    }

    
    std::string PlantName;
};

//=============================================================================

class CollectableAvatarPieceType : public CollectableType
{
public:
    RT_CLASS_DEFINE(CollectableAvatarPieceType, CollectableType, RtClass);
    
    CollectableAvatarPieceType()
    {
        PlantName = "";
        AvatarType = E_AVATAR_NONE;
    }
    
    std::string PlantName;
    PlantAvatarType AvatarType;
};

//=============================================================================

class CollectableAccessoryPieceType : public CollectableType
{
public:
    RT_CLASS_DEFINE(CollectableAccessoryPieceType, CollectableType, RtClass);

    CollectableAccessoryPieceType()
    {
    	AccessoryType = "";
    }

    std::string AccessoryType;
};

//=============================================================================

class CollectableSpringCoin : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableSpringCoin, Collectable, RtClass) {}
	
	int GetSpringCoinValue() const;
};

//=============================================================================

//class CollectableSpringGem : public Collectable
//{
//public:
//	RT_CLASS_DEFINE(CollectableSpringGem, Collectable, RtClass) {}
//	
//	int GetSpringGemValue() const;
//    
//protected:
//    virtual void onUpdate();
//};

//=============================================================================

class CollectablePlantPiece : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectablePlantPiece, Collectable, RtClass) {}
	
    std::string GetPlantName() const;
    
    std::string GetTypeName() const;
    
protected:
    virtual void onUpdate() override;
private:
    virtual void initializeRenderEffect() override;
    StandaloneEffect* CreateSelfRenderEffect(const CollectableType* i_type);
};

//=============================================================================

class CollectableAvatarPiece : public Collectable
{
    RT_CLASS_DEFINE(CollectableAvatarPiece, Collectable, RtClass) {}
    
    std::string GetPlantName() const;
    std::string GetTypeName() const;
    PlantAvatarType GetPlantAvatarType() const;
    
protected:
    virtual void onUpdate() override;
private:
    virtual void initializeRenderEffect() override;
};

//=============================================================================

class CollectableAccessoryPiece : public Collectable
{
    RT_CLASS_DEFINE(CollectableAccessoryPiece, Collectable, RtClass) {}

    std::string GetAccessoryType() const;
    std::string GetTypeName() const;

protected:
    virtual void onUpdate() override;
};

//=============================================================================

class CollectableDRMadal : public Collectable
{
    RT_CLASS_DEFINE(CollectableDRMadal, Collectable, RtClass) {}
    
protected:
    virtual void onUpdate() override;
};

//=============================================================================

#endif
