//
//  CollectableWeapon.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-4-16.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__CollectableWeapon__
#define __PlantsVersusZombies2__CollectableWeapon__

#include "Collectable.h"

class CollectableWeaponType : public CollectableType
{
	RT_CLASS_DEFINE(CollectableWeaponType, CollectableType, RtClass);
};


class CollectableWeapon : public Collectable
{
public:
    
	CollectableWeapon()
	{
		m_seedPacketImage = NULL;
	}
    
	virtual ~CollectableWeapon()
	{
        
	}
    
	RT_CLASS_DEFINE(CollectableWeapon, Collectable, RtClass);
	
	void SetSeedType(const std::string& i_seedType);
    
    std::string GetSeedName();
	
protected:
	virtual void onDraw(class Sexy::Graphics* i_g) override;
	virtual void onDestroy() override;
	
private:
	void drawToBuffer();
	
	PlantTypePtr m_seedType;
    std::string  m_seedName;
	DeviceImage* m_seedPacketImage;
};

#endif /* defined(__PlantsVersusZombies2__CollectableWeapon__) */
