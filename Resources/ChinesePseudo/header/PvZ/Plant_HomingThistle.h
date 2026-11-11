//
//  Plant_HomingThistle.h
//  PlantsVersusZombies2
//
//  Created by Andrew Khosravian on 7/8/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __Plant_HomingThistle__
#define __Plant_HomingThistle__

#include "PlantFramework.h"
#include "RtObject.h"
#include "Projectile.h"
#include "BoardEntity.h"

class HomingThistleProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(HomingThistleProps, PlantPropertySheet, RtClass);
	
	HomingThistleProps()
	{
		ThistlePlantfoodMinTargets = 10;
		ThistlePlantfoodUnaimedRepeatCount = 5;
		ThistleUnaimedOffsetStart = -8;
		ThistleAimedOffsetStart = -4;
		ThistleUnaimedSlotDegrees = 15;
	}
	
	int ThistlePlantfoodMinTargets;
	int ThistlePlantfoodUnaimedRepeatCount;
	int ThistleUnaimedOffsetStart;
	int ThistleAimedOffsetStart;
	int ThistleUnaimedSlotDegrees;
};

class PlantHomingThistle : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantHomingThistle, PlantFramework, RtClass);

    PlantHomingThistle();

    virtual void				Initialize() override;
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	void UpdateUnconditionally() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	int	GetPlantFoodPlayCount() override;
    
    virtual void		UpdateActions() override;

private:
	ZombiePtr FindTargetZombie(Rect& i_rect, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
	class HomingThistleLeaf* fireRotatedProjectile(PlantWeapon i_plantWeapon, int i_forwardSlotOffset);
	
	bool m_hasTarget;
	BoardEntityPtr m_target;
	int m_pfTargetIndex;
	int m_pfShotIndex;
    int m_iRemainProjs;
    pvztime_t m_RemainProjTime;
	std::vector<RtWeakPtr<BoardEntity> > m_pfTargets;
};

class PlantAnimRig_HomingThistle : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_HomingThistle, PlantAnimRig, RtClass);

	PlantAnimRig_HomingThistle();

private:

	std::string getPlantFoodOnAnimName() override;
	std::string getPlantFoodMainAnimName() override;
	std::string getPlantFoodOffAnimName() override;
};

class HomingThistleLeafProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(HomingThistleLeafProps, ProjectilePropertySheet, RtClass);

	HomingThistleLeafProps()
	{
        MaxRotationsPerSecond = 1.0;
	}

	float MaxRotationsPerSecond;
};

class HomingThistleLeaf : public Projectile
{
public:
	RT_CLASS_DEFINE(HomingThistleLeaf, Projectile, RtClass);

	HomingThistleLeaf();

	void SetOverrideTarget(BoardEntity* i_overrideTarget);
	void SetRotatedVelocity(float i_magnitude);
	
protected:

	void onDeflection(class BoardEntity* i_deflector) override;
	void moveThroughTime(pvztime_t i_dt) override;
    void getCollisionEntities(std::vector<BoardEntity*> &o_entities,const Rect& i_projectileRect) const override;
    
    float calcDesiredRot(SexyVector3 i_toTarget, float i_currentRot);
    SexyVector3 GetTargetPos(BoardEntity* i_target);    
    bool OnCollideEntity(BoardEntity* i_entity) override;
    
	RtWeakPtr<BoardEntity> m_overrideTarget;
	bool m_deflected;
};


#endif
