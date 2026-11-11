//
//  CollectableCoin.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/20/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectableCoin_h
#define PlantsVersusZombies2_CollectableCoin_h

#include "Collectable.h"

class CollectableCoinType : public CollectableType
{
public:
	RT_CLASS_DEFINE(CollectableCoinType, CollectableType, RtClass);
	
	CollectableCoinType()
	{
		CoinValue = 0;
	}
	
	int CoinValue;
};

class CollectableCoin : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableCoin, Collectable, RtClass) {}
	
	int GetCoinValue() const;
	
	virtual void onFinishMotion() override;

private:
};

class CollectableCoinFake : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableCoinFake, Collectable, RtClass) {}

	int GetCoinValue() const;
	
	virtual void onFinishMotion() override;

};

class CollectableCoinDangerDrop : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableCoinDangerDrop, Collectable, RtClass) {}
    
	int GetCoinValue() const;
	
	virtual void onFinishMotion() override;

};

#endif
