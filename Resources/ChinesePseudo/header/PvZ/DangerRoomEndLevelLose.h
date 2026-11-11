//
//  DangerRoomEndLevelLose.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.12.21.
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef _DangerRoomEndLevelLose_h_
#define _DangerRoomEndLevelLose_h_

#include "UISingletonDialog.h"

class DangerRoomEndLevelLose : public UISingletonDialog<DangerRoomEndLevelLose>
{
public:
	DangerRoomEndLevelLose();
	virtual ~DangerRoomEndLevelLose();
	virtual bool            OnCreate() override;
	virtual std::string     GetLayoutName() override { return "DangerRoomEndLevelLose"; }
    //virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;
    virtual void            OnClose() override;

	// ButtonListener
	virtual void            ButtonDepress(int i_id) override;
    
    void                    Start(bool i_msgError, float i_delay);

private:
    Sexy::Widget*           m_pRootWidget = nullptr;
    float                   m_timerDelayShow = -1.0f;
    float                   m_timerClose = -1.0f;
};


#endif
