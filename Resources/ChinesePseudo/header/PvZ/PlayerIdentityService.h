//
//  PlayerIdentityService.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen on 11/19/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlayerIdentityService__
#define __PlantsVersusZombies2__PlayerIdentityService__

#include "Precompile.h"
#include "ICloudListener.h"
#include <string>

#define PCPID_KEY "pcpid"

class FakeHttpDriver;
class ICloudWrapper;
class UUIDCreator;
class UserPrefsWrapper;
class MessageRouter;
class PlayerInfo;
class GameEventNotification;
namespace Sexy
{
    class StructuredData;
}

class PlayerIdentityService : public ICloudListener
{
public:
	PlayerIdentityService(ICloudWrapper& iCloudWrapper, UUIDCreator& i_uuidCreator, UserPrefsWrapper& i_userPrefsWrapper, MessageRouter& i_messageRouter);
	virtual ~PlayerIdentityService();
    void Init();
    virtual std::string GetAccount();
	std::string CreateNewId();
    
    virtual void iCloudDataInitialSyncChange();
    virtual void iCloudDataServerChangeWithChangedKeys(const char** keys);
    //virtual void iCloudAccountDidSignout();
    //virtual void iCloudStorageNotAvailable();
    virtual void iCloudDidFinishInitialization();
    virtual void iCloudAccountDidSignInFirstTime();
	
protected:
	// DATA FOR TEST
	FakeHttpDriver* m_HttpDriverForTest;
	
private:
	void accountStoredInKvStore();
	std::string accountStoredLocally();
	void onUpdateAccountID(const Sexy::StructuredData* i_response);
	void postMergeRequest(const std::string& i_iCloudAccountId, const std::string& i_userPrefsAccountId);
    
	ICloudWrapper& m_iCloudWrapper;
    UUIDCreator& m_UUIDCreator;
    UserPrefsWrapper& m_userPrefsWrapper;
    MessageRouter& m_messageRouter;
    std::vector<Sexy::StructuredData*> m_createdRequests;
};

namespace Message
{
    void BindAskForMerge(const Sexy::StructuredData* i_request);
    void UpdateAccountId(const Sexy::StructuredData* i_response);
}

#endif /* defined(__PlantsVersusZombies2__PlayerIdentityService__) */
