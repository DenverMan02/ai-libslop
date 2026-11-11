/*
 * 	GridItemWizardCrucible.h
 *
 * 	Created on:	2022-5-27
 * 		Author:	kkdud
 */

#ifndef PLANTSVERSUSZOMBIES2_PVZ2_GRIDITEMWIZARDCRUCIBLE_H_
#define PLANTSVERSUSZOMBIES2_PVZ2_GRIDITEMWIZARDCRUCIBLE_H_

#include "GridItemBreakableTarget.h"
#include "GridItemPropertySheet.h"
#include "EffectObject.h"


enum WizardCrucibleState
{
	PVZ_BEGIN_ENUM(CRUCIBLE_),
	CRUCIBLE_PREPARE,
	CRUCIBLE_DISABLED,
	CRUCIBLE_ACTIVATING,
	CRUCIBLE_ACTIVATED,
	CRUCIBLE_DISABLING,
	CRUCIBLE_DYING,
	PVZ_END_ENUM(CRUCIBLE_)
};

class GridItemWizardCrucible : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemWizardCrucible, GridItemAnimation, RtClass);

	GridItemWizardCrucible();

	int CalcRenderOrder() const override;
	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	void setState(WizardCrucibleState i_state);
	void registerForEvents() override;

	virtual bool Activate();
	bool tryToTrigger(std::string i_inPlantTypeName);
	void setValues(float i_boilingDuration, float i_explodeDamageAmount, float i_venomDamageAmountPerSecond, float i_venomExistDuration);

protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	void onAnimDone(const std::string &i_animLabel);
	void TakeDamage(const DamageInfo& i_damage) override;
	bool canActivated();
	virtual void onActivated();
	bool canDoTrigger(std::string i_inPlantTypeName);

	bool OverrideProjectileCollision(Projectile* i_projectile) override;
	bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;
	void onDestroy() override;

	virtual void updateState();

	WizardCrucibleState m_state;

private:
	void triggerRarityUpgrade();
	std::string pickRandomSeedPacket();
	void initializePlantTypeNameList();
	bool checkPlantTypeNameListVector();
	void explode();
	void outflowVenom();

	pvztime_t m_endTime;
	float m_boilingDuration;
	float m_explodeDamageAmount;
	float m_venomDamageAmountPerSecond;
	float m_venomExistDuration;
	bool m_hasExploded;

	std::string m_currentUpgradePlantTypeName;

	std::vector<std::vector<std::string>> m_plantTypeNameListVector;

};


class GridItemWizardCrucibleProps : public GridItemBreakableTargetProps
{
public:
	RT_CLASS_DEFINE(GridItemWizardCrucibleProps, GridItemBreakableTargetProps, RtClass);

	std::vector<std::string> CannotGetPlantTypeName;
};

class GridItemWizardCrucibleAnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemWizardCrucibleAnimRig, PopAnimRig, RtClass);

	void PlayCrucibleDisabled();
	void PlayCrucibleActivating(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayCrucibleActivated();
	void PlayCrucibleDisabling(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayCrucibleDying(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	const std::string getDisabledAnimName();
	const std::string getDisablingAnimName();
	const std::string getActivatingAnimName();
	const std::string getActivatedAnimName();
	const std::string getDyingAnimName();
};

class EffectObject_WizardCrucibleVenom : public EffectObject
{
public:
	RT_CLASS_DEFINE(EffectObject_WizardCrucibleVenom, EffectObject, RtClass);

	void onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY) override;
	void onUpdate() override;
	void setVrnomValues(Rect i_rect, float i_time, float i_dps);
	void onDraw(class Graphics* i_g) override;

private:
	Rect m_effectGridRect;
	float m_existDuration;
	float m_venomDps;
};

#endif /* PLANTSVERSUSZOMBIES2_PVZ2_GRIDITEMWIZARDCRUCIBLE_H_ */
