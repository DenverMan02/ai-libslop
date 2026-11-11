/*
 * AccountRemove.h
 *
 *  Created on: 2022-6-14
 *      Author: admin
 */

#ifndef ACCOUNTREMOVE_H_
#define ACCOUNTREMOVE_H_

#include "DNode/DNodeWidget.h"
#include "NetworkData.h"
#include "Singleton.h"

namespace Message
{
	void FinishCheckAccount(bool i_success);
}

enum AccountStatus
{
	AccountStatus_Normal,
	AccountStatus_Frozen,
	AccountStatus_Deleted
};

class AccountRemoveMgr : public LazySingleton <AccountRemoveMgr>
{
public:
	AccountRemoveMgr();
    ~AccountRemoveMgr();

    void TryCheckAccount(bool i_displayUI);
    void CheckAccount(bool i_displayUI);
    void RecoverAccount();
    void DeleteLocalProfile();

    void SetHasCheckAccount(bool i_check) { m_check = i_check; }
    bool HasCheckAccount() { return m_check; }

    bool HasAccountDeleted() { return m_status == AccountStatus_Deleted; }
    bool HasAccountFrozen() { return m_status == AccountStatus_Frozen; }

    void onMsgError(int erroId, const std::string& requestID);

    void DisplayUI();

    const std::string& GetDeletedTime() { return m_deletedTime; }

private:
    void onCheckAccount(bool i_displayUI);

    bool m_check;
    bool m_accountDeleted;
    bool m_accountFrozen;
    std::string m_deletedTime;

    AccountStatus m_status;
};

class NetworkRecoverAccountInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkRecoverAccountInfo, INetworkData, RtClass);

public:
    bool m_success;
};

class NetworkDeleteAccountInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkDeleteAccountInfo, INetworkData, RtClass);

public:
    bool m_success;
    std::string m_time;
};

class NetworkGetAccountInfo : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkGetAccountInfo, INetworkData, RtClass);

public:
    bool m_isAccountDeleted;
    std::string m_time;
};

class AccountRemove:public DNodeWidget
{
public:
	enum AccountRemoveStage
	{
		Stage_Delete_Warning,
		Stage_Freeze_Warning,
		Stage_Delete_Last_Warning,
		Stage_Deleted
	};

    static AccountRemove* create(AccountStatus i_status);
    static AccountRemove* get();

    virtual ~AccountRemove();

    virtual void Initialize() override;

    virtual void UserInit() override;

    void ExitGame();

    void InitUI(AccountStatus i_status);

public:
    static AccountRemove* s_pWidgetHandler;
    AccountRemoveStage m_stage = Stage_Delete_Warning;
    AccountStatus m_status;
};

#endif /* ACCOUNTREMOVE_H_ */
