//
//  StandaloneEffectFactory.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 11/11/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StandaloneEffectFactory__
#define __PlantsVersusZombies2__StandaloneEffectFactory__

#include "PVZDB.h"

class StandaloneEffect;
class Effect_PopAnim;
class Effect_StaticImage;

class StandaloneEffectFactory
{
public:
	virtual ~StandaloneEffectFactory(){}
	
	StandaloneEffect* AddEffect(Sexy::RtClass *i_effectClass);
	template<typename T>
	T* AddEffect();
	
	Effect_StaticImage* CreateCenteredScreenSpaceEffectStaticImage();
	Effect_PopAnim* CreateCenteredScreenSpaceEffectPopAnim();
	
	static StandaloneEffectFactory& GetEffectsTableFactory();
	static StandaloneEffectFactory& GetOutsideOfTableFactory();
	
private:
	StandaloneEffectFactory(PVZDB::TableIndex i_table);
	
	PVZDB::TableIndex mTableIndex;
};

template<typename T>
T* StandaloneEffectFactory::AddEffect()
{
	return AddEffect(T::StaticGetClass())->template CastChecked<T>();
}

#endif /* defined(__PlantsVersusZombies2__StandaloneEffectFactory__) */
