/*
 * Plant_CarrotMissile.h
 *
 *  Created on: 2014-8-5
 *      Author: jianglc
 */

#ifndef PLANT_CARROTMISSILE_H_
#define PLANT_CARROTMISSILE_H_

#include "PlantFramework.h"

class PlantCarrotMissile : public PlantFramework
{

public:

	RT_CLASS_DEFINE(PlantCarrotMissile, PlantFramework, RtClass);

public:

	virtual void	Initialize() override;

	virtual bool	CanApplyPlantfood() override;

	virtual bool 	CanBeShoveled() override;

	virtual void 	onKilled(bool i_instantKill) override;

	virtual bool	HasShadow() override;

	virtual void 	UpdateActions() override;

	void PlayIdleAnim(bool i_avatar);

	virtual void    onBeThrown() override;

	virtual void    onBePushed() override;
private:
	bool m_isAvatar = false;
};


#endif /* PLANT_CARROTMISSILE_H_ */
