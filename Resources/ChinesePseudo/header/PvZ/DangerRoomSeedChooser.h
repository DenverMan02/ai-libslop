//
//  DangerRoomSeedChooser.h
//  PlantsVersusZombies2
//
//  Created by Emma on 2016.11.2
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_DangerRoomSeedChooser_h
#define PlantsVersusZombies2_DangerRoomSeedChooser_h

#include "SeedChooser.h"

class DangerRoomSeedChooser : public SeedChooser
{
public:
    RT_CLASS_DEFINE(DangerRoomSeedChooser, SeedChooser, RtClass);
    DangerRoomSeedChooser();
    
    //virtual void			Draw(Graphics* i_g) override;
   	virtual void			VerifyAndSelectSeeds() override;

    virtual void            refreshValidPlantTypeList();

    void					SetSeedBankProperties(const class SeedBankProperties* i_propertySheet) override;
 
protected:
    virtual void			startMovingPacket(ChooserPacketData& i_packetData) override;
    virtual void            rebuildValidPlantTypeList() override;
    virtual void            initPlantFromRecord() override;
    virtual void			onSlideInFinished() override;
    virtual void			finalizeSelection() override;
    virtual void			drawArtifact(Sexy::Graphics* i_graphics) const override;
    //DECLARE_STATE_FUNCTIONS(WidgetState, Initializing);
    //OVERRIDE_STATE_ONENTER(WidgetState, Initializing);
    //OVERRIDE_STATE_UPDATE(WidgetState, Initializing);
    
    ChooserPacketData*      getBankPacket(const std::string& seedtype);
    void                    movePacket(class SeedPacket_DangerRoom* pPacketFrom, class SeedPacket_DangerRoom* pPacketTo);
    void                    onMessageBoxCallback(class UIMessageBox* box, int buttonID);
    void                    checkButtons();
    SexyString             GetSeedChooserWarnings(const std::vector<PlantTypePtr>& i_seedList);
protected:
    const std::vector<class S2C_DangerRoomPlantNum>& GetPlantNumList();
    std::vector<class S2C_DangerRoomPlantNum>& GetTrainingPlantNumList();
    void ResetTrainingPlantNumList();

    bool					m_isTraining;
    std::vector<S2C_DangerRoomPlantNum> m_trainingList;

};

#endif
