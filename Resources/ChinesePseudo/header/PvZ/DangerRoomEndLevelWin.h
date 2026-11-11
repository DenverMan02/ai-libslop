//
//  DangerRoomEndLevelWin.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.11.15.
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef _DangerRoomEndLevelWin_h_
#define _DangerRoomEndLevelWin_h_

#include "UISingletonDialog.h"
#include "TimeMgr.h"
#include "ActivityItemWidgets.h"

class DangerRoomEndLevelWin : public UISingletonDialog<DangerRoomEndLevelWin>
{
public:
	DangerRoomEndLevelWin();
	virtual ~DangerRoomEndLevelWin();
	virtual bool					OnCreate() override;
    virtual void					OnClose() override;
	virtual std::string				GetLayoutName() override { return "DangerRoomEndLevelWin"; }
    virtual void					Draw(Sexy::Graphics* i_g) override;
    virtual void					Update() override;

	// ButtonListener
	virtual void					ButtonDepress(int i_id) override;
    
    void                            StartAnim(bool i_msgError);
    
protected:
    void                            onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp,
                                                     const std::string& i_command, const std::string& i_param);
    void                            onAnimStopped(const std::string &i_animLabelName);
    
    void                            StartSeedPlantsAnim();
    void                            PlaySeedAnim(int i_index);

private:
    class UIWidgetAnim*             m_pAnimPane = nullptr;
    class NumberWidget*             m_pNumberWidget = nullptr;
    class NumberWidget*             m_pAddWidget = nullptr;
    float                           m_timerClose = -1.0f;
    int                             m_btnClicked = 0;
    std::vector<std::tuple<class SeedPacketPlantWidget*, int>>   m_seedPlants;
    float                           m_timerSeedAnim = -1.0f;
    int                             m_seedAnimIndex = -1;
    SlidingController               m_slidingController;
    SlidingController               m_slidingController2;
};

//--------------------------------------------------------
// SeedPacketPlantWidget
//--------------------------------------------------------
class SeedPacketPlantWidget : public Sexy::Widget
{
public:
    SeedPacketPlantWidget();
    ~SeedPacketPlantWidget();
    virtual void        Draw(Sexy::Graphics* i_g) override;
    virtual void		DrawAll(ModalFlags* theFlags, Graphics* i_g) override;
    virtual void        Update() override;
    
    void                SetPlantType(const std::string& i_plantType);
    void                SetNum(int i_num, bool i_bAnim);
    int                 GetNum() const;
    void                PlayEffects();
protected:
    std::string         m_plantType;
    const class PacketRenderData* m_pPacketRenderData = nullptr;
    class PopAnimRig*   m_animEffectStar = nullptr;
    class PopAnimRig*   m_animEffectBorder = nullptr;
    class NumberWidget* m_pNumberWidget = nullptr;
};


#endif
