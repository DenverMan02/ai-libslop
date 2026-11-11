//
//  FakeNetworkObjects.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen on 3/4/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_FakeNetworkObjects_h
#define PlantsVersusZombies2_FakeNetworkObjects_h

#include "OnlineDataPersistor.h"
#include "PlayerInfoDeltaHandler.h"
#include "PlayerIdentityService.h"
#include "NetworkStatusDecider.h"
#include "FacebookIdBinder.h"
#include "ServerConfig.h"
#include "GameEventMgr.h"
#include "UserPrefsWrapper.h"
#include "UUIDCreator.h"
#include "SexyAppFramework/drivers/facebook/NullFacebookDriver.h"
#include "ICloudWrapper.h"
#include "MergePlayerInfosOnServer.h"
#include "IdentityMessages.h"

class FakeICloudWrapper: public ICloudWrapper
{
public:
    void StoreStringValue(const std::string& i_key, const std::string& i_value)
    {
        m_storeStringValueWasCalled = true;
        m_storedKey = i_key;
        m_storedValue = i_value;
    }
    
    std::string GetStringValue(const std::string& i_key)
    {
        if(i_key.compare(m_expectedKey) == 0)
        {
            return m_expectedValue;
        }
        
        return "";
    }
    
    bool Synchronize()
    {
        return m_synchronized;
    }
	
	void SetListener(ICloudListener* listener)
	{
		m_expectedListener = listener;
	}
	
	std::string m_expectedKey = "";
    std::string m_expectedValue = "";
    std::string m_storedKey;
    std::string m_storedValue;
    bool m_synchronized = true;
    bool m_storeStringValueWasCalled = false;
	ICloudListener* m_expectedListener = NULL;
};

class FakePlayerIdentityService : public PlayerIdentityService
{
public:
	FakePlayerIdentityService(ICloudWrapper& iCloudWrapper, UUIDCreator& uuidCreator, UserPrefsWrapper& userPrefsWrapper, MessageRouter& i_messageRouter)
	: PlayerIdentityService(iCloudWrapper, uuidCreator, userPrefsWrapper, i_messageRouter)
	{}
    std::string GetAccount()
    {
        return m_account;
    }    
    std::string m_account;
};

class FakeNetworkStatusDecider : public NetworkStatusDecider
{
public:
    virtual const bool ShouldSendNetworkRequest() const
    {
        return m_shouldSendNetworkRequest;
    }
    bool m_shouldSendNetworkRequest = true;
};

class FakeLoadNetworkServiceListener : public LoadNetworkServiceListener
{
public:
	FakeLoadNetworkServiceListener(IDataPersistor& unusedCtorArg)
	: LoadNetworkServiceListener(unusedCtorArg)
	{
	}
	
	void SetUpDataForTest(RtSerialBuffer& i_buffer)
	{
		LoadNetworkServiceListener::loadFromBuffer(i_buffer);
		LoadNetworkServiceListener::notifyDataLoaded();
	}
};

class FakeOnlineDataPersistor :public OnlineDataPersistor
{
public:
	FakeOnlineDataPersistor(ServerConfigGetter& serverConfigGetter, PlayerIdentityService& playerIdentityService, IDataPersistor& offlineDataPersistor, PlayerInfoDeltaHandler& deltaHandler)
	: OnlineDataPersistor(serverConfigGetter, playerIdentityService, offlineDataPersistor, deltaHandler)
	, loadCalled(false)
	, loadWithNotifyCalled(false)
	, saveCalled(false)
	, rtWriter(&rtBuffer)
	{}
	void Load() { loadCalled = true; }
	void LoadWithNotify() { loadWithNotifyCalled = true; }
	Sexy::RtSerialRtonWriter Save() { saveCalled = true; return rtWriter; }
	
	bool loadCalled;
	bool loadWithNotifyCalled;
	bool saveCalled;
    Sexy::RtSerialBuffer rtBuffer;
    Sexy::RtSerialRtonWriter rtWriter;
};


class FakeOfflineDataPersistor :public OfflineDataPersistor
{
public:
	FakeOfflineDataPersistor()
	: OfflineDataPersistor()
	, loadCalled(false)
	, loadWithNotifyCalled(false)
	, saveCalled(false)
    , rtWriter(&rtBuffer)
	{}
	void Load() { loadCalled = true; }
	void LoadWithNotify() { loadWithNotifyCalled = true; }
	Sexy::RtSerialRtonWriter Save() { saveCalled = true; return rtWriter; }
	
	bool loadCalled;
	bool loadWithNotifyCalled;
	bool saveCalled;
    Sexy::RtSerialBuffer rtBuffer;
    Sexy::RtSerialRtonWriter rtWriter;
};

class FakePlayerInfoDeltaHandler : public PlayerInfoDeltaHandler
{
public:
	FakePlayerInfoDeltaHandler()
	: loadCalled(false)
	, loadWithNotifyCalled(false)
	, saveCalled(false)
	, updateFileIndexCalled(false)
	, rtWriter(&rtBuffer)
	{}
	void Load() { loadCalled = true; }
	void LoadWithNotify() { loadWithNotifyCalled = true; }
	Sexy::RtSerialRtonWriter Save() { saveCalled = true; return rtWriter; }
	void UpdateFileIndex() { updateFileIndexCalled = true; }
	
	bool loadCalled;
	bool loadWithNotifyCalled;
	bool saveCalled;
	bool updateFileIndexCalled;
    Sexy::RtSerialBuffer rtBuffer;
    Sexy::RtSerialRtonWriter rtWriter;
};

class FakeServerConfigGetter: public ServerConfigGetter {
public:
    void SetIp(const std::string& ip) { m_serverConfig.ip = ip; }
    void SetAppId(const std::string& appId) { m_serverConfig.fb_app_id = appId;}
	void SetPermissions(const std::string& permissions) { m_serverConfig.fb_permissions = permissions; }
protected:
	ServerConfig* getServerConfig()
	{
		return &m_serverConfig;
	}
private:
	ServerConfig m_serverConfig;
};

class FakeFacebookIdBinder : public FacebookIdBinder {
public:
	FakeFacebookIdBinder(ServerConfigGetter& serverConfigGetter, MessageRouter& i_messageRouter)
	: FacebookIdBinder(serverConfigGetter, i_messageRouter)
	, facebookIdPassedIn()
	, authTokenPassedIn()
	{}
	
	void Bind(const std::string& i_pcpId, const std::string& i_FacebookId, const std::string& i_AuthToken)
	{
		pcpIdPassedIn = i_pcpId;
		facebookIdPassedIn = i_FacebookId;
		authTokenPassedIn = i_AuthToken;
	}
	
	std::string pcpIdPassedIn;
	std::string facebookIdPassedIn;
	std::string authTokenPassedIn;
};

class FakeUserPrefsWrapper: public UserPrefsWrapper
{
public:
    std::string fakeAccountId;
    
    std::string m_setKey;
    std::string m_setValue;
    std::string m_getKey;
    
	FakeUserPrefsWrapper()
	: fakeAccountId()
	, m_setKey()
	, m_setValue()
	, m_getKey()
	{}
	
    const std::string GetString(const std::string& i_key, std::string i_defaultValue = "")
    {
        m_getKey = i_key;
		
        if(fakeAccountId.empty())
            return i_defaultValue;
        return fakeAccountId;
    }
    
    void SetString(const std::string &i_key, std::string i_value)
    {
        m_setKey = i_key;
        m_setValue = i_value;
    }
    
    void SetFakeAccountId(const std::string& i_fakeAccountId)
    {
        fakeAccountId = i_fakeAccountId;
    }
};

class FakeUUIDCreator: public UUIDCreator
{
public:
    std::string Create()
    {
        return m_UUID;
    }
    
    std::string m_UUID;
};

class FakeIFacebookDriver : public Sexy::NullFacebookDriver {
public:
	FakeIFacebookDriver()
	: appIdArg("")
	, readPermissionsArg("")
	, allowLoginUIArg(false)
	, callbackArg(NULL)
	, openSessionForReadReturnValue(false)
	, expectedPermissions("requestedPermissions")
	, expectedAppId("myAppId")
	, facebookId("myFacebookId")
	, authToken("myAuthToken")
	{
	}
    
	void InitWithAppId( const std::string& appId ) {
		appIdArg = appId;
	}
	bool OpenSessionForRead( const std::string& readPermissions, bool allowLoginUI, SessionStateCallback callback ) {
		if(appIdArg == expectedAppId) {
			readPermissionsArg = readPermissions;
			allowLoginUIArg = allowLoginUI;
			callbackArg = callback;
			return openSessionForReadReturnValue;
		}
		return false;
	}
	//	bool IsOpen() const {
	//		return false;
	//	}
	//	bool IsOpening() const {
	//		return false;
	//	}
	//	SessionState GetSessionState() const {
	//		return SessionClosed;
	//	}
	std::string GetUserId() const {
		return facebookId;
	}
	std::string GetAccessToken() const {
		return authToken;
	}
	std::string appIdArg;
	std::string readPermissionsArg;
	bool allowLoginUIArg;
	bool openSessionForReadReturnValue;
	SessionStateCallback callbackArg;
	std::string expectedPermissions;
	std::string expectedAppId;
	std::string facebookId;
	std::string authToken;
};


//
// Network Message Catchers
//
struct UpdateAccountIdMessageCatcher
{
    UpdateAccountIdMessageCatcher(MessageRouter& messageRouter)
    {
        messageRouter.Subscribe(Message::UpdateAccountId, MakeDelegate(*this, &UpdateAccountIdMessageCatcher::onFired));
    }
    
    void onFired(const Sexy::StructuredData* i_response)
    {
        responses.push_back(i_response);
    }
    
    std::vector<const Sexy::StructuredData*> responses;
};

struct BindAskForMergeMessageCatcher
{
    BindAskForMergeMessageCatcher(MessageRouter& messageRouter)
    {
        messageRouter.Subscribe(Message::BindAskForMerge, MakeDelegate(*this, &BindAskForMergeMessageCatcher::onFired));
    }
    
    void onFired(const Sexy::StructuredData* i_response)
    {
        responses.push_back(i_response);
    }
    
    std::vector<const Sexy::StructuredData*> responses;
};

struct BindPCPIdAlreadyBoundMessageCatcher
{
    BindPCPIdAlreadyBoundMessageCatcher(MessageRouter& messageRouter)
    : callCount(0)
    {
        messageRouter.Subscribe(Message::BindPCPIdAlreadyBound, MakeDelegate(*this, &BindPCPIdAlreadyBoundMessageCatcher::onFired));
    }
    
    void onFired()
    {
        ++callCount;
    }
    
    int callCount;
};

struct AccountIdChangedMessageCatcher
{
    AccountIdChangedMessageCatcher(MessageRouter& messageRouter)
    : callCount(0)
    {
        messageRouter.Subscribe(Message::AccountIdChanged, MakeDelegate(*this, &AccountIdChangedMessageCatcher::onFired));
    }

    void onFired()
    {
        ++callCount;
    }
    
    int callCount;
};

struct ForceReloadDataMessageCatcher
{
    ForceReloadDataMessageCatcher(MessageRouter& messageRouter)
    : callCount(0)
    {
        messageRouter.Subscribe(Message::ForceReloadData, MakeDelegate(*this, &ForceReloadDataMessageCatcher::onFired));
    }
    
    void onFired()
    {
        ++callCount;
    }
    
    int callCount;
};

#endif
