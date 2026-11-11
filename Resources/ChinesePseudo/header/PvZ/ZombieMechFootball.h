//

//  ZombieMechFootball.h

//  PlantsVersusZombies2

//

//  Created by jsola on 8/15/12.

//  Copyright (c) 2012 PopCap Games. All rights reserved.

//



#ifndef PlantsVersusZombies2_ZombieMechFootball_h

#define PlantsVersusZombies2_ZombieMechFootball_h



#include <string>



#include "BoardEntity.h"

#include "PopAnimRig.h"

#include "RtObject.h"

#include "StateMachine.h"

#include "TimeMgr.h"

#include "Zombie.h"

#include "ZombieMech.h"



class GridItem;

class Plant;





STATE_ENUM_CHILD_BEGIN(ZombieState_MechFootball, ZombieState_Mech)

    ZS_MF_Push,
    ZS_MF_Throw,
STATE_ENUM_END(ZombieState_MechFootball)



class ZombieMechFootball : public ZombieMech

{

public:

	RT_CLASS_DEFINE(ZombieMechFootball, ZombieMech, RtClass);

	

	ZombieMechFootball();
    void ApplyZombieFood() override;
    void ClearPlaybackParams(int i_type) override;
protected:

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	DECLARE_STATE_FUNCTIONS(ZombieState, Push);
	DECLARE_STATE_FUNCTIONS(ZombieState, Throw);


	virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;

	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;



private:

	bool shouldPush();

	bool canPushPlant(Plant* i_plant);

	

	void findAndPushPlant();

	void pushRow(int i_gridX, int i_gridY);

	void pushPlant(Plant* i_plant);

	void pushGridItem(GridItem* i_gridItem);
    void onAnimStopped(const std::string& i_animLabel);
    std::vector<BoardEntity*> FindFireTarget();
    void ThrowBall(const SexyVector3& target);
    bool CanTarget(BoardEntity* entity);
	AnimHandle m_activeAnim;
    
protected:
    std::vector<SexyVector3> m_targetPosList;

};



#endif

