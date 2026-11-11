//
//  SeedPacket_PVP.h
//  PlantsVersusZombies2
//
//  Created by Emma on 2015.10.14
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __SeedPacket_PVP_H__
#define __SeedPacket_PVP_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "SeedBank.h"
#include "SeedPacket.h"


class SeedPacket_PVP : public SeedPacket
{
public:
	RT_CLASS_DEFINE(SeedPacket_PVP, SeedPacket, RtClass);
    SeedPacket_PVP();

	virtual void        Draw(Graphics* i_g) override;
    virtual bool		OnTouch(const Sexy::Touch& i_touch) override;

    virtual bool			IsAffordable() override;
    virtual bool         TryUse(class PacketCursor* pCursor) override;
    virtual void         CopyFrom(SeedPacket* pCopy) override;
    
    void                SetCurNum(int iVal);
    void                SetMaxNum(int iVal);
    void                SetCost(int iVal);
    int                 GetCurNum() const { return m_iCurNum; }
    int                 GetMaxNum() const { return m_iMaxNum; }
    int                 GetCost() const { return m_iCost; }
    
    void                SetLocked(bool setting, const SexyString& desc);
    bool                IsLocked() const { return m_bLocked; }
    
protected:
    virtual void         DrawText(Graphics* i_g) override;
    virtual void			onSeedPacketPlanted(SeedPacket* i_packet) override;
    void                 onCursorDestroyed(BaseCursor* i_cursor) override;
	virtual void			updateAffordability(const SunCurrency i_newSunCurrency) override;
protected:
    int                 m_iCurNum;
    int                 m_iMaxNum;
    int                 m_iCost;
    bool                m_bLocked;
    bool                m_sunEnough = false;
    SexyString          m_strLockDesc;
};

#endif // __SeedPacket_PVP_H__
