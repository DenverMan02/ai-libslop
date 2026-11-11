//
//  PresentType.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/27/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PresentType_h
#define PlantsVersusZombies2_PresentType_h

#include "ObjectTypeDescriptor.h"

typedef RtWeakPtr<const class PresentType> PresentTypePtr;

class PresentType : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(PresentType, ObjectTypeDescriptor, RtClass);
	
	PresentType()
	{
		Scale = 1.f;
	}
	
	// This function should do whatever is needed to give the contents to the player
	// It should only ever be called from the world map or from the end of level VictoryScreen
	// DO NOT do any visual effects or other flash. Give up the gold and walk away.
	virtual void AwardPresent() const
	{
		// You get nothing! Absolutely nothing! Stupid! You're so stupid!
	}
	
	class StandaloneEffect* BuildEffect() const;

	/// Award screen display properties
	std::string 	PopAnim;
	std::string		Animation;
	std::string 	Image;
	float  			Scale;
};

class PresentTypeCoin : public PresentType
{
public:
	RT_CLASS_DEFINE(PresentTypeCoin, PresentType, RtClass);
	PresentTypeCoin()
	{
		CoinValue = 0;
	}

	virtual void AwardPresent() const override;

	int				CoinValue;
};

class PresentTypeKey : public PresentType
{
public:
	RT_CLASS_DEFINE(PresentTypeKey, PresentType, RtClass);
	PresentTypeKey()
	{
		KeyCount = 1;
	}
	
	virtual void AwardPresent() const override;
	
	std::string WorldName;
	int KeyCount;
};

//PVZ2_CHINESE_END
//Below PresentTypeDrop*** used for drop group
class PresentTypeDropPiece : public PresentType
{
public:
	RT_CLASS_DEFINE(PresentTypeDropPiece, PresentType, RtClass);

	PresentTypeDropPiece()
	{
		PieceCount = 1;
	}

	virtual void AwardPresent() const override;

	std::string PieceName;
	int PieceCount;
};

class PresentTypeFertilizer : public PresentType
{
public:
	RT_CLASS_DEFINE(PresentTypeFertilizer, PresentType, RtClass);

	PresentTypeFertilizer()
	{
		FertilizerCount = 0;
	}

	virtual void AwardPresent() const override;

	int FertilizerCount;
};

class PresentTypeDropGold : public PresentType
{
public:
	RT_CLASS_DEFINE(PresentTypeDropGold, PresentType, RtClass);
	PresentTypeDropGold()
	{
		CoinValue = 0;
	}
    
	virtual void AwardPresent() const override;
    
	int				CoinValue;
};

class PresentTypeDropEmpty : public PresentType
{
public:
	RT_CLASS_DEFINE(PresentTypeDropEmpty, PresentType, RtClass);
	PresentTypeDropEmpty()
	{
		
	}
    
	virtual void AwardPresent() const override;

};
//PVZ2_CHINESE_END
#endif
