/*
 * ZombieRenaiCarver.h
 *
 *  Created on: 2019-8-12
 *      Author: Administrator
 */

#ifndef ZOMBIERENAICARVER_H_
#define ZOMBIERENAICARVER_H_

#include <string>
#include "RtDb.h"
#include "RtObject.h"
#include "ZombieImp.h"
#include "ZombieAnimRig_Imp.h"

typedef RtWeakPtr<class GridItemRenaiStatue> GridItemRenaiStatuePtr;

// These states for zombie transforms each mode
STATE_ENUM_CHILD_BEGIN(ZombieState_Carver, ZombieStateImp)
	ZS_CARVER_CARVE,
STATE_ENUM_END(ZombieState_Carver)

class ZombieRenaiCarverProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieRenaiCarverProps, ZombiePropertySheet, RtClass);
};

class ZombieRenaiCarver : public ZombieImp
{
public:
	RT_CLASS_DEFINE(ZombieRenaiCarver, ZombieImp, RtClass);

	ZombieRenaiCarver();

protected:

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	DECLARE_STATE_FUNCTIONS(ZombieState, Carve);

	virtual void registerForEvents() override;

private:
	BoardEntity *FindEatTarget() override;
	BoardEntity* findStatue(int row, Rect attackRect);
	bool findStatue();
	bool shouldCarve();
	bool canCarveStatue(class GridItemRenaiStatue* i_statue);
	bool findAndCarveStatue();
	void TryCarveStatue();
	void OnNotifyStatueFinishCarve(class GridItemRenaiStatue* i_statue);

	// Transform states
	void onCarveAnimDone(const std::string& i_animLabelName);
	GridItemRenaiStatuePtr m_bindedStatue;
	//pvztime_t m_beginCarveTime;
};

class ZombieAnimRig_RenaiCarver : public ZombieAnimRig_Imp
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_RenaiCarver, ZombieAnimRig_Imp, RtClass);

	void PlayCarve(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayCarve();
protected:
	void onPopAnimInitialized() override;
	virtual const std::vector<std::string>& getHeadLayerNames() override;
};


#endif /* ZOMBIERENAICARVER_H_ */
