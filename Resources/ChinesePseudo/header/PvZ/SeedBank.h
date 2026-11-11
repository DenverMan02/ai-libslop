//
//  SeedBank.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  Handles the display of and input on seed packets. Also generates an atlas that the
//  seed packets will use for their images while the game is running (we keep up to 10 plants
//  in memory for their seed packet images, instead of the full roster.
//

#ifndef __SEEDBANK_H__
#define __SEEDBANK_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"

#include "SeedPacket.h"
#include "ProbabilitySet.h"
#include "SlidingWidget.h"

const int8 SEEDBANK_MAX_PACKETS = 9; // 8 normally, 9 for conveyor, 7 for pneumatic tube

enum SeedBankType
{
	SEEDBANK_NORMAL,
	SEEDBANK_CONVEYOR,
	SEEDBANK_PNEUMATIC,
    SEEDBANK_PVP,
    SEEDBANK_NEWPVP,
	SEEDBANK_BEGHOULED,
	SEEDBANK_WORLDCUP,
	SEEDBANK_RIFT,
};

class WaveDefinition;
class SeedPacket;

class SeedBankNew : public SlidingWidget
{
	
public:
	RT_CLASS_DEFINE(SeedBankNew, SlidingWidget, RtClass);
	
	SeedBankNew();
	virtual ~SeedBankNew();
	
	// Public Interface (Inheritable)
	
	virtual void					Draw(Graphics* i_g) override;
	virtual void					InitializePacketTimers();
	
	virtual void					SetSeedBankProperties(RtWeakPtr<const class SeedBankProperties> i_propertySheet);
	virtual void					SetAutofillSeedTypes(const std::vector<std::string>& i_seedList);
    
    virtual void                    GetPlantResourceGroups(std::vector<std::string>& o_resourceGroupList);
	
	// Public Interface (Core)
	
    void							SetGlobalLevel(int i_level) { m_globalLevel = i_level; }
    RtWeakPtr<SeedPacket>			GetPacket(const int index);
    RtWeakPtr<SeedPacket>			GetPacket(const std::string& typeName);
    RtWeakPtr<SeedPacket>			TryFindSeedPacket(const PlantTypePtr i_type);
	void							SetPacketsOnDisplay(bool i_isOnDisplay);
    virtual void					SetNumPackets(uint8 i_numPackets, bool i_updatePositions = true);
    void							SetAllPacketsReady();

    std::vector<std::string>	GetBlacklist();

	inline const SeedBankType		GetSeedBankType();
	inline const int8				GetPacketCount();
	inline const int				GetGlobalLevel();
    int                             GetSeedsCount();
    void                            SetSeedBankType(SeedBankType iType) { m_bankType = iType; }
    
    void                            SetZombieMode(bool i_zombieMode);
    void                            SetGridItemMode(bool i_gridItemMode);
	void							SetVerticalLayout(bool setting) { m_bVerticalLayout = setting; }
	bool							IsVerticalLayout() const { return m_bVerticalLayout; }
    
    virtual void					fillSeedPackets();
    
    void                        SetSeedPacketType(const RtName seedPacketType);
    const RtName                GetSeedPacketType() const { return m_seedPacketType; }
    
    virtual bool HasPlant(const std::string& i_objectType);
    
protected:

	// Protected Interface (Inheritable)
	
	OVERRIDE_STATE_UPDATE(WidgetState, Initializing);

	virtual void					initLoadingResourcesGroupList() override;
	virtual void					initialize(const uint8 i_packetCount = 0);

	//virtual void					fillSeedPackets();
	
	virtual void					onNewWave(int i_waveIndex, const WaveDefinition *i_currentDefinition);
    virtual void					onSeedPacketPlanted(class SeedPacket* i_packet);

	virtual void					setPacketPositions();
	void							layoutVertical();
	void							layoutHorizontal();
   	void							addPacket(UIWidgetPtr i_packetWidget, bool i_updatePositions = true);
    
	// Protected Interface (core)
protected:
    
	// Protected Members (serialized)
	
	uint8							m_packetCount;
	SeedBankType					m_bankType;
	RtWeakPtr<const class SeedBankProperties>	m_seedBankProps;
	std::vector<std::string>		m_autofillSeedTypes;
    bool                            m_zombieMode;
    bool                            m_gridItemMode;

	bool								m_bVerticalLayout;
    RtName                          m_seedPacketType;
    RtName 							m_specialSeedPacketType;
    int								m_globalLevel;
	
};

inline const int SeedBankNew::GetGlobalLevel()
{
	return m_globalLevel;
}

inline const int8 SeedBankNew::GetPacketCount()
{
	return m_packetCount;
}

inline const SeedBankType SeedBankNew::GetSeedBankType()
{
	return m_bankType;
}

typedef RtWeakPtr<SeedBankNew> SeedBankPtr;

#endif // __SEEDBANK_H__
