//
//  FBOpenGraph.h
//  PlantsVersusZombies2
//
//  Created by Seth Brown on 2013-04-23.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_FBOpenGraphManager_h
#define PlantsVersusZombies2_FBOpenGraphManager_h

// TODO: Optimize these includes
#include "FBOpenGraphAction.h"
#include "SexyAppFramework/SexyAppBase.h"

#include "NetworkServiceManager.h"
#include "NetworkStatusDecider.h"
#include "PVZTypes.h"

// TODO: make this a Singleton global
class WaveDefinition;

namespace Message
{
	void OpenGraphEvent(FBOpenGraphAction* ogActionPtr);
}

class FBOpenGraphListener : public Sexy::NetworkServiceListener
{
public:
	FBOpenGraphListener(class FBOpenGraphManager* i_openGraphManager)
	: m_openGraphManager(i_openGraphManager)
	{}
	
	void ServiceRequestCompleted(const Sexy::StructuredData* response, const void* context);
	void ServiceRequestCompleted(ImageLib::Image*& image, const void* context);
	void ServiceRequestCompleted(const Sexy::Buffer* buffer, const void* context);
	void ServiceRequestFailed(const Sexy::StructuredData* response, const void* context);
    
private:
	class FBOpenGraphManager* m_openGraphManager;
    
};

class FBOpenGraphManager
{
public:
	FBOpenGraphManager()
    : m_openGraphListener(this)
    {}
	virtual ~FBOpenGraphManager() {}
    
	void Init(const SexyString& serviceSKU, const SexyString& serviceAuth, const SexyString& serviceURL, const SexyString& servicePath);
	void SetFacebook(const SexyString& userID, const SexyString& accessToken);
	void EnablePosting();
	void DisablePosting();
    void Term();
    
private:

    NetworkStatusDecider m_networkStatusDecider;
    FBOpenGraphListener m_openGraphListener;
    std::vector<FBOpenGraphAction*> m_actionQueue;
	bool m_enabled=false;
	
	SexyString m_serviceSKU;
	SexyString m_serviceAuth;
	SexyString m_serviceURL;
	SexyString m_servicePath;
	
	SexyString m_facebookID;
	SexyString m_facebookAccessToken;
	
	// register and deregister from messages
	void registerEventsWithLawnApp();
	void unregisterEventsWithLawnApp();
    
    // Message handlers to add actions to queue
    void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void onYetiDefeated();
    void onPlantUnlocked(const std::string& i_plantName);
    void onWorldMapSwitchedWorlds(class WorldData* i_world);
    void onDangerIsleLevelComplete();
	void onWaveStarting(const WaveDefinition* i_currentDefinition);
    void onLevelEnded();
    
    // Send all requests in the queue
    void sendRequestPool();

};

#endif
