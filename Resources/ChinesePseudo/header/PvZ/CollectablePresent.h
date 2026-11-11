//
//  CollectablePresent.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/27/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CollectablePresent_h
#define PlantsVersusZombies2_CollectablePresent_h

#include "Collectable.h"
#include "WorldData.h"

class CollectablePresentType : public CollectableType
{
public:
	RT_CLASS_DEFINE(CollectablePresentType, CollectableType, RtClass);
	
	CollectablePresentType()
	{
		IsShiny = false;
	}

	bool IsShiny;
};

class CollectablePresent : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectablePresent, Collectable, RtClass);
	
	CollectablePresent()
	{
	
	}
	
	bool GetIsShiny() const;

private:
};

class CollectableYetiPresentType: public CollectableType
{
public:
    RT_CLASS_DEFINE(CollectableYetiPresentType, CollectableType, RtClass);
    
    CollectableYetiPresentType()
    {
    }
};

class CollectableYetiPresent: public Collectable
{
public:
    RT_CLASS_DEFINE(CollectableYetiPresent, Collectable, RtClass);
    
    CollectableYetiPresent()
    {
        ToturialPresent = false;
    }
    
    bool IsToturialPresent()
    {
        return ToturialPresent;
    }
    void SetToturialPresent(bool isToturial)
    {
        ToturialPresent = isToturial;
    }
    
//not serial
    bool ToturialPresent;

};

///////////

class CollectableNewerPresentType : public CollectableType
{
public:
    RT_CLASS_DEFINE(CollectableNewerPresentType, CollectableType, RtClass);
    
    CollectableNewerPresentType()
    {
        
    }
};

class CollectableNewerPresent: public Collectable
{
public:
    RT_CLASS_DEFINE(CollectableNewerPresent, Collectable, RtClass);
    
    CollectableNewerPresent()
    {
        
    }
};

class CollectableAdvanceNewerPresent: public Collectable
{
public:
    RT_CLASS_DEFINE(CollectableAdvanceNewerPresent, Collectable, RtClass);
    
    CollectableAdvanceNewerPresent()
    {
        
    }
};

#endif
