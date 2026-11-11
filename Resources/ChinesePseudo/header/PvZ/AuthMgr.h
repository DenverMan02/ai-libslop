/*
 * AuthMgr.h
 *
 *  Created on: 2019-12-4
 *      Author: Administrator
 */

#ifndef AUTHMGR_H_
#define AUTHMGR_H_

#include "Singleton.h"
#include "LawnAppEnums.h"
#include "NetworkData.h"

namespace Message
{
    void NotifyAuthResult(bool i_success);
    void NotifyAuthPaymentResult(bool i_success);
}

struct LocalAuthInfo
{

	LocalAuthInfo()
	{
		HasAuthed = false;
        IsIllegal = false;
        Age = 0;
        Recharge = 0;
	}

	bool HasAuthed;
    bool IsIllegal;
    int Age;
    int Recharge;
};
#ifdef HOST_IPHONEOS
enum PaymentError
{
    Unknown_Payment_Error,
    Payment_OK,
    Per_Payment_Limit,
    Total_Payment_Limit
};

struct LocalAuthAgeInfo
{
    LocalAuthAgeInfo()
    {
        minAge = 0;
        maxAge = 0;
        limitPerPayment = 0;
        limitTotalPayment = 0;
    }
    
    int minAge;
    int maxAge;
    int limitPerPayment;
    int limitTotalPayment;
};

struct LocalAuthPaymentInfo
{
    
    LocalAuthPaymentInfo()
    {
        ProductId = "";
        ObjectId = 0;
    }
    
    std::string ProductId;
    int ObjectId;
};

class NetworkAuthRequestInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkAuthRequestInfo, INetworkData, RtClass);
    
public:
    bool authed;
    int age;
};

class NetworkAuthPaymentInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkAuthPaymentInfo, INetworkData, RtClass);
    
public:
    bool success;    
};
#endif

class NetworkAuthHeartBeatInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkAuthHeartBeatInfo, INetworkData, RtClass);

public:
	bool reachLimit;
};

class AuthMgr : public LazySingleton <AuthMgr>
{
public:
	AuthMgr();
    ~AuthMgr();

    void SetNoAuth(bool i_noAuth) { m_noAuth = i_noAuth; }
    bool HasNoAuth() { return m_noAuth; }

    void SetToken(const std::string& i_token) { m_token = i_token; }
    const std::string& GetToken() { return m_token; }

#ifdef HOST_IPHONEOS
    void SetAuthInfo(bool i_authed, int i_age, int i_recharge);
#else
    void SetAuthInfo(bool i_authed, bool i_illegal);
#endif
    void SetHeartBeatInterval(float i_interval) { m_heartBeatInterval = i_interval; }
    bool HasAuthed();
    bool HasReachLimit() { return m_reachLimit; }
    void Update(float dt);
    bool HandleReachLimit();
    void RequestAuth(const std::string& idcard, const std::string& name);
    void SetLimitDesc(const std::wstring& i_desc) { m_limitDesc = i_desc; }
    void SetDesc(const std::wstring& i_desc) { m_desc = i_desc; }
    const std::wstring& GetDesc() { return m_desc; }
    void SetCharacterId(const std::string& i_id) { m_characterId = i_id; }
    const std::string& GetCharacterId() { return m_characterId; }
#ifdef HOST_IPHONEOS
    void RequestPayment(const std::string& product_id, int objectId);
    void GetPaymentInfo(std::string& product_id, int& objectId);
    void AddRechargeAmount(int i_amount);
    void SetAuthAgeInfo(const std::vector<class AuthAgeInfo>& i_info);
    void HandlePaymentError();
    void SetHasLogin(bool i_login) { m_hasLogin = i_login; }
    bool HasLogin() { return m_hasLogin; }
#endif

private:
#ifdef HOST_IPHONEOS
    PaymentError CheckPayment(int i_price);
    const LocalAuthAgeInfo& FindAgeInfo(int i_age);
    void SortAges();
#endif
    void CheckLegal();
    bool NeedCheck();
    void StartRequest();
    void OnReachLimit();
    void onMsgError(int erroId, const std::string& requestID);

    LocalAuthInfo m_authInfo;
    float         m_heatBeatTimer;
    float 		  m_heartBeatInterval;
    bool		  m_reachLimit;
    bool		  m_noAuth;
    std::wstring  m_limitDesc;
    std::wstring  m_desc;
    std::string   m_characterId;
    std::string   m_token;
#ifdef HOST_IPHONEOS
    LocalAuthPaymentInfo m_paymentInfo;
    std::vector<LocalAuthAgeInfo> m_authAgeInfo;
    PaymentError m_reason;
    bool          m_hasLogin;
#endif
};

#endif /* AUTHMGR_H_ */
