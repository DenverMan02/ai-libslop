#ifndef RoofMoudle_H
#define RoofMoudle_H

#include "LevelModule.h"


class RoofModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(RoofModule, LevelModule, RtClass);
    
	RoofModule();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames);
    
protected:
    
	void			registerForEvents() override;
	void			onPostLoad() override;
	
private:
    
    void            OnUpdate();
	void			OnLoadComplete();
    void            OnGamePlayStarted();
    void            OnPlantPlanted(class Plant* i_plant);
    void            OnZombieAddedToBoard(class Zombie* i_zombie);
    void			AddToRenderQueue(class RenderItem* i_renderQueue, int& io_renderQueueIndex);
	void			DoRender(Graphics* i_g);
};

class RoofProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(RoofProperties, LevelModuleProperties, RtClass);
	
	RoofProperties()
	:FlowerPotStartColumn(0),
	FlowerPotEndColumn(2)
	{

	}
	
	virtual RtClass* GetModuleClass() const
	{
		return RoofModule::StaticGetClass();
	}

	int FlowerPotStartColumn;
	int FlowerPotEndColumn;
};

#endif