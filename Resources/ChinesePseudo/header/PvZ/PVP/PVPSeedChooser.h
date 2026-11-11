//
//  PVPSeedChooser.h
//  PlantsVersusZombies2
//
//  Created by Emma on 2015.10.15
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVPSeedChooser_h
#define PlantsVersusZombies2_PVPSeedChooser_h

#include "SeedChooser.h"

class PVPSeedChooser : public SeedChooser
{
public:
    RT_CLASS_DEFINE(PVPSeedChooser, SeedChooser, RtClass);
    PVPSeedChooser();
    
    virtual void			Draw(Graphics* i_g) override;
   	virtual void			VerifyAndSelectSeeds() override;
    
    void                SetPVPMode(int iMode) { m_pvpMode = iMode; }
    void                SetTotalBrains(int iVal) { m_totalBrains = iVal; }
    int                 GetUnusedBrains();
 
    static void         InitSeedPacketPVP(class SeedPacket* pPacket, int pvpmode);
protected:
    virtual void			onCheatEnabled() override;
    virtual void			onCheatDisabled() override;
    virtual bool			isBlacklisted(const std::string& i_seedName) override {return false;}
    virtual void			finalizeSelection() override;
    virtual void			startMovingPacket(ChooserPacketData& i_packetData) override;
    virtual void         onLandInBank(ChooserPacketData& i_packetData) override;
    
    //DECLARE_STATE_FUNCTIONS(WidgetState, Initializing);
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing);
    OVERRIDE_STATE_UPDATE(WidgetState, Initializing);
protected:
    void                rebuildSeedList();
    ChooserPacketData*  getBankPacket(const std::string& seedtype);
    
protected:
    int                 m_pvpMode;
    int                 m_totalBrains;
    Rect                m_brainRect;

};

#endif
