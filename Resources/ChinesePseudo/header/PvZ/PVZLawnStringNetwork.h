/*
 * PVZLawnStringNetwork.h
 *
 *  Created on: 2014-4-24
 *      Author: jianglc
 */

#ifndef PVZLAWNSTRINGNETWORK_H_
#define PVZLAWNSTRINGNETWORK_H_

#include "NetworkServiceManager.h"
#include "PVZDB.h"
#include "PVZVersion.h"

namespace Message
{
    void FetchLawnStringComplete();
}

class PVZLawnStringNetwork : public Sexy::NetworkServiceListener
{
public:
	PVZLawnStringNetwork();
	void CheckForUpdates(int i_retries = 0);
    void TryRequest();
    void OnRequestFinished(std::string i_json);

    void ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context);
    void ServiceRequestFailed(const Sexy::StructuredData*, const void* i_context);
    void ServiceRequestCompleted(ImageLib::Image*&, const void* i_context);
    void ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context);

    std::string GetUpdateUrl();

private:
    int         m_retriesLeft;
    std::string m_updateUrl;
};


#endif /* PVZLAWNSTRINGNETWORK_H_ */
