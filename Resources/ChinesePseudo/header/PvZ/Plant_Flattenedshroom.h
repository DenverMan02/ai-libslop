/*
 * Plant_Flattenedshroom.h
 *
 *  Created on: 2017-11-29
 *      Author: Administrator
 */

#ifndef PLANT_FLATTENEDSHROOM_H_
#define PLANT_FLATTENEDSHROOM_H_

#include <stdio.h>

#include <string>

#include "PopAnimRig.h"
#include "PlantAnimRig.h"
#include "PlantFramework.h"
#include "RtObject.h"

class FlattenedshroomProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(FlattenedshroomProps, PlantPropertySheet, RtClass);

    int ReadyDecPercent = 0;
    float TimeUntilSubmerge = 15.f;
    float BlockTime = 5.0f;
};

class PlantTypeFlattenedshroom : public PlantType
{
public:
    RT_CLASS_DEFINE(PlantTypeFlattenedshroom, PlantType, RtClass) {}

    void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
};

class PlantFlattenedshroom : public PlantFramework
{
private:
	enum State
	{
		STATE_NORMAL = STATE_FRAMEWORK_BEGIN,
		STATE_UNDERGROUNDING,
		STATE_UNDERGROUNDED,
		STATE_EXPLODING,
		STATE_FLYING,
	};

public:
	RT_CLASS_DEFINE(PlantFlattenedshroom, PlantFramework, RtClass);

	void Initialize() override;

	virtual bool	OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	virtual bool	CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	virtual void	CancelPlantfood() override;
	virtual void	UpdateActions() override;
	//virtual void	UpdateActions() override;
	void FlyThroughAir(SexyVector2 i_startPixelLoc, SexyVector2 i_destPixelLoc);
	virtual void 	OnRelocationComplete() override;
	float GetBlockTime();
private:
	bool DoDuplicate();
	std::vector<Point> GetSplitLocations();
	bool m_isOnPot;
};

enum PlantAnimRigState_Flattenedshroom
{
	PLANTANIM_FLATTENEDSHROOM_PLANTED = PLANTANIM_USERDEFINED,
	PLANTANIM_FLATTENEDSHROOM_SUBMERGE,
};

class PlantAnimRig_Flattenedshroom : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Flattenedshroom, PlantAnimRig, RtClass);

	typedef PopAnimRig::AnimStoppedReflectionDelegate EmergeAnimDone;

	virtual bool PlayInitialFrame() override;
	//virtual bool PlayIdleLooped() override;
	virtual bool PlaySubmergeIntoGround(EmergeAnimDone i_onEmergeDone = EmergeAnimDone());
	virtual bool PlaySubmergeIntoGroundFast(EmergeAnimDone i_onEmergeDone = EmergeAnimDone());
	virtual bool PlaySpinningPotato();
	virtual std::string getIdleAnimationName() override;

	bool PlayPreviewAnim(bool bHideLayer = false) override;

	void SetSubmerged(bool i_submerged);

protected:
	virtual void onPopAnimInitialized() override;

	bool m_submerged;
};

#endif /* PLANT_FLATTENEDSHROOM_H_ */
