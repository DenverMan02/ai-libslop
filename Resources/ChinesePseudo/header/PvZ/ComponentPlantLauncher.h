//
//  ComponentPlantLauncher.h
//  PlantsVersusZombies2
//
//  Created by Alex Gelles on 9/7/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ComponentPlantLauncher__
#define __PlantsVersusZombies2__ComponentPlantLauncher__

#include "PlantFramework.h"
#include "RtObject.h"
#include "Projectile.h"
#include "BaseCursor.h"
#include "GameSubSystem.h"

namespace Message
{
	void LauncherSelected();
	void LauncherLaunched();
	void LauncherTappedOnCooldown();
}

enum class PlantLaunchState
{
	STATE_SELECTED = STATE_FRAMEWORK_BEGIN,
	STATE_FIRING,
	STATE_RECOVERING,
	STATE_RECOVERING_END,
};

class PlantLauncherProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PlantLauncherProps, PlantPropertySheet, RtClass);

	PlantLauncherProps()
	:FireTime(0),
	TargetOffset(),
	SplashDamage(0),
	PlantfoodFireTime(0),
	NumPlantfoodRockets(0)
	{
	}

	pvztime_t FireTime;
	SexyVector2 TargetOffset;
	int SplashDamage;
	float PlantfoodFireTime;
	int NumPlantfoodRockets;
};

class PlantLauncherTargetCursor : public BaseCursor
{
public:
    RT_CLASS_DEFINE(PlantLauncherTargetCursor, BaseCursor, Sexy::RtClass) {}
    
    PlantLauncherTargetCursor() {}
    explicit PlantLauncherTargetCursor(const Sexy::Touch& i_boardSpaceTouch, PlantFramework* i_Plant, const std::string& i_effect, Delegate1<const Sexy::Point&> i_fireCall);
    virtual ~PlantLauncherTargetCursor();
    
    const PlantFramework* GetPlant() const { return m_Plant; }
    
protected:
    Sexy::SexyVector2 getCursorAnimOffset() const override;
    bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
    
private:
    void onPlantDied(Plant* i_plant);
    
	Delegate1<const Sexy::Point&> m_fireCallBack;
	std::string m_effect;
    Sexy::SexyVector2 m_cursorOffset;
    PlantFramework* m_Plant = nullptr;
};

class ComponentPlantLauncher : public GameObject
{
public:
	RT_CLASS_DEFINE(ComponentPlantLauncher, GameObject, RtClass);
	ComponentPlantLauncher(Plant* owner, Delegate0wRet<bool> OnSelected, Delegate0 OnDeselected, Delegate0 OnFiring, Delegate2wRet<bool, SexyVector3&, const PlantLauncherProps*> OnAboutToFireProjectile = nullptr, Delegate2<Projectile&, const PlantLauncherProps* > OnFiredProjectile = nullptr);
	ComponentPlantLauncher() : m_owner(nullptr), m_onlyTargetZombies(false), m_targetCursor(nullptr),  m_fireIgnoreBoardState(false), m_onSelected(nullptr), m_onDeselected(nullptr), m_onFiring(nullptr), m_cursorTextureName(""), m_onAboutToFireProjectile(nullptr), m_onFiredProjectile(nullptr)
	, m_weapon(WEAPON_SECONDARY){}
	void RegisterOwner(Plant* owner, Delegate0wRet<bool> OnSelected, Delegate0 OnDeselected, Delegate0 OnFiring, Delegate2wRet<bool, SexyVector3&, const PlantLauncherProps*> OnAboutToFireProjectile = nullptr, Delegate2<Projectile&, const PlantLauncherProps* > OnFiredProjectile = nullptr);
	
	void SetPlantWeapon(PlantWeapon i_weapon) { m_weapon = i_weapon; }
	void SetCanOnlyTargetZombies(bool i_x) { m_onlyTargetZombies = i_x; }
	void SetFireIgnoreBoardState(bool i_x) { m_fireIgnoreBoardState = i_x; }
	void SetCursorTexture(const std::string& cursorTextureName) { m_cursorTextureName = cursorTextureName; }
	
	void Fire(const Sexy::Point& i_targetLocation);
	void NotifySetHidden(bool i_newValue, bool i_oldValue);
	
	void OnApplyCondition(PlantConditions i_condition);

    bool onTouchEvent(const Sexy::Touch& i_touch);
    void onCursorDestroyed(BaseCursor* i_cursor);

	void RegisterForEvents();
	void unregisterForEvents() override;
	
	Delegate2<Projectile&, const PlantLauncherProps* > GetFireProjectileCallback() { return m_onFiredProjectile; }
	Delegate2wRet<bool, SexyVector3&, const PlantLauncherProps*> GetAboutToFireProjectileCallback() { return m_onAboutToFireProjectile; }
	RtWeakPtr<Plant> GetOwner() { return m_owner; }
	
    void setState(const int i_newState);
	bool select();
	void deselect();
	void forceStopSelection();
	bool canFire() const;

	void queueShot(pvztime_t i_launchTime, const Point& i_targetLocation, PlantWeapon i_weapon);

	bool m_onlyTargetZombies;
	bool m_fireIgnoreBoardState;

	// not serialized
	class PlantLauncherTargetCursor* m_targetCursor;
private:
	RtWeakPtr<Plant> m_owner;
	Delegate0 m_onDeselected, m_onFiring;
	Delegate0wRet<bool> m_onSelected;
	Delegate2<Projectile&, const PlantLauncherProps* > m_onFiredProjectile;
	Delegate2wRet<bool, SexyVector3&, const PlantLauncherProps* > m_onAboutToFireProjectile;
	std::string m_cursorTextureName;
	PlantWeapon m_weapon;
};

class PlantLauncherSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(PlantLauncherSubSystem, GameSubSystem, RtClass);
	
	struct PlantLauncherEntry
	{
		PlantLauncherEntry() {}
		PlantLauncherEntry(ComponentPlantLauncher* i_owner, pvztime_t i_launchTime, const Point& i_target, PlantWeapon i_weapon);
		
		RtWeakPtr<ComponentPlantLauncher> Owner;
		RtWeakPtr<Plant> PPlant;
		RtWeakPtr<const PlantLauncherProps> PlantLauncherPropertySheet;
		pvztime_t LaunchTime;
		Point Target;
		int Weapon;
	};

	void QueueShot(ComponentPlantLauncher* i_owner, pvztime_t i_launchTime, const Point& i_target, PlantWeapon i_weapon);
	void Update() override;
	
private:
	void launch(const PlantLauncherEntry& i_entry);
	std::vector<PlantLauncherEntry> m_shots;

};

#endif
