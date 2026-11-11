#pragma once
#ifndef __SEXYAPPFRAMEWORK_ADPLACEMENTMANAGER_H__
#define __SEXYAPPFRAMEWORK_ADPLACEMENTMANAGER_H__

#include "Common.h"

#include "NetworkServiceManager.h"
#include "RtDelegate.h"
#include "SkipCapManager.h"

#include <list>
#include <string>


/*************************************************
  Example AdPlacementManager usage:
 

 
 *************************************************/

namespace Sexy
{
    class Image;
    class MetricsManager;
    
    class AdResponse : public NonCopyable
    {
    public:
        AdResponse();
        
        // Ownership of inAdImage will be passed to this object.
        AdResponse( Sexy::Image* inAdImage,
                    const std::string& inProfileId,
                    const std::string& inSessionId,
                    const std::string& inPlacementId,
                    const std::string& inAdId,
                    const std::string& inActionUrl,
                    const std::string& inViewTrackUrl,
                    const std::string& inActionTrackUrl );
        
        virtual ~AdResponse();
        
        // $$$$ (avy) look at docs for ServiceRequestCompleted( ImageLib::Image*& image, const void* context ) to see a better (?) way to take ownership.
        // But if we do change how this works, keep in mind that we may not be able to reuse the mEmptyAdInfo member.
        void                TakeOwnership(AdResponse& inGiveOwnershipTo) const;
        
        bool                ShouldShowAd() const;
        bool                HasAction() const;
        std::string         GetActionUrl() const;
        Image*              GetAdImage() const;
        
        std::string         GetProfileId() const;
        std::string         GetSessionId() const;
        std::string         GetPlacementId() const;

        void                NotifyAdDisplayed() const;
        void                NotifyActionTaken() const;

        bool                WasAdDisplayed() const; // Will return true if NotifyAdDisplayed() has been called... even if ShouldShowAd() returns false.
        bool                WasActionTaken() const; // Will return true if NotifyActionTaken() has been called... even if HasAction() returns false.
        
    private:
        void                releaseAdImage();
        
        // $$$$ (avy) include SmartPtr.h and wrap this image in it.
        
        Image*              mAdImage;   // will be NULL if no ad should currently be display for the placement
        mutable bool        mOwnsImage; // if true, then when this AdInfo instance is destroyed, its image will be deleted.
        
        std::string         mActionUrl; // will be an empty string if there is no action that can be taken on this ad
        std::string         mProfileId;
        std::string         mSessionId;
        std::string         mPlacementId;
        std::string         mAdId;      // will be an empty str ing if there is no need to report back once the ad has been displayed
        std::string         mViewTrackUrl;
        std::string         mActionTrackUrl;
        
        
        // two bools for indicating if the AdDisplayed notification or the ActionTaken
        // notification has been issued, so that if those methods are called more than once,
        // they only perform the notifications to the servers the first time.
        mutable bool        mWasAdDisplayed;
        mutable bool        mWasActionTaken;
    };

    
    class AdPlacementManager
    : public NetworkServiceListener
    {
        friend class AdResponse;
    public:
        
        // AdPlacementCallback signature: callback(AdResponse& inAdResponse)
        typedef Delegate1<const AdResponse&> AdPlacementCallback;
        
        static void                 Init();
        static AdPlacementManager*  GetInstance();
        static void                 Shutdown();
        
        // Save and restore state
        void Save();
        void Restore();

        // By default AdPlacement will be enabled after Init() is called.
        void SetEnabled(bool inShouldEnable);

        void MakeAdRequest(const std::string& inPlacementId, AdPlacementCallback inStatusCallback);
        void MakeAdRequest(const std::string& inPlacementId, Sexy::StructuredData& inKeyValuePairs, AdPlacementCallback inStatusCallback);
        
        /**
		 * Optional call to override the default PlatformName.
		 * Default values are "iOS", "OSX", "Windows" depending on platform.
		 */
		void SetPlatformName( const std::string& inPlatformName );
		
		/**
		 * Optional call to override the ProductName.
		 * The default value is read from SexyAppBase::mProdName.
		 */
		void SetProductName( const std::string& inProductName );
		
		/**
		 * Optional call to override thedefault ClientVersion.
		 * The default value is read from SexyAppBase::mProductVersion.
		 */
		void SetClientVersion( const std::string& inClientVersion );
        
        /**
         * Optional call to override the default language to fetch ads for.
         * inLanguage must be a lowercase two character language code 
         * such as "en" or "fr".
         * Init() will set the default language to english ("en").
         */
        void SetLanguage( const std::string& inLanguage );
        
		/**
		 * Optional call to override the default Draper URL.
		 */
		void SetDraperServer( const std::string& inDraperUrl );
        
        /**
         * Call this when a profile is removed from a device
         */
        void NotifyPopCapIdDispose( const std::string& inProfileID );
        
        /**
         * For debugging only. By default network tracing is disabled.
         * Only enable temporarily to debug AdPlacement network problems.
         */
        void SetNetworkTraceEnabled(bool inShouldEnable);
        
        //
        // NetworkServiceListener
        //
        
        virtual void ServiceRequestCompleted( const StructuredData* inResponse, const void* inContext );
		virtual void ServiceRequestCompleted( ImageLib::Image*& ioImage, const void* inContext );
		virtual void ServiceRequestCompleted( const Buffer* buffer, const void* context );
		virtual void ServiceRequestFailed( const StructuredData* response, const void* context );
        
    protected:
        // These are protected so only AdInfo can call these methods.
        void NotifyAdDisplayed(const std::string& inProfileId, const std::string& inSessionId, const std::string& inPlacementId, const std::string& inViewTrackUrl);
        void NotifyActionTaken(const std::string& inProfileId, const std::string& inSessionId, const std::string& inPlacementId, const std::string& inAdId);
        
    private:
        
        enum AdRequestState
        {
            AdRequestState_WaitingForDraperJson,
            AdRequestState_WaitingForAdImage,
            AdRequestState_Succeeded,
            AdRequestState_Failed
        };
        
        struct AdRequest
        {
            AdRequest(const std::string& inProfileId, const std::string& inSessionId, const std::string& inPlacementId, AdRequestState inState, AdPlacementCallback inCallback)
            {
                ProfileId = inProfileId;
                SessionId = inSessionId;
                PlacementId = inPlacementId;
                State = inState;
                Callback = inCallback;
            }
            
            bool operator == (const AdRequest& inIsEqualTo) const
            {
                return this == &inIsEqualTo;
            }
            
            std::string ProfileId;
            std::string SessionId;
            std::string PlacementId;
            AdRequestState State;
            AdPlacementCallback Callback;
            
            std::string AdId;
            std::string ActionUrl;
            std::string ViewTrackUrl;
            std::string ActionTrackUrl;
        };
        
        AdPlacementManager();
        virtual ~AdPlacementManager();
        
        void            makeAdRequest(const std::string& inPlacementId, Sexy::StructuredData* inKeyValuePairs, AdPlacementCallback inStatusCallback);
        std::string     buildDraperPlacementUrl(const std::string& inPlacementId);
        void            cleanUpAdRequest(AdRequest* inAdRequest);
        void            sendEmptyAdResponse(AdPlacementCallback inCallback);
        
        /**
         * Get the throttle value for a given placement.  If no throttle record
         * is available for the placement, then the global (per game) draper throttle is used,
         * if no global draper throttle value is found then the default value (passed in to
         * this method) is returned.
         */
        double          getPlacementThrottleValue( const std::string& inPlacementId, double defaultThrottle );
        
        // $$$$ (avy) need to also provide an implementation which doesn't use the persistent sampling key.
        bool            shouldFetchPlacement( const std::string& inProfileId, const std::string& inSessionId, const std::string& inPlacementId );
        
        
        static AdPlacementManager* sInstance;
        
        
        MetricsManager*         mMetricsManager;
        NetworkServiceManager*  mNetworkServiceManager;
        std::string             mDraperServer;
        
        bool                    mIsAdPlacementEnabled;
        double                  mDefaultThrottle;
        
        std::string             mClientVersion;
		std::string             mPlatformName;
		std::string             mProductName;
        std::string             mLanguage;
        
        std::list<AdRequest>    mOutstandingAdRequests;
        
        bool                    mShouldEnableNetorkTrace;
        const std::string       mNetworkChannel;
        
        // Keep a single empty AdInfo instance, this will be passed to the
        // placement callback whenever there is no ad to be displayed.
        // This way we'll never allocate AdResponse objects for this case.
        const AdResponse        mEmptyAdResponse;
    };
    
} // namespace Sexy


// $$$$ (avy)
#include "Graphics.h"

class AdTest
{
public:
    AdTest()
        : mCurrentAdResponse(NULL)
    {
        
    }
    
    void DoInitSessionAdPlacement()
    {        
        // Create a StructuredData object containing key value pairs to send to the ad server so that
        // it can more effectively select appropriate ads.
        // Below are suggested keys to send if they have a meaning in your game.
        Sexy::StructuredData adSelectionKeyValuePairs;
        PrepareAdServerKeyValuePairs(adSelectionKeyValuePairs);
        Sexy::AdPlacementManager::GetInstance()->MakeAdRequest("app_init", adSelectionKeyValuePairs, MakeDelegate(*this, &AdTest::AdResponseHandler));        
    }
    
    void Draw(Sexy::Graphics* inGraphics)
    {
        if (mCurrentAdResponse != NULL && mCurrentAdResponse->ShouldShowAd())
        {
            inGraphics->DrawImage(mCurrentAdResponse->GetAdImage(), 0, 0);
            if (!mCurrentAdResponse->WasAdDisplayed())
            {
                mCurrentAdResponse->NotifyAdDisplayed();
            }
        }
    }
    
    void Update()
    {
        
    }
    
private:
    void AdResponseHandler(const Sexy::AdResponse& inAdResponse)
    {
        if (!inAdResponse.ShouldShowAd())
        {
            return;
        }
        
        // $$$$ (avy) rewrite this, its a bit ugly
        if (mCurrentAdResponse == NULL)
        {
            mCurrentAdResponse = new Sexy::AdResponse();
        }
        inAdResponse.TakeOwnership(*mCurrentAdResponse);
        
        mCurrentAdResponse->NotifyAdDisplayed();
    }
    
    void PrepareAdServerKeyValuePairs(Sexy::StructuredData& ioAdSelectionKeyValuePairs)
    {
        ioAdSelectionKeyValuePairs.Clear();
        
        ioAdSelectionKeyValuePairs.BeginObject();

        ioAdSelectionKeyValuePairs.   AddString("profileId", "pA"); // whether a player has spent money in the game
        ioAdSelectionKeyValuePairs.   AddString("sessionId", "sA"); // whether a player has spent money in the game

        ioAdSelectionKeyValuePairs.   AddBoolean("monetized", HasPlayerMonetized()); // whether a player has spent money in the game
        ioAdSelectionKeyValuePairs.   AddBoolean("logged_in", IsLoggedInToFacebook()); // whether a user is logged in
        if (IsLoggedInToFacebook())
        {
            ioAdSelectionKeyValuePairs.   AddBoolean("logged_in_via", "facebook"); // a comma separated string of the names of the authentication system. Ex. facebook,origin
        }
        ioAdSelectionKeyValuePairs.   AddInteger("total_launches", GetTotalNumAppLaunches()); // the number of times the app has been launched
        ioAdSelectionKeyValuePairs.   AddInteger("last_launch", GetLastLaunchAppLaunchTimestamp());
        
        ioAdSelectionKeyValuePairs.   AddInteger("xp", GetPlayerXp()); // experience points, as relates to the player in the game
        ioAdSelectionKeyValuePairs.   AddInteger("level", GetPlayerLevel()); // the level of the player in the game
        
        // Note: "uuid" and "build" keys are automatically sent by AdPlacementManager, there is no need to add them here.
        
        ioAdSelectionKeyValuePairs.EndObject();
    }
    
    // These are just stubbed out methods to fetch values to pass on to the ad server.
    bool    IsLoggedInToFacebook()              { return true; }
    bool    HasPlayerMonetized()                { return true; }
    int32   GetTotalNumAppLaunches()            { return 10; }
    float   GetLastLaunchAppLaunchTimestamp()   { return 5565656; }
    int32   GetPlayerXp()                       { return 10; }
    int32   GetPlayerLevel()                    { return 10; }
    
    Sexy::AdResponse* mCurrentAdResponse;
};


#endif // __SEXYAPPFRAMEWORK_ADPLACEMENTMANAGER_H__