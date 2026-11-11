/*
 * ScaledBoardModule.h
 *
 *  Created on: 2022-10-11
 *      Author: admin
 */

#ifndef SCALEDBOARDMODULE_H_
#define SCALEDBOARDMODULE_H_

#include "LevelModule.h"
#include "RtDb.h"

class ScaledBoardModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(ScaledBoardModule, LevelModule, RtClass);

	ScaledBoardModule();
	~ScaledBoardModule();

	float GetBoardScale();

protected:
	void registerForEvents() override;

	void OnCreatePlant(class Plant* plant);
	void OnZombiePlaceOnBoard(class Zombie* zombie);
	void OnNotifyGridItemPlaceOnBoard(class GridItemAnimation* i_gridItem);
	void OnNotifyProjectileCreated(class Projectile* i_projectile);
	void OnNotifyPopAnimCreated(class Effect_PopAnim* i_anim);

};

class ScaledBoardModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ScaledBoardModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return ScaledBoardModule::StaticGetClass();
	}

	float BoardEntityScale;
};


#endif /* SCALEDBOARDMODULE_H_ */
