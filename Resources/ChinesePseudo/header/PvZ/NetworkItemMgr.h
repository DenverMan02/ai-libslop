/*
 * GemOfferMgr.h
 *
 *  Created on: 2017-8-15
 *      Author: Administrator
 */

#ifndef NETWORKITEMMGR_H_
#define NETWORKITEMMGR_H_

#include "NetworkData.h"

namespace Message
{
	void FinishItemAdd();
    void FinishUnsyncItems();
    void FinishGetPlayerinfo();
}

class NetworkItemMgr : public LazySingleton <NetworkItemMgr>
{
public:
	NetworkItemMgr();
    ~NetworkItemMgr();

    void NetworkSetPlantLevel(int i_id, int i_level);
    void NetworkAddPlantPieceCount(const std::vector<NetworkItemInfo>& i_infos);
    bool HasNetworkCacheSyncComplete();
    bool NeedSync();
    bool DoSync();
    bool ReachMaxRetry();
    void ShowWaitingDialog();
    void KillWaitingDialog();
    void SetLoginSuccess(bool i_success) { m_loginSuccess = i_success; }
    bool IsLoginSuccess() { return m_loginSuccess; }
    void TrySyncManually();
    void HandleSyncTask();
    void SetAutoSyncComplete(bool i_complete) { m_finishedSync = i_complete; }
    bool IsSyncComplete() { return m_finishedSync; }
    bool TryCheckUnsyncItems();
private:
    void onMsgError(int erroId, const std::string& requestID);
    void ClearSyncCache();
    void InsertSyncCache(const std::vector<NetworkItemInfo>& i_infos);
    void WaitForSync();
    void OnSyncManually();
    void RemoveSyncCache(const std::vector<NetworkItemInfo>& i_infos);
    void GetUnsyncItems(std::vector<NetworkItemInfo>& i_infos);
    void CheckUnsyncItems(const std::vector<NetworkItemInfo>& i_infos);
    void onFinishGetPlayerinfo();
    bool m_sendingRequest;
    int m_syncCount;
    bool m_showWaitingDialog;
    bool m_loginSuccess;
    bool m_finishedSync;
    bool m_hasUnsyncItems;
};


#endif /* GEMOFFERMGR_H_ */
