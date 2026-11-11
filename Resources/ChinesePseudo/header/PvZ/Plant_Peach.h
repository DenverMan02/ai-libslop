//
//  Plant_Peach.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-12-2.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Peach__
#define __PlantsVersusZombies2__Plant_Peach__

#include "PlantFramework.h"
#include "RtObject.h"

class PlantPeach : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantPeach, PlantFramework, RtClass);
    
	virtual void	Initialize() override;
	virtual void	UpdateActions() override;
	virtual void	DoSpecial(int i_extraParam = 0) override;
	virtual bool	CanApplyPlantfood() override;
	virtual void	ApplyPlantfood() override;
	virtual void	CancelPlantfood() override;
    virtual void	CurePlant(const PlantAction& i_fromAction) override;
    virtual void    onDestroy() override;
    
    static bool     PlantCanBeCured(Plant * plant);
    
private:
    void            doTakeCure(Plant * plant);
    
    bool            IsPlantNeedCure();
    
    void            onPlantfoodStarted() override;
    
    void            setAroundInvincible(bool is_invincible);
    
    void            onAnimStoppedCallback(const std::string& strAnimLabel) override;
    
    void            PlayAttackUpEffect();
    
    bool            ShouldPlayAttactUpEffect();
    
    void            UpdateAttackUpValue();
};

#endif /* defined(__PlantsVersusZombies2__Plant_Peach__) */
