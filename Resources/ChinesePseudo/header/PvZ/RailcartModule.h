//
//  RailcartModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_RailcartModule_h
#define PlantsVersusZombies2_RailcartModule_h

#include "LevelModule.h"
#include "BoardEnums.h"
#include "PlantType.h"

class RailcartModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(RailcartModule, LevelModule, RtClass) {}

	RailcartModule()
	: m_drawRails(true)
	{
		// Do nothing.
	}
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

private:
	/// Private methods + members

protected:
	
	virtual void			registerForEvents() override;
	virtual void			onPostLoad() override;
	
private:

	void					onLoadComplete();
	void					gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
	
	void					placeRailsAndCarts();
    void					addToRenderQueue(class RenderQueue* i_queue);
    
	void					renderRails(Graphics* i_g);
	void					parseRailImages();
	void 				    onClearBoard();

	// Transient
	ImagePtr				m_railTop;
	ImagePtr				m_railMid;
	ImagePtr				m_railBottom;
	std::string				m_railcartTypeUsed;
	bool					m_drawRails;
};


struct RailcartRail
{
	int			Column;
	int			RowStart;
	int			RowEnd;
	RailcartRail():Column(-1), RowStart(-1), RowEnd(-1) {}
};
struct RailcartLocation
{
	int 		Column;
	int 		Row;
	RailcartLocation():Column(-1), Row(-1) {}
};

class RailcartProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(RailcartProperties, LevelModuleProperties, RtClass);
	
	RailcartProperties()
	{
		RailcartType = "";		// Use the stage's default rails
	}
	
	virtual RtClass* GetModuleClass() const override
	{
		return RailcartModule::StaticGetClass();
	}

	//virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const;
	std::string GetDefaultRailcartTypeName() const;

	std::string RailcartType;
	std::vector<RailcartRail> Rails;
	std::vector<RailcartLocation> Railcarts;
};

#endif
