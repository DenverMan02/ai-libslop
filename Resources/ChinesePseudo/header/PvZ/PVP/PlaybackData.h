//
//  Playback.h
//  PlantsVersusZombies2
//
//  Created by Emma on 2015.9.25
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlaybackData_h
#define PlantsVersusZombies2_PlaybackData_h

#include "GameObject.h"
#include "RtSerial.h"
#include "Reflection.h"
#include "ArenaPrecompile.h"
#include "PVPDatas.h"

//-------------------------------------------------------------------
//-------------------------------------------------------------------
class PTrigger : public RtObject
{
public:
    RT_CLASS_DEFINE_ABSTRACT(PTrigger, RtObject, RtClass);
    PTrigger(uint32 i_type);
    uint32 GetTriggerType() const { return m_triggerType; };
    
    virtual void DoTrigger() = 0;
	class Zombie*	GetZombieByID(int i_zombieTempID);
    
    static PTrigger* CreateByType(uint32 i_type);
    
protected:
    uint32      m_triggerType;
};

//-------------------------------------------------------------------
class PTriggerZombiePlaced : public PTrigger
{
public:
    RT_CLASS_DEFINE(PTriggerZombiePlaced, PTrigger, RtClass);
    PTriggerZombiePlaced();
    
    virtual void DoTrigger() override;
    
    void SetZombie(class Zombie* pZombie);
    
protected:
    std::string			m_zombieType;
    Sexy::Point		m_grid;
    bool					m_hasPlantFood;
	int						m_zombieTempID = 0;
public:
    static const uint32 TypeValue;
};

//-------------------------------------------------------------------
class  PTriggerZombieAddParams: public PTrigger
{
public:
	struct Param 
	{
		uint8 m_key;
		std::string m_value;
	};
public:
	RT_CLASS_DEFINE(PTriggerZombieAddParams, PTrigger, RtClass);
	PTriggerZombieAddParams();

	virtual void DoTrigger() override;
	void			SetZombieTempID(int i_zombieTempID) { m_zombieTempID = i_zombieTempID; }
	void			SetParams(int i_paramsType, const std::map<uint8, std::string>& params);

protected:	
	int						m_zombieTempID = 0;
	int						m_paramsType = 0;
	std::vector<Param>	m_params;
public:
	static const uint32 TypeValue;
};

//-------------------------------------------------------------------
class PTriggerPlantfood : public PTrigger
{
public:
    RT_CLASS_DEFINE(PTriggerPlantfood, PTrigger, RtClass);
    PTriggerPlantfood();
    
    virtual void DoTrigger() override;
    
    void    SetPlant(class Plant* i_plant);
protected:
    Sexy::Point m_grid;
public:
    static const uint32 TypeValue;
};

class PTriggerSkillUsed : public PTrigger
{
public:
    RT_CLASS_DEFINE(PTriggerSkillUsed, PTrigger, RtClass);
    PTriggerSkillUsed();
    
    virtual void DoTrigger() override;
    
    void SetSkill(class Zombie* pSkill, int i_cost);
protected:
    std::string     m_skillType;
    SexyVector3   m_location;
    int         m_cost;
public:
    static const uint32 TypeValue;
};


//-------------------------------------------------------------------
//-------------------------------------------------------------------
class PFrame : public RtObject
{
public:
    RT_CLASS_DEFINE(PFrame, RtObject, RtClass);
    PFrame();
    ~PFrame();
    
public:
    virtual bool Serialize(const Sexy::RtSerializeContext& inContext) override;
    
    void        ClearTriggers();
    void        DoTriggers();
    
    void        AddTrigger(PTrigger* pTrigger);
    
    void        SetFrame(uint32 iFrame) { m_iFrame = iFrame; }
    uint32      GetFrame() const { return m_iFrame; }
    
protected:
    PTrigger*   readTriggerFromJson(RtSerialRtonSync* inSync);
    
protected:
    uint32 m_iFrame;
    std::vector<PTrigger*> m_Triggers;
};


//-------------------------------------------------------------------
//-------------------------------------------------------------------
enum PlaybackState
{
    Playback_Invalid,
    Playback_Recording,
    Playback_Playing,
};

enum PlaybackRevengeStatus
{
    Playback_Attack = 0,
    Playback_Revenge = 1,
    Playback_Revenge_Done = 2,
    Playback_BeRevenged = 3,
    Playback_EvilDave = 4,
    
    Playback_RevengeInvalid,
};

typedef uint64 BattleID;
struct PlaybackBrief
{
public:
    uint64  m_profileID = 0;
    BattleID  m_battleID = 0;
    bool    m_isAttacker = false;
    int     m_arenaType = 0;
    int     m_version = 0;
    std::wstring    m_opponentName;
    uint64          m_opponentID = 0;
    int     m_numStar = 0;
    int     m_pvpCup = 0;
    int     m_pvpCoin = 0;
    int     m_pvpMedal = 0;
    int     m_revengeStatus = 0;
    BattleID  m_revengeID = 0;
    uint32  m_battleTime = 0;
    
};

struct PlaybackZombieData
{
    std::string m_type;
    int         m_num = 0;
    int         m_level = 0;
};
typedef PlaybackZombieData PlaybackSkillData;

class PlaybackData : public RtObject
{
public:
    RT_CLASS_DEFINE(PlaybackData, RtObject, RtClass);
protected:
    PlaybackData();
    ~PlaybackData();
public:
    virtual bool Serialize(const Sexy::RtSerializeContext& inContext) override;
    
    void Destroy();
    void Update();
    void AddTrigger(PTrigger* pTrigger);
    
    void ClearData();
    void StartRecording();
    void StartPlaying();
    void End();
    
    void SetState(int iVal) { m_state = iVal; }
    int  GetState() const { return m_state; }
    bool IsPlayingEnd();
    
    bool IsValid();
    void SaveToServer();
    bool LoadFromServer(std::string& strCompressed);
    
protected:
    PFrame*     getCurFrame();
    
protected:
    // need writing to json
    std::vector<PFrame> m_Frames;
    uint32 m_iFrameNum;     // min size is 1
    
    // don't write
    uint32 m_iCurFrame;     // begin from 0
    uint32 m_iNext;
    int     m_state;
    
    // ----- battle info -----
public:
    // init info
    PlayerPlantData                     m_PlayerPlantData;
    DefenderInfo                        m_DefenderInfo;
    std::vector<PlaybackZombieData>     m_zombieDatas;
    std::vector<PlaybackZombieData>     m_skillDatas;
    
    // result info
    std::vector<ZombieRecord>            m_ZombieRecords;      // zombies lost

    PlaybackBrief                       m_PlaybackBrief;
};


#endif
