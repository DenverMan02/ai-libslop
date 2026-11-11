/*
 * LawnStringUpdater.h
 *
 *  Created on: 2023-7-10
 *      Author: admin
 */

#ifndef LAWNSTRINGUPDATER_H_
#define LAWNSTRINGUPDATER_H_

#include "Core.h"
#include "NetworkServiceManager.h"

struct LawnStringFileInfo
{
	LawnStringFileInfo()
	: m_fileName("")
	, m_md5("")
	{

	}

	std::string m_fileName;
	std::string m_md5;
};

enum LawnStringRequestStage
{
	LawnStringRequestStage_None,
	LawnStringRequestStage_GetFileInfo,
	LawnStringRequestStage_GetFile
};

class NetworkLawnStringInfo : public RtObject
{
public:
    RT_CLASS_DEFINE(NetworkLawnStringInfo, RtObject, RtClass);
    NetworkLawnStringInfo()
    : m_fileName("")
    , m_md5("")
    {}
public:
    std::string m_fileName;
    std::string m_md5;

    bool SerializeJson(const std::string &i_json);
    std::string SerializeObj();
};

class LawnStringUpdater : public Sexy::NetworkServiceListener, public LazySingleton<LawnStringUpdater>
{
public:
	LawnStringUpdater();
    virtual ~LawnStringUpdater();

public:
	void CheckForUpdates(int i_retries = 0);
    void TryRequest(LawnStringRequestStage i_stage);
    void OnRequestFinished(std::string i_json);

    void ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context);
    void ServiceRequestFailed(const Sexy::StructuredData*, const void* i_context);
    void ServiceRequestCompleted(ImageLib::Image*&, const void* i_context);
    void ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context);

private:
    void Init();
    std::string GetLocalLawnStringMd5();

    int         m_retriesLeft;
    std::string m_fileInfoUrl;
    std::string m_fileUrl;

    LawnStringRequestStage m_currentStage;
    LawnStringFileInfo m_fileInfo;
};


#endif /* LAWNSTRINGUPDATER_H_ */
