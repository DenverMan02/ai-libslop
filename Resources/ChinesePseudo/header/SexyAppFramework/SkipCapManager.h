//
//  SkipCapManager.h
//  SexyAppFramework Prime
//
//  Created by Todd Gilbertsen on 4/16/13.
//
//
#pragma once

#ifndef SexyAppFramework_Prime_SkipCapManager_h
#define SexyAppFramework_Prime_SkipCapManager_h

#include "Common.h"

#include "NetworkServiceManager.h"
#include "RtDelegate.h"

#include <list>
#include <string>

//----------------------------------------------------------------------------------------
// SkipCap classes
//
// Used for GATS-based Draper throttling
//----------------------------------------------------------------------------------------
namespace Sexy
{

    //----------------------------------------------------------------------------------------
    // SkipCapData
    //
    // Contains a skip count, cap, number of times shown, and current number skipped.
    //----------------------------------------------------------------------------------------
    class SkipCapData
    {
        friend class SkipCapManager;  // easier to serialize
        
    public:
        SkipCapData();
        SkipCapData( int inSkipCount, int inCap );
    
        void Init( int inSkipCount, int inCap );
    
    public:
        int mSkipCount;
        int mCap;
        int mCurrentTimesShown;
        int mCurrentNumSkipped;
    };


    //----------------------------------------------------------------------------------------
    // SkipCapSession
    //
    // Contains all skip/cap data for a given session
    //----------------------------------------------------------------------------------------
    class SkipCapSession
    {
        friend class SkipCapManager; // easier to serialize
        
    public:
        SkipCapSession();
        SkipCapSession( const std::string &inProfileId, const std::string &inSessionId );
    
        void Init( const std::string &inProfileId, const std::string &inSessionId );
        
        void RealizePlacement( const std::string &inPlacementId );
        bool AttemptAdCheck( const std::string &inPlacementId );
    
        void AdDisplayed( const std::string &inPlacementId );
        void ActionTaken( const std::string &inPlacementId );
        
    public:
        std::string mProfileId;
        std::string mSessionId;
        SkipCapData mSessionData;
        
    private:
        std::map<std::string, SkipCapData *> mPlacementMap;
    };

    
    //----------------------------------------------------------------------------------------
    // SkipCapManager
    //
    // Singleton.  Manager for skip/cap data for all sessions.  
    //----------------------------------------------------------------------------------------
    class SkipCapManager
    {
    public:
        static SkipCapManager& GetInstance()
        {
            static SkipCapManager sInstance;
            return sInstance;
        }
        
        void Initialize();
        SkipCapSession *GetSessionData( const std::string &inProfileId, const std::string &inSessionId );
        void DeleteSessionData( const std::string &inProfileId );
        
        void SaveToBuffer( Buffer &buffer, int version );
        void RestoreFromBuffer( Buffer &buffer, int version );

    private:
        SkipCapManager() {};
        SkipCapManager(SkipCapManager const&);
        void operator=(SkipCapManager const&);
    
        SkipCapSession *findSessionData( const std::string &inProfileId, const std::string &inSessionId );
        void addSessionData( const std::string &inProfileId, const std::string &inSessionId, SkipCapSession *inSessionData );
        
        std::string makeKey( const std::string &inProfileId, const std::string &inSessionId );

    private:
        std::map<std::string, SkipCapSession *> mSessions;
        const static std::string mConcatToken;
    };
}

#endif
