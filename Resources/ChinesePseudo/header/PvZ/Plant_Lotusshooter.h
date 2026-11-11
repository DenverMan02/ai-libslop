/*
 * Plant_Lotusshooter.h
 *
 *  Created on: 2017-12-1
 *      Author: Administrator
 */

#ifndef PLANT_LOTUSSHOOTER_H_
#define PLANT_LOTUSSHOOTER_H_

#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"

class LotusshooterProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(LotusshooterProps, PlantPropertySheet, RtClass);

    LotusshooterProps()
	{
    	PoisonDuration = 5.0f;
    	PoisonDamage = 1.0f;
    	PlantFoodProjectileCount = 1;
		PlantFoodBeamDPS = 200.0f;
		PlantFoodBeamMovementRate = 100;
		PlantFoodBeamMaxTargetingAngleDegrees = 85.0f;
		PlantFoodBeamMaxTargetingDistance = 500.f;
		BeamDamageInterval = 1.0f;
		BeamDuration = 5.0f;
		BeamRate = 1.0f;
	}

    float PoisonDuration;
    float PoisonDamage;
    int PlantFoodProjectileCount;
    float PlantFoodBeamDPS;
	float PlantFoodBeamMovementRate;
	Sexy::Point PlantFoodBeamStartOffset;
	Sexy::Point PlantFoodOriginArtOffset;
	Sexy::Point PlantFoodBeamStartArtOffset;
	Sexy::Point PlantFoodBeamEndArtOffset;
	Sexy::Point PlantFoodHitEffectPivotOffset;
	float PlantFoodBeamMaxTargetingAngleDegrees;
	float PlantFoodBeamMaxTargetingDistance;
	float BeamDamageInterval;
	float BeamDuration;
	float BeamRate;
};

class LotusProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(LotusProjectile, Projectile, RtClass);

	virtual bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void SetIsPlantfood(bool i_plantfood) { m_plantfood = i_plantfood; }
protected:
	void onInitialized() override;
private:
	bool m_plantfood;
};

class LotusPoisonProjectile : public LotusProjectile
{
public:
	RT_CLASS_DEFINE(LotusPoisonProjectile, LotusProjectile, RtClass);

	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
};

class PlantLotusshooter : public PlantFramework
{
private:
	enum States
	{
		STATE_PLANTFOOD_FINALE  = STATE_FRAMEWORK_BEGIN,
	};
public:
	RT_CLASS_DEFINE(PlantLotusshooter, PlantFramework, RtClass);

	PlantLotusshooter();
	~PlantLotusshooter();

	virtual void			Initialize() override;
	virtual void 			AddToRenderQueue(class RenderQueue* i_queue) override;
	virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	virtual void			UpdatePlantfood() override;
	virtual void			CancelPlantfood() override;
	virtual bool			FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void 					UpdateUnconditionally() override;
	virtual void			UpdateActions() override;
	bool 					OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
private:
	bool CheckAbsorbPoison();

	void TryAbsorbPoison();

	void DoLevelSpecial(int state, PlantWeapon i_plantWeapon);

	virtual void	onAnimStoppedCallback(const std::string& i_animLabelName) override;

	enum BeamState
	{
		BEAMSTATE_INACTIVE,
		BEAMSTATE_ACTIVE,
		BEAMSTATE_DISABLING
	};

	bool shouldDrawPreviousBeam(Sexy::SexyVector2& i_currentPos, Sexy::SexyVector2& i_previousPos);
	Sexy::SexyVector2 boardToScreenSpace(const Sexy::SexyVector3& i_vector);
	Sexy::SexyVector2 artPointToScreenPoint(const Sexy::Point& i_artPoint);
	float getAngleForVector(const Sexy::SexyVector2& i_vector);
	BoardEntity* findClosestTarget();
	bool isTargetValid(BoardEntity* i_target);
	SexyVector2 getPositionForTarget(BoardEntity* i_target);
	void damageTarget(BoardEntity* i_damagedEntity, bool i_applyingPulseDamage);
	void positionBeamHitForBlasting(const SexyVector2& i_beamPivotScreenSpace);
	void setBeamState(BeamState i_newState);

	RtWeakPtr<GameObject> LoadPopanimEffect(std::string i_name, int i_renderLayer);

	RtWeakPtr<GameObject> LoadAvatarPopanimEffect(std::string i_name, int i_renderLayer);

	void drawMainBeamAndOrigin(Graphics *i_g);

	void drawLaserFromToScreenSpace(Graphics *i_graphics, const Sexy::SexyVector2 &i_from, const Sexy::SexyVector2 &i_to,
									const Sexy::SexyVector2 &i_startArtOffset, const Sexy::SexyVector2 &i_endArtOffset, Effect_PopAnim* i_beamRig);

	void drawLaserFromToScreenSpace(Graphics *i_graphics, const Sexy::SexyVector2 &i_from, const Sexy::SexyVector2 &i_to,
									const Sexy::SexyVector2 &i_startArtOffset, const Sexy::SexyVector2 &i_endArtOffset, Effect_PopAnim* i_beamRig, int alpha);

	LotusshooterPlantfood m_plantfood;

	bool m_absorbedPoison;
	int32 m_comboCount;
	int32 m_poisonBulletCount;

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
	int m_lastPulseDamageApplied;
	pvztime_t m_beamTimer;
	pvztime_t m_beamEndTime;
	bool m_superAttacking;
};

class PlantAnimRig_Lotusshooter : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Lotusshooter, PlantAnimRig, RtClass);

	void PlayAbsorb(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlaySuperAttack();
};

#endif /* PLANT_LOTUSSHOOTER_H_ */
