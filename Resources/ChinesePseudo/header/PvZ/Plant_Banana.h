//
//  Plant_Banana.h
//  PlantsVersusZombies2
//
//  Created by Andrew Khosravian on 6/18/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Banana__
#define __PlantsVersusZombies2__Plant_Banana__

#include "PlantFramework.h"
#include "RtObject.h"
#include "Projectile.h"
#include "StandardLevelIntro.h"
#include "Effect_BouncingArrow.h"
#include "GameSubSystem.h"

namespace Message
{
	void BananaSelected();
	void BananaLaunched();
	void BananaTappedOnCooldown();
}

enum BananaState
{
    BANANA_STATE_SELECTED = STATE_FRAMEWORK_BEGIN,
	BANANA_STATE_FIRING,
	BANANA_STATE_RECOVERING,
	BANANA_STATE_RECOVERING_END,
};


enum  E_BANANA_LV5_STEP
{
	BANANA_LV5_FIRST_FIRE,
	BANANA_LV5_FIRST_EXPOSE,
	BANANA_LV5_COUNTDOWN,
	BANANA_LV5_SECOND_EXPOSE,
	BANANA_LV5_END,
};




class PlantBanana : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantBanana, PlantFramework, RtClass);
    PlantBanana();
	void Initialize() override;
    void UpdateActions() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	void SetCanOnlyTargetZombies(bool i_x) { m_onlyTargetZombies = i_x; }
	void SetFireIgnoreBoardState(bool i_x) { m_fireIgnoreBoardState = i_x; }
	void ChooseTarget2Fire(const Sexy::Point& i_targetLocation);
	void NotifySetHidden(bool i_newValue, bool i_oldValue) override;
    Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
    void Idle() override;
	bool IsPlayingLevel5() { return m_isCurLevel5Attack; }

	void SetPlayingLevel5(bool isLv5);
	bool IsMeetShowPlayLv5();
	void RandomPlayLevel5();
private:
    void addShot(float plantFoodFireTime, int& io_shot, const Point& i_point,bool bBig = false);
    
    void registerForEvents() override;
    void unregisterForEvents() override;

    bool onTouchEvent(const Sexy::Touch& i_touch);
    void onCursorDestroyed(BaseCursor* i_cursor);
	void onAnimStoppedCallback(const std::string& i_animName) override;
    void setState(const int i_newState);
	bool select();
	void deselect();
	bool canFire() const;

	void queueShot(pvztime_t i_launchTime, const Point& i_targetLocation,bool bBig = false);

	bool m_onlyTargetZombies;
	bool m_fireIgnoreBoardState;
	bool m_isCurLevel5Attack;

	// not serialized
	class BananaTargetCursor* m_targetCursor;
};


class PlantAnimRig_Banana : public PlantAnimRig
{
public:
	//RT_CLASS_DEFINE(PlantAnimRig_Banana, PlantAnimRig, RtClass) {}
	RT_CLASS_DEFINE(PlantAnimRig_Banana, PlantAnimRig, RtClass);
	bool PlaySelected();
	bool PlayRecoverStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayRecoverLoop();
	bool PlayRecoverEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
	bool PlayPlantFoodStart(int i_mainAnimPlayCount, PlantFoodMainAnimStartedDelegate i_onPlantFoodStarted, PlantFoodMainAnimEndedDelegate i_onPlantFoodLooped, PlantFoodMainAnimEndedDelegate i_onPlantFoodEnded) override;
	
	void SetIsLevel5(bool isLv5) 
	{
		m_islevel5 = isLv5;
	}
	PlantBanana *m_plantOwer;
	std::string getIdleAnimationName()override;
private:
	bool m_islevel5 = false;
};

class BananaTutorialModule : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(BananaTutorialModule, StandardLevelIntro, RtClass);

	void initializeModule() override;
	void registerForEvents() override;

	void onLevelEnded();
	void onBananaSelected();
	void onBananaLaunched();
	void onBananaTappedWhileCoolingDown();
	void onTutorialFinished();
	void onZombieDestroyed(class Zombie* i_zombie, const DamageInfo* i_deathBlow);

protected:
	void startLevelIntro(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE, bool i_special = false) override;
	void startNarration(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE) override;

private:
	void pointArrowAtZombie();
	void pointArrowAtBanana();

	bool m_tutorialIsActive;
	ZombiePtr m_tutorialZombie;
	PlantPtr m_tutorialBanana;
	RtWeakPtr<Effect_BouncingArrow> m_bouncingArrow;
};

class BananaTutorialProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(BananaTutorialProperties, StandardLevelIntroProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return BananaTutorialModule::StaticGetClass();
	}

	BananaTutorialProperties(){}

	void GatherResourceRequirements(std::set<std::string> &io_resourceGroupNames) const override;
};

class BananaLauncherSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(BananaLauncherSubSystem, GameSubSystem, RtClass);
    
    BananaLauncherSubSystem();

	struct BananaLauncherEntry
	{
		BananaLauncherEntry() {}
		BananaLauncherEntry(PlantBanana* i_owner, pvztime_t i_launchTime, const Point& i_target, bool bBig = false);

		//PlantBanana *m_owerPlant;
		PlantPtr Owner;
		RtWeakPtr<const BananaProps> BananaPropertySheet;
		pvztime_t LaunchTime;
		bool m_isLevel5 = false;
		Point Target;
		bool  bIsBig;
	};

	void QueueShot(PlantBanana* i_owner, pvztime_t i_launchTime, const Point& i_target,bool bBig = false);
	void Update() override;
    BananaLauncherEntry* GetLauncherEntry(int i);

private:
	void launch(const BananaLauncherEntry& i_entry);
	std::vector<BananaLauncherEntry> m_shots;
	 
};




class BananaLv5PropertySheet : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(BananaLv5PropertySheet, ProjectilePropertySheet, RtClass);

	BananaLv5PropertySheet()
	{
	}

	float AreaDamage;
	int RowNum;
	int ColumnNum;

};

class BananaLv5Projectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BananaLv5Projectile, Projectile, RtClass);
	BananaLv5Projectile();
	virtual ~BananaLv5Projectile();
private:

	E_BANANA_LV5_STEP  m_curStep;
	RtWeakPtr<Effect_PopAnim> 	m_effectMissile;
public:
	bool OnCollideGround() override;
	
	bool PlayCollideGroundExposeAm();
	bool PlayLevel5TimeCountDownAm();
	bool PlayLevel5SecondExposeAm();
	

private:
	bool  InitExposeAm();
	void  FirstExposeAttack();
	void  SecondExposeAttack();
private:
	void onProjectileAmStop(const std::string& i_animName);

	void RemoveUndamageableEntitiesFromList(std::vector<BoardEntity*> &o_boardEntities);
	void onExposeAnimStopped(StandaloneEffect* i_effect);
};



#endif

