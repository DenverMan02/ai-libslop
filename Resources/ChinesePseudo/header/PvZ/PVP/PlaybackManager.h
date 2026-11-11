//
//  PlaybackManager.h
//  PlantsVersusZombies2
//
//  Created by Emma on 2015.10.23
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlaybackManager__
#define __PlantsVersusZombies2__PlaybackManager__

#include "Singleton.h"
#include "PlaybackData.h"

typedef std::map<BattleID, PlaybackData*> MapPlaybackDatas;
class PlaybackManager : public LazySingleton<PlaybackManager>
{
public:
    PlaybackManager();
    virtual ~PlaybackManager();
    void                Clear();
    
    void                SetCurrentData(BattleID i_id);       // if 0, then begin recording
    PlaybackData*       GetCurrentData() { return m_pPlayback; }
    
    bool                IsRecording() const { return m_state == Playback_Recording; }
    bool                IsPlaying() const { return m_state == Playback_Playing; }
    void                SetState(int iVal) { m_state = iVal; }
    
    void                StartPlayback();
    void                EndPlayback();
    
    const MapPlaybackDatas& GetDatas() const { return m_MapDatas; }
    void                AddPlaybackBrief(const PlaybackBrief& brief);
    PlaybackData*       GetPlayback(BattleID i_id);
    
    int                 GetVersion();
    bool                CheckVersionValid(int i_ver);
    bool                IsHaveNewPlayback();
    void                RefreshNewPlaybackID();
    void                SetMaxBattleID(BattleID i_id);
    
protected:
    PlaybackData*       m_pPlayback;
    MapPlaybackDatas    m_MapDatas;
    int                 m_state;
    BattleID            m_maxBattleID;
};

#define gPlaybackMgr (PlaybackManager::GetInstancePtr())

#endif /* defined(__PlantsVersusZombies2__PlaybackManager__) */
