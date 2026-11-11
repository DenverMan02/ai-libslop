#ifndef RTCLASSTEST_H_
#define RTCLASSTEST_H_

#include <set>
#include <string>
#include <vector>

#include "PVZTypes.h"
#include "RtObject.h"
#include "StandardLevelIntro.h"
#include "TimeMgr.h"
#include "ObjectTypeDirectory.h"
#include "StandardLevelIntro.h"
#include "Plant_Peashooter.h"
#include "ZombieGargantuar.h"

#include "SingletonExtern.h"

class TestIntroModule : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(TestIntroModule, StandardLevelIntro, RtClass);

	void registerForEvents() override;

	void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);

protected:
	void startLevelIntro(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE, bool i_special = false) override;
	void onStandardIntroComplete() override;

private:
	PlantPtr m_testPlant;
	ZombiePtr m_testZombie;
};

class TestIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(TestIntroProperties, StandardLevelIntroProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return TestIntroModule::StaticGetClass();
	}

private:
	bool NewBoolField;
	std::string NewStringField;
};

#endif /* RTCLASSTEST_H_ */
