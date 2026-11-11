/*
 * CardGameBoardModule.h
 *
 *  Created on: 2022-5-27
 *      Author: admin
 */

#ifndef CARDGAMEBOARDMODULE_H_
#define CARDGAMEBOARDMODULE_H_

#include "LevelModule.h"
#include "RtDb.h"

class CardGameBoardModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(CardGameBoardModule, LevelModule, RtClass);

	CardGameBoardModule();
	~CardGameBoardModule();

	float GetBoardScale();

protected:
	void registerForEvents() override;

	void OnCardGameIntroStart();
	void OnCardGamePickCardStart(int i_round);
	void OnCardGamePlayerActionStart();
	void OnCardGamePlayerDiscardStart();

	void OnGameplayStarted();
	void onEndLevel();
	void OnCreatePlant(class Plant* plant);
	void OnZombiePlaceOnBoard(class Zombie* zombie);
	void OnNotifyGridItemPlaceOnBoard(class GridItemAnimation* i_gridItem);
	void OnNotifyProjectileCreated(class Projectile* i_projectile);

};

class CardGameBoardModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(CardGameBoardModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return CardGameBoardModule::StaticGetClass();
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float BoardEntityScale;
};


#endif /* CARDGAMEBOARDMODULE_H_ */
