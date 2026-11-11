//
//  PVPSeedBankModule.h
//  PlantsVersusZombies2
//
//  Created by Emma on 2015.10.13
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PVPSeedBank_H__
#define __PVPSeedBank_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "SeedBank.h"
#include "SeedPacket.h"



class PVPSeedBank : public SeedBankNew
{
public:
	RT_CLASS_DEFINE(PVPSeedBank, SeedBankNew, RtClass);
	
	PVPSeedBank();
	virtual ~PVPSeedBank();
    
   	virtual bool                 IsMouseOver(const int i_mouseX, const int i_mouseY) override;
   	virtual bool                 OnTouch(const Sexy::Touch& i_touch) override;
    virtual void				 Draw(Graphics* i_g) override;
    
    virtual void					fillSeedPackets() override;
    
    void							AddPacket(UIWidgetPtr i_packetWidget);
    void                        RefreshPackets();
    void                        SetMaxShowNum(int iVal) { m_maxShowNum = iVal; }
    
protected:
   	virtual void                 registerForEvents() override;
    virtual void					initialize(const uint8 i_packetCount = 0) override;
    virtual void					setPacketPositions() override;
    
    bool                        handleTouch(const Sexy::Touch& i_touch);
    void                        cancelTouch();
    int                         getButtonAt(int x, int y);
    bool                        isPageBegin();
    bool                        isPageEnd();

protected:
    int                         m_curPage;
    int                         m_maxShowNum;
    Sexy::Rect                  m_decBtnArea;
    Sexy::Rect                  m_incBtnArea;
    Sexy::TouchID               m_touchIdent;

};

typedef RtWeakPtr<PVPSeedBank> PVPSeedBankPtr;

#endif // __PVPSeedBank_H__
