//
//  Plant_Squash.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 11/2/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Squash_h
#define PlantsVersusZombies2_Plant_Squash_h

#include "PlantFramework.h"
#include "StandaloneEffect.h"

class PlantSquash : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSquash, PlantFramework, RtClass);

	// Public Interface (Inheritable)
    
    virtual void				Initialize() override;
	virtual void				UpdateActions() override;

	virtual bool				CanApplyPlantfood() override;
	virtual void				ApplyPlantfood() override;
	virtual void				CancelPlantfood() override;
	
	virtual int					CalcRenderOrder() override;
	bool                        CanBeTargeted() override;
    virtual CollisionTypeFlags	GetCollisionFlags(PlantWeapon i_plantWeapon) override;
	virtual SexyVector2			GetShadowOffset() override;
	virtual bool				IsInvincible() const override;
	virtual bool				CanBeShoveled() override;
    
    virtual bool				BlockRailcartMovement() const override;
    bool 						HasGravity() override;
    
    void registerForEvents() override;
	void unregisterForEvents() override;
    void Idle() override;
    ZombiePtr getJumpLeft() const {return m_targetZombie;}
    
protected:
	virtual bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	virtual void onDestroy() override;
	
private:

	// Private Interface (Core)
    void onAnimStoppedCallback(const std::string&) override;

	void						onAnimTurnFinished(const std::string& i_animLabel);
	void						onAnimLandingFinished(const std::string& i_animLabel);

    void						blockGravestoneSpawning(const Sexy::Point& i_gridPosition, bool* o_blocked);
	void						pickPlantfoodDestination();
	void						travelToJumpUpDestination();
	void						travelToLandingDestination();
	void						dealDamageToLandingArea();
	void						calculatePlantfoodJumps();
	void						playAnimation(const std::string& i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_delegate = PopAnimRig::AnimStoppedReflectionDelegate());
    void						gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
	
    void						setState(uint i_plantState);
    void						backToStartPoint();
    void						recoverStartState();
    void                    onPlantPlacedOnBoard(Plant* i_plant);
	// Private Members (serialized)

	int							m_originalColumn;
	int							m_originalRow;
	SexyVector3					m_startPos;
	SexyVector3					m_endPos;
	int							m_plantfoodJumpsLeft;
	int							m_hitZombies;
	StandaloneEffectPtr			m_plantfoodEffect;
	ZombiePtr					m_targetZombie;
	bool						m_bBackToStartPoint;
	
};


#endif
