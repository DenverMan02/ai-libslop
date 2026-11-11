//
//  TMZeroModule.h
//  PlantsVersusZombies2
//
//  Created by Lang Nan on 15-7-8.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TMZeroModule__
#define __PlantsVersusZombies2__TMZeroModule__

#include "LevelModule.h"
#include "BoardEnums.h"
#include "PlantType.h"
#include "BoardConstants.h"
#include "Plant.h"


class TMZeroModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(TMZeroModule, LevelModule, RtClass);
    
	TMZeroModule();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames);
    
protected:
    
	void			registerForEvents() override;
	void			onPostLoad() override;
	
private:
    
    bool            HandleTouch(Sexy::Touch* i_touch);
    void            CancelTouch();
    void            OnUpdate();
	void			OnLoadComplete();
    void            OnGamePlayStarted();
    void            OnPlantPlanted(class Plant* i_plant);
    void            OnZombieAddedToBoard(class Zombie* i_zombie);
    bool            OnWinCondition();
    void			AddToRenderQueue(class RenderItem* i_renderQueue, int& io_renderQueueIndex);
	void			DoRender(Graphics* i_g);
};

class TMZeroProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(TMZeroProperties, LevelModuleProperties, RtClass);
	
	TMZeroProperties()
	{

	}
	
	virtual RtClass* GetModuleClass() const
	{
		return TMZeroModule::StaticGetClass();
	}
};

/*

class AStarSearch
{
    
public:
    
    AStarSearch();
    
    ~AStarSearch();
    
    void PushHeap(QueData a[],int pa);
    
    void PopHeap(QueData a[],int pa);
    
    bool inside(int x,int y);
    
    int diff(int x,int y);
    
    void getPath(int state);
    
    int astarSearch();
};
 
 */



#endif /* defined(__PlantsVersusZombies2__TMZeroModule__) */
