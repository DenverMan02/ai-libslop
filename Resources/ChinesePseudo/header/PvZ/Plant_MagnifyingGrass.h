//
//  Plant_MagnifyingGrass.h
//  PlantsVersusZombies2
//
//  Created by jsola on 8/27/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_MagnifyingGrass_h
#define PlantsVersusZombies2_Plant_MagnifyingGrass_h

#include "Precompile.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "TimeMgr.h"
#include "Projectile.h"

struct PrismBeamTracker
{
	friend class PlantMagnifyingGrass;
	
	void InitBeam(Plant* i_originatingPlant, Plant* i_targetMagnifyingGrass, Color i_color, pvztime_t i_startTime, pvztime_t i_endTime, pvztime_t i_pulseTravelTime, const MagnifyingGrassProps* props);
	void GetBeamEndPoints(SexyVector3& o_startLoc, SexyVector3& o_endLoc) const;
	Color GetColor() const;
	
	bool IsBeamVisible() const;
	bool IsPulseVisible() const;
	float GetPulseProgress() const;
	bool IsContracting() const;
	bool IsDone() const;
	void PlayContractionSound();
	
	Plant* GetOriginatingPlant() const;

private:
	PlantPtr		m_originatingPlant;			// The plant (probably a sunflower) that this originates from
	PlantPtr		m_targetMagnifyingGrass;	// The magnifying grass it's going towards
	Color			m_color;					// Coloring
	SexyVector3		m_startLoc;					// Board space start and end location of the beam
	SexyVector3		m_endLoc;
	pvztime_t		m_startExtendTime;
	pvztime_t		m_endExtendTime;
	pvztime_t		m_startContractTime;
	pvztime_t		m_endContractTime;
	pvztime_t		m_startPulseTime;
	pvztime_t		m_endPulseTime;
	bool			m_playedContractionSound;
};

class MagnifyingGrassProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(MagnifyingGrassProjectile, Projectile, RtClass);
    
    MagnifyingGrassProjectile()
    {
        chargeAttack = false;
        ratioAttack  = 1.0f;
    }
    
    void SetChargeAttack(bool i_chargeAttack, float i_ratioAttack);
    
protected:    
    virtual void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;
    
private:
    bool chargeAttack;
    float ratioAttack;
};

class PlantMagnifyingGrass : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantMagnifyingGrass, PlantFramework, RtClass);
	
	PlantMagnifyingGrass();
	~PlantMagnifyingGrass();

	void Initialize() override;
	void Draw(Graphics* g) override;
    virtual void AddToRenderQueue(class RenderQueue* i_queue) override;

    virtual class Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

	void UpdateUnconditionally() override;

	void SetTouchEnabled(bool i_enabled);
    
    bool GetChargeAttack() const
    {
        return m_bChargeAttack;
    }
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    virtual void AutoFire() override;
    void Idle() override;
	bool tryFireRegularShot(bool i_isFree);
private:
	BoardEntity* findClosestTarget();
    bool isTargetValid(BoardEntity* i_target);
	SexyVector2 getPositionForTarget(BoardEntity* i_target);
	void damageTarget(BoardEntity* i_damagedEntity, bool i_applyingPulseDamage);
	void positionBeamHitForBlasting(const SexyVector2& i_beamPivotScreenSpace);
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
	
	void drawMainBeamAndOrigin(Graphics *i_g);
	void drawSunProducerBeams(Graphics *i_g);
	
	void drawSunSuck(Sexy::Graphics *i_g);
	void startSunSuck();
    
    bool DoTapAttack();

	void drawLaserFromTo(class Graphics *i_graphics, const Sexy::SexyVector3 &i_from, const Sexy::SexyVector3 &i_to,
						 const Sexy::Point &i_startArtOffset, const Sexy::Point &i_endArtOffset, class Effect_PopAnim* i_beamRig);
	void drawLaserFromToScreenSpace(Graphics *i_graphics, const Sexy::SexyVector2 &i_from, const Sexy::SexyVector2 &i_to,
									const Sexy::SexyVector2 &i_startArtOffset, const Sexy::SexyVector2 &i_endArtOffset, Effect_PopAnim* i_beamRig);
	
	void drawLaserFromToScreenSpace(Graphics *i_graphics, const Sexy::SexyVector2 &i_from, const Sexy::SexyVector2 &i_to,
									const Sexy::SexyVector2 &i_startArtOffset, const Sexy::SexyVector2 &i_endArtOffset, Effect_PopAnim* i_beamRig, int alpha);
	
	RtWeakPtr<GameObject> LoadPopanimEffect(std::string i_name, int i_renderLayer);
    
    RtWeakPtr<GameObject> LoadAvatarPopanimEffect(std::string i_name, int i_renderLayer);

	enum BeamState
	{
		BEAMSTATE_INACTIVE,
		BEAMSTATE_ACTIVE,
		BEAMSTATE_DISABLING
	};
	
	void setBeamState(BeamState i_newState);
	void buildPrismBeams();
	
	bool onTouchEvent(const Sexy::Touch& i_touch);
    void ClearTouch();
    
	void onCancelEvent();
	void spendSun();
    
    int  GetSunMoneyPerShot();

	bool m_doingTapShot;
	pvztime_t m_sunSuckStartTime;
	
	BeamState m_beamState;
	
	Sexy::SexyVector2 m_lastBeamEnd;
	Sexy::SexyVector2 m_previousBeamEnd;
	
	SexyVector2 m_beamTargetPositionBoardSpace;
	SexyVector2 m_beamCurrentPositionBoardSpace;
	BoardEntityPtr m_previousBeamTarget;
	SexyVector2 m_originPivotPoint;
	RtWeakPtr<class Effect_PopAnim> m_beamRig;
	RtWeakPtr<class Effect_PopAnim> m_beamHitRig;
	RtWeakPtr<class Effect_PopAnim> m_beamInRig;
	RtWeakPtr<class Effect_PopAnim> m_beamOriginRig;
	
    Sexy::TouchID       m_touchIdent;
    pvztime_t 			m_touchStartTime;
	bool                m_touchEnabled;
    
    bool                m_bChargeAttack;

	std::vector<PrismBeamTracker> m_prismBeams;
	int m_lastPulseDamageApplied;
	
	int m_sunSpentByGrass;
};

#endif
