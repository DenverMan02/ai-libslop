//
//  JoustNetworkMgr.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/26/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_JoustNetworkMgr_h
#define PlantsVersusZombies2_JoustNetworkMgr_h

#include "Core.h"
#include "JoustDataPackets.h"
#include "NetworkServiceManager.h"
#include "NetworkData.h"

class NetworkDashboardInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkDashboardInfo, Sexy::RtObject, Sexy::RtClass);

public:
    int PlayerCrowns;
	int PlayerWinStreak;
	int PlayerLeague;
	int PlayerTotalWins;
	int PlayerLeaderboardPosition;
	int PlayerTickets;

	JoustTournamentData 			Tournament;

	std::vector<JoustPlayerData>	Leaderboard;

	JoustAPIResponseLeagueChange	LeagueChangeEvent;

	std::vector<std::vector<JoustLeaderboardRewardInfo>> LeaderboardRewards;

	std::vector<JoustBonusInfo>		WinStreakRewards;

	bool CanPlay;

	bool IsCheatingCheck;// if cheating check
};

class NetworkPostMatch : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkPostMatch, INetworkData, RtClass);

public:
    std::wstring OpponentName;
	int OpponentAvatarId;
	int OpponentScore;
	std::string ReplayData;
	std::string ArtifactOrderId;
};

class NetworkCompletePostMatch : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkCompletePostMatch, INetworkData, RtClass);

public:
    int WinStreakNum;
    std::vector<JoustBonusInfo> Rewards;
    int EarnedCrown;
	int CheatingCheckWarningLevel;// cheating check warning level
};

class JoustNetworkMgr : public Sexy::NetworkServiceListener, public LazySingleton<JoustNetworkMgr>
{	
public:
    JoustNetworkMgr();
    virtual ~JoustNetworkMgr();
	
	void Send_GetDashboard();
	void Send_PostAvatar(const std::wstring& i_name, int i_iconID, const std::function<void(JoustAPIResponse* response)> i_successCallback, const std::function<void()> i_failCallback);
	void Send_PostCreateOrUpdateMatch(const std::string& i_existingMatchID, const std::function<void(JoustAPIResponse* response)> i_successCallback, const std::function<void()> i_failCallback);
	void Send_PostCompleteMatch(JoustAPIPostCompleteMatch& i_data, const std::function<void(JoustAPIResponse* response)> i_successCallback, const std::function<void()> i_failCallback);
	void Send_PostRegisterForTournament(const std::function<void(JoustAPIResponse* response)> i_successCallback, const std::function<void()> i_failCallback);
	void CheatSendBadRequest();
	
	void CancelCurrentRequest();
	
	void SetCustomNetworkTimeout(int inTimeout) { m_NetworkTimeout = inTimeout; m_UseCustomNetworkTimeout = true; }
	
	JoustAPIResponseStatus GetResponseStatus(JoustAPIContext i_context);
	
	//New apis
	bool CheckCurrentDashboardInfo();
	void SyncDashboardInfo();
	void RequestPostMatch();
	void RequestPostCompleteMatch(JoustAPIPostCompleteMatch& i_data);

	int GetLeagueCount();

	JoustAPIResponseDashboard m_dashboardInfo;

private:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void applyNetworkTime(const IHttpTransaction* http);
	
	std::string getPCPID();
	std::string buildURL(const std::string& i_url);
	void sendRequest(Sexy::StructuredData& i_requestData, JoustAPIContext i_context);
	void initRequestData(Sexy::StructuredData& i_requestData, const std::string& i_requestCommand, bool i_postRequest);
	
    void handleDownloadError(JoustAPIContext i_context, const int i_errorCode);

    void            ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context) {}
	void            ServiceRequestFailed(const Sexy::StructuredData* i_response, const void* i_context) {}
	void            ServiceRequestCompleted(ImageLib::Image*&, const void* i_context) {}
	void            ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context) {}

    // Network service listener overrides
//    virtual void ServiceRequestCompleted( const IHttpTransaction* http, ImageLib::Image*& ioImage, const void* i_context );
//    virtual void ServiceRequestCompleted( const IHttpTransaction* http, const Sexy::StructuredData* response, const void* i_context );
//    virtual void ServiceRequestCompleted( const IHttpTransaction* http, const Sexy::Buffer* buffer, const void* i_context );
//    virtual void ServiceRequestFailed( const IHttpTransaction* http, const Sexy::StructuredData* response, const void* i_context );

	void applySuccessfulResponse(JoustAPIContext i_context, const Sexy::StructuredData* data);
	JoustAPIResponseStatus filterResponseForErrors(const Sexy::StructuredData* data);
	void applySuccessfulDashboardResponse(const NetworkDashboardInfo& i_info);
	void applySuccessfulMatchResponse(const NetworkPostMatch& i_match);
	void applySuccessfulMatchCompleteResponse(const NetworkCompletePostMatch& i_match);
	void applySuccessfulEmptyResponse(JoustAPIContext i_context);
	
	void doFailedResponseCallback(JoustAPIContext i_context, JoustAPIResponseStatus i_status);
	
	LevelOfTheDay_RewardItemType parseRewardStructure(const StructuredData::Value* i_dataContainer);

	bool m_UseCustomNetworkTimeout = false;
	int m_NetworkTimeout;
	
	JoustAPIContext m_expectedContext;
	int m_currentRequestID;
	JoustAPIResponseStatus	m_responseStatus;
	std::function<void(JoustAPIResponse* response)> m_OnSuccessCallback;
	std::function<void()> m_OnFailCallback;
	bool m_requested;
};

#endif
