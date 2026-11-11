//
//  SeedPacket_PVPSkill.h
//  PlantsVersusZombies2
//
//  Created by Emma on 2015.10.10
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __SeedPacket_PVPSkill_H__
#define __SeedPacket_PVPSkill_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "SeedBank.h"
#include "SeedPacket.h"


class SeedPacket_PVPSkill : public SeedPacket
{
public:
	RT_CLASS_DEFINE(SeedPacket_PVPSkill, SeedPacket, RtClass);
    SeedPacket_PVPSkill();

	virtual void        Draw(Graphics* i_g) override;
    virtual bool		OnTouch(const Sexy::Touch& i_touch) override;

    virtual bool			IsAffordable() override;
    virtual bool         TryUse(class PacketCursor* pCursor) override;
    
    void                InitEnergy(int initVal, int maxVal);
    int                 GetEnergyCost() const { return m_iEnergyCost; }
    void                UseSkill(const SexyVector3& location, int i_cost);
    void                SetLevel(int i_level);
    int                 GetLevel() { return m_level; }
protected:
    virtual void         registerForEvents() override;
    virtual void         unregisterForEvents() override;
    virtual void         initLoadingResourcesGroupList() override;
    virtual void         DrawText(Graphics* i_g) override;
    virtual void			onSeedPacketPlanted(SeedPacket* i_packet) override {}
    virtual void         onSunCurrencyChanged(SunCurrency i_upcomingAmount) override {}
    virtual void         onSunClicked(class CollectableSun* i_sun, SunCurrency i_upcomingAmount) override {}
            void		onCursorDestroyed(class BaseCursor* i_cursor) override;
    void                onPVPSkillEnergyChanged(int curEnergy);
    
protected:
    int                 m_iEnergyCost;
    int                 m_iMaxEnergyCost;
    int                 m_level;

};

namespace Message
{
    void PVPSkillUsed(class Zombie* pSkill, int iCost);
}

#endif // __SeedPacket_PVPSkill_H__
