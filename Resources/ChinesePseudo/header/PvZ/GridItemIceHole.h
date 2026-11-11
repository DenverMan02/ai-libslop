//
//  GridItemIceHole.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-9-11.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GridItemIceHole_h
#define PlantsVersusZombies2_GridItemIceHole_h

#include "GridItem.h"

class GridItemIceHolePropertySheet : public GridItemPropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemIceHolePropertySheet, GridItemPropertySheet, RtClass);
    
	GridItemIceHolePropertySheet()
	{}
    
    std::string PopAnim;
};

class GridItemIceHole : public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemIceHole, GridItem, RtClass);
    
	GridItemIceHole();
    virtual ~GridItemIceHole();
    
	bool IsDamageableByPlants() const override { return false; }
	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
    
protected:
	void registerForEvents() override;
	void onGridItemInitialize() override;
	void onUpdate() override;
    void onDraw(class Sexy::Graphics* i_g) override;
    
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
	void TakeDamage(const DamageInfo& i_damage) override;
    
    int CalcRenderOrder() const override;
    
private:
    
    void RenderFoodInEnd(const std::string& strLabel);
    
    void RenderFoodEnd(const std::string& strLabel);
    
private:
    
    RtWeakPtr<class EffectAnimRig_IceHole> m_pRenderRig;
    bool m_bHoleRunning;
    int  m_iDamageZombieCount;
};


class EffectAnimRig_IceHole : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_IceHole, PopAnimRig, RtClass);
    
    EffectAnimRig_IceHole();
    
    virtual ~EffectAnimRig_IceHole();
    
    void PlayFoodIn(AnimStoppedDelegate endCall);
    
    void PlayFood(AnimStoppedDelegate endCall);
};


#endif
