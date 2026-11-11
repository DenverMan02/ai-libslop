//
//  Plant_GoldLeaf.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 2/19/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_GoldLeaf__
#define __PlantsVersusZombies2__Plant_GoldLeaf__

#include <string>

#include "PlantFramework.h"
#include "PlantType.h"
#include "RtObject.h"

class GoldLeafProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(GoldLeafProps, PlantPropertySheet, RtClass);
	
	GoldLeafProps() {}
};

class PlantGoldLeaf : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantGoldLeaf, PlantFramework, RtClass);
	
	void Initialize() override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	
	bool IsInvincible() const override;
	bool CanBeShoveled() override;
	bool HasShadow() override;
	
	bool HasCreatedTile() const
	{
		return m_createdTile;
	}
	
	int		CalcRenderOrder() override;
private:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	void createTile();
	
	bool m_createdTile = false;
	bool m_hasShadow = true;
};

class PlantTypeGoldLeaf : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeGoldLeaf, PlantType, RtClass) {}
	
	// Gold tile turnips may rise in cost as the number of planted tiles increases
	//int GetCurrentCost() const override;
	
	// Gold tile turnips can be planted on top of almost anything
	void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
};

#endif /* defined(__PlantsVersusZombies2__Plant_GoldLeaf__) */
