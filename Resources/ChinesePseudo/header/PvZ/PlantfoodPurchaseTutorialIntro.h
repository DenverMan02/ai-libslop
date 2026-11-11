//
//  PlantfoodPurchaseTutorialIntro.h
//  PlantsVersusZombies2
//
//  Created by jsola on 2/26/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantfoodPurchaseTutorialIntro_h
#define PlantsVersusZombies2_PlantfoodPurchaseTutorialIntro_h

#include "StandardLevelIntro.h"
#include "AnimationMgr.h"
#include "Core.h"
#include "StandaloneEffect.h"
#include "PowerupCukeTutorialIntro.h"
#include "SeedPacket.h"

class PlantfoodPurchaseTutorialIntro : public PowerupCukeTutorialIntro
{
public:
	RT_CLASS_DEFINE(PlantfoodPurchaseTutorialIntro, PowerupCukeTutorialIntro, RtClass);

	void pauseWave(bool bPause) override;

protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;

	void startIntro() override;
	void update() override;
	void onEndLevel() override;
	void onGameplayStarted() override;
	void enterTutorial() override;
	bool needCukeTutorial() override;
	void onToolAppliedPlantFood(class PlantGroup* i_plant) override;

private:
	//void			startIntro();
	//void			onUpdate();
	//void			onEndLevel();
		
	void			setupDaveProlog();
	void			startDaveNarrative();
	void			onDaveShouldSpawnCoins();
	//PVZ2_CHINESE_START
	void			onFakeGemBanked(int i_count);
	//PVZ2_CHINESE_END
	
	void			grantFakeMoney();
	
	void			updatePlantfoodPurchaseTutorial();
	void			showPlantfoodPurchaseSuccessAdvice();
	void			finishPlantfoodPurchaseTutorial();

	void			onPlantfoodCountChanged(int i_count);
	void			onNarrationFinished();

	class Effect_BouncingArrow*		addBouncingArrow(const SexyVector2& i_screenLocation);
	void							clearBouncingArrows();
	
	enum PlantfoodPurchaseState
	{
		PVZ_BEGIN_ENUM(STATE_PPT_),
		STATE_PPT_INACTIVE,
		STATE_PPT_DAVE_INTRO,
		STATE_PPT_GIVING_COINS,
		STATE_PPT_DISPLAYING_ADVICE_1,
		STATE_PPT_DISPLAYING_ADVICE_2,
        STATE_PPT_BUY_SUN,
        STATE_PPT_PLANT_SUNFLOWER,
        STATE_PPT_PLANT_USEPLANTFOOD,
		PVZ_END_ENUM(STATE_PPT_),
	};
	
	void			setState(PlantfoodPurchaseState i_newState);
	void onPlantPlanted(Plant* i_plant);
    class SunBank* GetSunBank();
	AnimationMgrWkPtr                  	m_animationMgr;
	std::vector<StandaloneEffectPtr>	m_bouncingArrows;

	bool 								m_plantfoodPurchaseTutorialActive;
	PlantfoodPurchaseState				m_plantfoodPurchaseTutorialState;
	pvztime_t							m_plantfoodPurchaseTutorialTimer;
	RtWeakPtr<class StandaloneEffect>	m_plantfoodPurchaseBouncyArrow;
	SeedPacketPtr           			m_sunflowerPacketPtr;
};

class PlantfoodPurchaseTutorialIntroProperties : public PowerupCukeTutorialIntroProperties
{
public:
	RT_CLASS_DEFINE(PlantfoodPurchaseTutorialIntroProperties, PowerupCukeTutorialIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{ 
		return PlantfoodPurchaseTutorialIntro::StaticGetClass();
	}
};


#endif
