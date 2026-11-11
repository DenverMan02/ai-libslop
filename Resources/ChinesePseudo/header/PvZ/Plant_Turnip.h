//
//  Plant_Turnip.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang & Jonathan Han on 13-11-29.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Turnip__
#define __PlantsVersusZombies2__Plant_Turnip__

#include "PlantFramework.h"
#include "RtObject.h"



class PlantTurnip : public PlantFramework
{
private:
	enum State
	{
		STATE_PLANTED = STATE_FRAMEWORK_BEGIN,
		STATE_RISING,
		STATE_FLYING,
		STATE_DEFENDING,
		STATE_DEFENDING_BLADEKEE,
        STATE_ATTACKRIGHT,
        STATE_ATTACKLEFT,
        STATE_PREPAREATTACK,
        STATE_RESUMEIDLE,
	};

public:
	RT_CLASS_DEFINE(PlantTurnip, PlantFramework, RtClass);
    
    PlantTurnip();
	
	virtual void	Initialize() override;
	virtual void	UpdateActions() override;

	virtual bool	CanApplyPlantfood() override;
	virtual void	ApplyPlantfood() override;
	virtual void	CancelPlantfood() override;

    virtual Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
    
	void DefendBladeKee();
	void FlyThroughAir(SexyVector2 i_startPixelLoc, SexyVector2 i_destPixelLoc);

	virtual bool	OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	virtual void 	OnRelocationComplete() override;

	static bool WhetherCanBePulled(const Plant* i_plant, int i_endCol);
    
protected:
	virtual void	onDestroy() override;
    
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

private:
	bool findHighestPriorityPlantableRow(int& o_row) const;
	bool findPlantableSpotColumn(int i_row, int i_columnPreferred,  int& o_column) const;
	void CreateAndflyTurnipAt(const Point& i_targetPosition) const;
	void OnPlantAbsorbed(const Point& i_gridPos, pvztime_t i_absorbDuration);

    bool FindTargets();
    GridItem* GetGridItemTarget(bool i_left);
	ZombiePtr GetZombieTarget(bool i_left);
    
    void TakeAttack();
    
    bool m_searchingLeft;
	pvztime_t m_defendDuration;
};




#endif /* defined(__PlantsVersusZombies2__Plant_Turnip__) */
