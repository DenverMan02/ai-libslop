//
//  Plant_Jalapeno.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Jalapeno__
#define __PlantsVersusZombies2__Plant_Jalapeno__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"

class PlantJalapeno : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantJalapeno, PlantFramework, RtClass);

	virtual void	Initialize() override;
	virtual void	UpdateActions() override;
	virtual bool    HasShadow() override;
	virtual void	Draw(Graphics* g) override;
	
	void	Explode();

	bool	CanBeShoveled() override { return false; }
	bool	CanBeTargeted() override { return false; }
	bool	IsInvincible() const override { return true; }
	
    virtual void stopSpecialEffect() override;
    void onBeThrown() override {};
    
private:
    
    bool CanAttackInColumn();
    
private:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

	pvztime_t m_explodedAtTime = PVZ_EOT();
	int m_lastExplosionPropagationDistance = 0;
	std::vector<BoardEntity*> m_damagedEntities;
    
    std::vector<Effect_PopAnim*> m_effectAnims;
};

#endif /* defined(__PlantsVersusZombies2__Plant_Jalapeno__) */
