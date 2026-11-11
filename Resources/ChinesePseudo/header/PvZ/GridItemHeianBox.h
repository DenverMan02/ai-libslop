/*
 * GridItemHeianBox.h
 *
 *  Created on: 2020-11-25
 *      Author: admin
 */

#ifndef GRIDITEMHEIANBOX_H_
#define GRIDITEMHEIANBOX_H_

#include "GridItemAnimation.h"
#include "GridItemPropertySheet.h"

enum HeianBoxState
{
	PVZ_BEGIN_ENUM(BOXSTATE_),
	BOXSTATE_PREPARE,
	BOXSTATE_DISABLED,
	BOXSTATE_ACTIVATING,
	BOXSTATE_ACTIVATED,
	BOXSTATE_DISABLING,
	PVZ_END_ENUM(BOXSTATE_)
};

class GridItemHeianBox : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemHeianBox, GridItemAnimation, RtClass);

	GridItemHeianBox();

	int CalcRenderOrder() const override;
	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	void setState(HeianBoxState i_state);
	void registerForEvents() override;

	virtual bool Activate();

protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	void onAnimDone(const std::string &i_animLabel);

	bool canActivated();
	virtual void onActivated();

	bool OverrideProjectileCollision(Projectile* i_projectile) override;
	bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;

	virtual void updateState();

	HeianBoxState m_state;
};

// Heian Sun Box
class GridItemHeianBoxProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxProps, GridItemAnimationProps, RtClass);
};

class GridItemHeianBoxAnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxAnimRig, PopAnimRig, RtClass);

	void PlayBoxDisabled();
	void PlayBoxActivating(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayBoxActivated();
	void PlayBoxDisabling(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	virtual const std::string getDisabledAnimName();
	virtual const std::string getDisablingAnimName();
	virtual const std::string getActivatingAnimName();
	virtual const std::string getActivatedAnimName();
};

class GridItemHeianBoxSunProps : public GridItemHeianBoxProps
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxSunProps, GridItemHeianBoxProps, RtClass);

	GridItemHeianBoxSunProps()
	{
		ReturnFactor = 1.0f;
	}

	float ReturnFactor;
};

class GridItemHeianBoxSun : public GridItemHeianBox
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxSun, GridItemHeianBox, RtClass);

protected:
	void onActivated() override;
	void onSunBoxAnimDone(const std::string &i_animLabel);

private:
	std::vector<BoardEntity*> findTargets();
	void collecting();
};

class GridItemHeianBoxSunAnimRig : public GridItemHeianBoxAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxSunAnimRig, GridItemHeianBoxAnimRig, RtClass);

	void PlaySunBoxCollecting(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};

// Heian Plantfood Box
class GridItemHeianBoxPlantfoodProps : public GridItemHeianBoxProps
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxPlantfoodProps, GridItemHeianBoxProps, RtClass);

	GridItemHeianBoxPlantfoodProps()
	{
		DisableTime = 1.0f;
	}

	float DisableTime;
};

class GridItemHeianBoxPlantfood : public GridItemHeianBox
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxPlantfood, GridItemHeianBox, RtClass);

	GridItemHeianBoxPlantfood();

protected:
	void onActivated() override;
	void updateState() override;

private:
	std::vector<BoardEntity*> findTargets();
	void triggerPlantfood();

	pvztime_t m_endTime;
};

class GridItemHeianBoxPlantfoodAnimRig : public GridItemHeianBoxAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxPlantfoodAnimRig, GridItemHeianBoxAnimRig, RtClass);
};

// Heian LevelUp Box
class GridItemHeianBoxLevelUpProps : public GridItemHeianBoxProps
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxLevelUpProps, GridItemHeianBoxProps, RtClass);

	GridItemHeianBoxLevelUpProps()
	{
		AddLevel = 1;
	}

	int AddLevel;
	PlantingRestrictionSet DisabledPlants;
};

class GridItemHeianBoxLevelUp : public GridItemHeianBox
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxLevelUp, GridItemHeianBox, RtClass);

protected:
	void onActivated() override;
	void onLevelUpBoxAnimDone(const std::string &i_animLabel);

private:
	std::vector<BoardEntity*> findTargets();
	void levelUp();
};

class GridItemHeianBoxLevelUpAnimRig : public GridItemHeianBoxAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxLevelUpAnimRig, GridItemHeianBoxAnimRig, RtClass);

	void PlayBoxLevelUp(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};

// Heian SeedPacket Box
class GridItemHeianBoxSeedPacketProps : public GridItemHeianBoxProps
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxSeedPacketProps, GridItemHeianBoxProps, RtClass);

	GridItemHeianBoxSeedPacketProps()
	{
		DisableTime = 1.0f;
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<std::string> PresetList;
	float DisableTime;
};

class GridItemHeianBoxSeedPacket : public GridItemHeianBox
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxSeedPacket, GridItemHeianBox, RtClass);

	GridItemHeianBoxSeedPacket();

protected:
	void onActivated() override;
	void updateState() override;

private:
	void triggerSeedPacket();
	std::string pickRandomSeedPacket();

	pvztime_t m_endTime;
};

class GridItemHeianBoxSeedPacketAnimRig : public GridItemHeianBoxAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemHeianBoxSeedPacketAnimRig, GridItemHeianBoxAnimRig, RtClass);
};

#endif /* GRIDITEMHEIANBOX_H_ */
