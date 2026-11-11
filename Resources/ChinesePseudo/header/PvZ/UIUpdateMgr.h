/*
 * UIUpdateMgr.h
 *
 *  Created on: 2018-4-9
 *      Author: Administrator
 */

#ifndef UIUPDATEMGR_H_
#define UIUPDATEMGR_H_

#include "AssetsManagerEx.h"
#include "Singleton.h"
#include "PVZ2UIDialog.h"
#include "NetworkData.h"

class NetworkRsbInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkRsbInfo, INetworkData, RtClass);

public:
	std::string rsbVersion;
};

class UIUpdateMgr : public LazySingleton<UIUpdateMgr>, public AssetsManagerDelegateProtocol
{
public:

	UIUpdateMgr();
    virtual ~UIUpdateMgr();

    void CheckUpdate();

    void DoUpdate();

    bool NeedUpdate() const;

    bool Init();

    void dispatchEvent(AssetsManagerEx * manager,
                       EventCode code,
                       float percent,
                       float percentByFile,
                       const std::string& assetId,
                       const std::string& message,
                       int curle_code,
                       int curlm_code);

    void LoadUIUpdateRSB();

    bool RequestUpdate();
    std::string GetRsbVersion();
    bool IsLoginSuccess();
    void SetLoginSuccess(bool i_success);

protected:

    const char* GetRSBFileName() const;

    std::string GetPackageRSBFilePath();

    void onUIUpdateUpdateCancel();
    void onUIUpdateUpdateOK();

    void onWaitingDialogClose();
    void onMsgErrorRequest(int erroId, const std::string& i_reqID);

private:

    AssetsManagerEx * m_AssetsManagerEx;

    PVZ2WaitingDialog * m_waitingDLG;

    int               m_failCount;
    std::string       m_storagePath;

    bool              m_bNeedUpdate;
    float             m_totalFileSize;
    std::string		  m_rsbVersion;
    bool			  m_loginSuccess;
};


#endif /* UIUPDATEMGR_H_ */
