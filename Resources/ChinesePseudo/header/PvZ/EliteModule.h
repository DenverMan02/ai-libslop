/*
 * EliteModule.h
 *
 *  Created on: 2021-6-1
 *      Author: zhousen
 */

#ifndef ELITEMODULE_H_
#define ELITEMODULE_H_

#include "PVZDB.h"
#include "Singleton.h"
#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "core.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "ProfileMgr.h"
#include "MagentoService.h"
#include "PlantAdventureConfig.h"
#include "BoxOpenUI.h"
#include "PopingWidget.h"
#include "UISingletonDialog.h"
#include "EASquared.h"
#include "UIUtil.h"
#include "UIRewardFrame.h"
//#include "ActivityManager.h"
#include "UIUtil.h"

//
// Elite Module Base
//
class EliteModuleBase
{
public:
	EliteModuleBase() {}
	virtual ~EliteModuleBase() {}
	virtual void Render(Sexy::Graphics* g) {}
};

//
// Plant Elite Module
//
class PlantEliteModule : public EliteModuleBase
{
public:
	PlantEliteModule() {}
	virtual ~PlantEliteModule() {}
	virtual void Render(Sexy::Graphics* g) override {}
};

//
// Zombie Elite Module
//
class ZombieEliteModule : public EliteModuleBase
{
public:
	ZombieEliteModule();
	virtual ~ZombieEliteModule();
	virtual void Render(Sexy::Graphics* g) override;

	void SetCurrentHealth(float health);
	void SetMaxHealth(float maxHealth);
	void SetHealthImage(Image* health, Image* frame);
	void SetHeadIcon(Image* head);
	void SetPosition(SexyVector3 position);
	void SetHealthBarVisible(bool visible);
	void SpawnZombieEffect(SexyVector3 pos);

protected:
	float _currentHealth;// elite  zombie current health
	float _maxHealth;// elite zombie max health
	Image* _headImg;// the zombie head icon
	Image* _healthFrameImg;// the health frame image
	Image* _healthProgressImg;// the health progress image
	SexyVector3 _position;// the zombie position
	bool _drawHealthBar;// check if draw health bar
};

#endif /* ELITEMODULE_H_ */
