/*
 * KongmingLantern.h
 *
 *  Created on: 2022-11-19
 *      Author:  huangzhisheng
 */

#ifndef KONGMINGLANTERN_H_
#define KONGMINGLANTERN_H_

#include "Wave.h"
#include "GridItemBoardEntityConditionTarget.h"

class GridItemKongmingLantern : public GridItemBoardEntityConditionTarget
{
public:
	RT_CLASS_DEFINE(GridItemKongmingLantern, GridItemBoardEntityConditionTarget, RtClass);

	GridItemKongmingLantern();
	virtual ~GridItemKongmingLantern();


protected:
	void onUpdate() override;
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return true; }
	virtual void onGridItemInitialize() override;
	virtual bool OverrideProjectileCollision(Projectile* i_projectile);
	void	TakeDamage(const DamageInfo& i_damage);

	bool	hitWithFrost();
	void	randomlySelectTarget();
	bool	checkAndKillPlants();
	void	onAnimStoppedCallback(const std::string& i_animLabel);

	enum m_status
	{
		normal,
		worn,
		Tottering
	};

private:
	int hitNumber;
	bool downing;
	bool hitting;
	Point m_targetPoint;
	int m_state;
};

class AnimRigKongmingLantern : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(AnimRigKongmingLantern , PopAnimRig, RtClass);

	bool playDown(std::string m_type ,PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool playHit(const std::string& i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool playDisappear(std::string m_type ,PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};

class GridItemBonfire : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemBonfire, GridItemAnimation, RtClass);

	void onUpdate() override;
	virtual void onGridItemInitialize() override;
	void	onAnimStoppedCallback(const std::string& i_animLabel);
	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

private:
	pvztime_t loopTime;
//	pvztime_t dieTime;
};

class AnimRigBonfire : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(AnimRigBonfire, PopAnimRig, RtClass);

	bool playAutoDisappear(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool playFireDisappear(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};


struct KongmingLanternData
{

	KongmingLanternData(){
		Row = 1;
	}

	int	Row;
};


class WaveActionKongmingLantern : public WaveAction
{
public:
	RT_CLASS_DEFINE(WaveActionKongmingLantern, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
	void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
};

class WaveActionKongmingLanternProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(WaveActionKongmingLanternProps, WaveActionProperties, RtClass);

	WaveActionKongmingLanternProps() {}
	RtClass* GetActionClass() const override { return WaveActionKongmingLantern::StaticGetClass(); }

	std::vector<KongmingLanternData> KongmingLanterns;
};


#endif /* KONGMINGLANTERN_H_ */
