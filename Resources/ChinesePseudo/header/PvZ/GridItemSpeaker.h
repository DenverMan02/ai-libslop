//
//  GridItemSpeaker.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 8/12/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemSpeaker__
#define __PlantsVersusZombies2__GridItemSpeaker__

#include "GridItemBoardEntityConditionTarget.h"
#include "Projectile.h"

enum SpeakerState
{
	PVZ_BEGIN_ENUM(SPEAKERSTATE_),
	SPEAKERSTATE_RISING,
	SPEAKERSTATE_DROPPING,
	SPEAKERSTATE_IDLE,
	SPEAKERSTATE_PULSING,
	SPEAKERSTATE_ATTACKING,
    SPEAKERSTATE_BLASTING,
	SPEAKERSTATE_ROWCLEAR,
	PVZ_END_ENUM(SPEAKERSTATE_)
};

class GridItemSpeakerProps : public GridItemBreakableTargetProps
{
public:
	RT_CLASS_DEFINE(GridItemSpeakerProps, GridItemBreakableTargetProps, RtClass);
	int SonicDamageAmount = 100;
};

//
//  Basic speaker
//

class GridItemSpeaker : public GridItemBreakableTarget
{
public:
	RT_CLASS_DEFINE(GridItemSpeaker, GridItemBreakableTarget, RtClass);
	GridItemSpeaker();
	virtual ~GridItemSpeaker();
	bool IsDamageableByPlants() const override { return true; }
	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	
	void SetSpeakerDroppingIn();
    void SetSpeakerBlasting();
    void SetSpeakerIdle();
	
protected:
	SpeakerState m_speakerState = SPEAKERSTATE_RISING;
	SpeakerState m_audioTriggeredNextSpeakerState = SPEAKERSTATE_Invalid;
	EntityComponent_GroundEffect m_groundEffect;
	
	void shortRangeAttack();
	
	void onPostLoad() override;
	void onAnimEnded();
	virtual void onPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params);
	void onGridItemInitialize() override;
	void onUpdate() override;
	void onKilled() override;
	void onDestroy() override;
	virtual void setState(const SpeakerState i_state);
	void setRiseHeight(float i_arbitraryHeightLerpValue);
	
private:
	void spawnSpeakerShatterEffect(const SexyVector2& i_targetPosition, const std::string& i_animationName) const;
	
	void onMusicBarReceived();
	void onMusicBeatReceived();
	
	float m_risingTime = 0.0f;
};

//
//  Zomboss speaker
//

class GridItemSpeakerZombossProps : public GridItemSpeakerProps
{
public:
	RT_CLASS_DEFINE(GridItemSpeakerZombossProps, GridItemSpeakerProps, RtClass);
	SexyVector2 ShockWaveSpawnOffset;
};

class GridItemSpeakerZomboss : public GridItemSpeaker
{
public:
	RT_CLASS_DEFINE(GridItemSpeakerZomboss, GridItemSpeaker, RtClass);
	void ZombossLaneClear();

protected:
	void setState(const SpeakerState i_state) override;
	void onUpdate() override;
	void onGridItemInitialize() override;
	
	void onPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params) override;
	
private:
	void onFlashEnded();
	void createShockWave();
	SexyVector2 calcShockWaveSpawnPosition();
	
	bool m_wantsToClearLane = false;
};

//
//  Sonic projectile
//

class SpeakerProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(SpeakerProjectile, Projectile, RtClass);
	
	bool OnCollideEntity(BoardEntity* i_entity) override;
	std::vector<BoardEntityPtr> m_hitEntities;
};

//
//  Bass projectile
//

class BassSpeakerProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(BassSpeakerProjectile, Projectile, RtClass);
    
    bool OnCollideEntity(BoardEntity* i_entity) override;
};

#endif /* defined(__PlantsVersusZombies2__GridItemSpeaker__) */
