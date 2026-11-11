//
//  SeedPacket_DangerRoom.h
//  PlantsVersusZombies2
//
//  Created by Emma on 2016.10.17
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef __SeedPacket_DangerRoom_H__
#define __SeedPacket_DangerRoom_H__

#include "SeedPacket_PVP.h"

class SeedPacket_DangerRoom : public SeedPacket_PVP
{
public:
	RT_CLASS_DEFINE(SeedPacket_DangerRoom, SeedPacket_PVP, RtClass);
    SeedPacket_DangerRoom();

	virtual void        Draw(Graphics* i_g) override;
    //virtual bool		OnTouch(const Sexy::Touch& i_touch) override;

    //virtual bool			IsAffordable() override;
    //virtual bool         TryUse(class PacketCursor* pCursor) override;
    virtual void         CopyFrom(SeedPacket* pCopy) override;
    virtual void         SetPlantType(const PlantTypePtr i_plantType) override;
    
protected:
    virtual void         DrawText(Graphics* i_g) override;
    virtual void         onSeedPacketPlanted(SeedPacket* i_packet) override;
protected:

};

class SeedPacket_DangerRoomTraining : public SeedPacket
{
public:
	RT_CLASS_DEFINE(SeedPacket_DangerRoomTraining, SeedPacket, RtClass);

	SunCurrency         GetSunCost() override;
};

#endif // __SeedPacket_DangerRoom_H__
