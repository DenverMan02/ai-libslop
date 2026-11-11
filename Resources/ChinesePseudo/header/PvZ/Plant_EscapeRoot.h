//
//  Plant_EscapeRoot.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 12/14/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_EscapeRoot__
#define __PlantsVersusZombies2__Plant_EscapeRoot__

#include <string>

#include "AnimRigLayerSet.h"
#include "BaseCursor.h"
#include "ComponentDamageRadius.h"
#include "Core.h"
#include "EffectObject.h"
#include "Plant.h"
#include "PlantAnimRig.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "ZombieEnums.h"
#include "GameSubSystem.h"

namespace Sexy
{
	class Point;
} // namespace Sexy

enum AttackPlantType
{
	PLANT_INVALID = -1,
	PLANT_POTATOMINE,
	PLANT_PRIMALPOTATOMINE,
	PLANT_CHERRYBOMB,
	PLANT_GRAPESHOT,
	PLANT_COUNT
};

class PlantWeights : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(PlantWeights, ObjectTypeDescriptor, RtClass);
	
	PlantWeights()
	{
		Weight = 0;
		PlantTypeName = "";
	}
	
	std::string PlantTypeName;
	int Weight;
};

class EscapeRootProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(EscapeRootProps, PlantPropertySheet, RtClass);
	
    EscapeRootProps();
    
	float TimeUntilArmed;
	float SwapCooldownTime;
	int PlantfoodAttackCount;
    int ReduceTimeUntilArmedPercent;
	std::vector<PlantWeights> ExplodingPlantWeights;
	PlantingRestrictionSet UnswappablePlants;
};

class PlantEscapeRoot : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantEscapeRoot, PlantFramework, RtClass);
	
private:
	enum State
	{
		SELF_STATE_NOTREADY = STATE_FRAMEWORK_BEGIN,
		STATE_RISING,
		STATE_ARMED,
		STATE_EXPLODING
	};
	
public:
	void Initialize() override;
	void UpdateActions() override;
	bool CanApplyPlantfood() override;
	bool CanEndPlantfood() override { return false; }
	void CancelPlantfood() override;
	bool HasShadow() override;
	void TakeSmashAttack(ZombiePtr i_srcZombie) override;
	
	CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override { return (COLLIDE_GROUND_ZOMBIES | COLLIDE_DYING_ZOMBIES); }

	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;

	bool CanBeShoveled() override;
	bool IsInvincible() const override;
	bool TryBlockPushOffBoard(Zombie* i_srcZombie, const int i_direction) override;
    SexyVector3 GetFireOriginOffset(const PlantAction& i_action, float i_plantScale) override;
    
	bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	
	void SwapPlantAt(Point i_boardPos);
	void RevealSwappedPlant();
	void BeginRemoteExplosion(Point i_gridLoc);
	void swapPlants();
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	void onApplyCondition(PlantConditions i_condition) override;
	
	void onDestroy() override;

private:
	void registerForEvents() override;
	void unregisterForEvents() override;
	
	void wrapTargetPlant();
	
	bool onTouchEvent(const Sexy::Touch& i_touch);
	void onCursorDestroyed(BaseCursor* i_cursor);
	bool canBeSelected();
	bool select();
	void deselect();
	void resetState();

	bool shouldExplodeBecauseShovedOffBoard(const int i_direction);
	void onExplosionBegun();
	void performPlantfoodAttack();
	Point calcTargetGridLoc();
	void setAttackType();
	PowerContext calcContextForAttackType(AttackPlantType i_attackType);
	AttackPlantType calcAttackType(std::string i_attackTypeName);
	void playPlantfoodExplosionEffect(Point i_targetLoc);
	void explode();
	void playExtraCherrybombAnim();
	void spawnGrapes();
	SexyVector3 calcPlantfoodOffset(Point i_targetLoc);
	void localPlantfoodAttack();
	void remotePlantfoodAttack(Point i_targetLoc);
    ComponentDamageRadiusProps GetComponentDamageRadiusProps();
	
	bool m_isSelected;
	pvztime_t m_maySelectAfter;
	int	m_currentPFAttackCount;
	SexyVector3 m_plantfoodOffset;
	AttackPlantType	m_attackType;
	
	RtWeakPtr<Plant> m_targetPlant;
	
	// not serialized
	class EscapeRootCursor* m_targetCursor;

RtWeakPtr<ComponentDamageRadius> m_explodeRadius;
};

enum PlantAnimRigState_EscapeRoot
{
	PLANTANIM_ESCAPEROOT_PLANTED = PLANTANIM_USERDEFINED,
	PLANTANIM_ESCAPEROOT_EMERGE,
};

class PlantAnimRig_EscapeRoot : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_EscapeRoot, PlantAnimRig, RtClass);
	
	bool PlayInitialFrame() override;
	bool PlayIdleLooped() override;
	bool PlayEmergeFromGround(PopAnimRig::AnimStoppedReflectionDelegate i_onEmergeDone = PopAnimRig::AnimStoppedReflectionDelegate());
	bool PlayBurrow(PopAnimRig::AnimStoppedReflectionDelegate i_onBurrowDone = PopAnimRig::AnimStoppedReflectionDelegate());
	bool PlayBurrowIdleLooped();
	bool PlaySelected();
	bool PlayPreviewAnim(bool bHideLayer = false) override;
    
	bool RevealPlant(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PFRevealPlant(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}) override;
	
	void SetSubmerged(bool i_submerged) { m_submerged = i_submerged; }
	void SetSelected(bool i_selected) { m_selected = i_selected; }
	void SetAttackType(AttackPlantType i_attackType) { m_attackType = i_attackType; }
	
	void AddLayerSet(std::string setName, std::vector<std::string> layerNames);
	void ShowLayerSet(std::string setName);
	
protected:
	void onPopAnimInitialized() override;
	std::string getPlantFoodOnAnimName() override;
	
private:
	void onInitialPlantDone(const std::string &name);
	void onSelectedDone(const std::string &name);
	void showCorrectPlant();
	
	bool m_submerged;
	bool m_selected;
	AttackPlantType m_attackType;
	AnimRigLayerSet m_layerSet;
};

class EscapeRootCursor : public BaseCursor
{
public:
	RT_CLASS_DEFINE(EscapeRootCursor, BaseCursor, Sexy::RtClass) {}
	
	EscapeRootCursor() {}
	explicit EscapeRootCursor(const Sexy::Touch& i_boardSpaceTouch, PlantEscapeRoot* i_bananaPlant);
	virtual ~EscapeRootCursor();
	
	const PlantEscapeRoot* GetEscapeRootPlant() const { return m_escapeRootPlant; }
	
protected:
	Sexy::SexyVector2 getCursorAnimOffset() const override;
	bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
	
private:
	void onPlantDied(Plant* i_plant);
	
	Sexy::SexyVector2 m_cursorOffset;
	PlantEscapeRoot* m_escapeRootPlant;
};

class EffectObject_TargetPlant : public EffectObject
{
public:
	RT_CLASS_DEFINE(EffectObject_TargetPlant, EffectObject, RtClass);
	~EffectObject_TargetPlant();
	
	void SetOwner(RtWeakPtr<BoardEntity> i_owner);
	void SetAttackType(AttackPlantType i_attackType) { m_attackType = i_attackType; }
	void PlayRetract();
	void PlayEmerge();
	
	void AddLayerSet(std::string setName, std::vector<std::string> layerNames);
	void ShowLayerSet(std::string setName);
	
protected:
	void onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY) override;
	void onAnimStopped(const std::string &i_animLabel) override;
	void onUpdate() override;
	
private:
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);
	void showCorrectPlant();
	void enableCorrectCostume();
	
	RtWeakPtr<Plant> m_owner;
	AttackPlantType m_attackType;
	Point m_targetGridLoc;
	AnimRigLayerSet m_layerSet;
};

class EscapeRootSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(EscapeRootSubSystem, GameSubSystem, RtClass);
    
    EscapeRootSubSystem();
    virtual ~EscapeRootSubSystem();
    
    bool AddPlant(RtWeakPtr<Plant> i_plant);
private:
    std::vector<RtWeakPtr<Plant>> m_plants;
};

#endif /* defined(__PlantsVersusZombies2__Plant_EscapeRoot__) */