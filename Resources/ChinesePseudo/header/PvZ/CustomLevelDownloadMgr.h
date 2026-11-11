/*
 * CustomLevelDownloadMgr.h
 *
 *  Created on: 2021-12-8
 *      Author: admin
 */

#ifndef CUSTOMLEVELDOWNLOADMGR_H_
#define CUSTOMLEVELDOWNLOADMGR_H_

#include "NetworkServiceManager.h"
#include "PVZDB.h"
#include "PVZVersion.h"

class CustomLevelDownloadMgr : public Sexy::NetworkServiceListener
{
public:
	CustomLevelDownloadMgr();
	void Fetch(int i_retries = 0, const std::string& i_serverUrl = "", bool i_save = true, bool i_self = false);
    void OnRequestFinished(std::string i_json);

    void ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context);
    void ServiceRequestFailed(const Sexy::StructuredData*, const void* i_context);
    void ServiceRequestCompleted(ImageLib::Image*&, const void* i_context);
    void ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context);

private:
    void TryRequest();
    void ShowNetConnectUI();
    void RemoveNetConnectUI();

    int         m_retriesLeft;
    std::string m_serverUrl;
    bool 		m_save;
    bool 		m_self;
};


#endif /* CUSTOMLEVELDOWNLOADMGR_H_ */
