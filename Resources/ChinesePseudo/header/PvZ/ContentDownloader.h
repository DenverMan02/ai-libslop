#pragma once

#include <string>
#include <vector>

#include "Crypt/md5.h"
#include "PVZVersion.h"
#include "PlatformAutodetect.h"
#include "SexyAppFramework/NetworkServiceManager.h"
#include "SexyAppFramework/ResStreamsManager.h"
#include "SexyString.h"
#include "TimeMgr.h"

struct DownloadPath
{
    std::string URL;
    std::string SavePath;
    std::string CustomId;
    PVZVersion  Version;
};

class ContentDownloaderDelegateProtocol
{
public:
    virtual ~ContentDownloaderDelegateProtocol()                        {};
    
public:
    
    //one file download
    virtual void FileDownloadSuccess(const DownloadPath& i_path)        {};
    
    //all files download
    virtual void ContentDownloaderFinished()                            {};
    
    virtual void ContentDownProgress(float i_progress)                  {};
    
    virtual void ContentDownloaderFailed(const DownloadPath& i_path,
                                         const std::string&  i_errorMsg,
                                         int   i_errorCode)             {};
};


class ContentDownloader : public Sexy::NetworkServiceListener
{
public:
    ContentDownloader();
    
    void StartDownload(const std::vector<DownloadPath> &i_paths);
    
    void setDelegate(ContentDownloaderDelegateProtocol * delegate);
    
    //
    // NetworkServiceListener
    //
    
    virtual void ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context);
    virtual void ServiceRequestCompleted(ImageLib::Image*& i_image, const void* i_context);
    virtual void ServiceRequestCompleted(const Sexy::Buffer* i_buffer, const void* i_context);
    virtual void ServiceResumableRequestCompleted(const std::string& i_filePath, const void* i_context);
    virtual void ServiceProgressUpdate(uint64 inNumBytesDownloaded, uint64 inTotalBytes, const void* i_context);
    virtual void ServiceRequestFailed(const Sexy::StructuredData* i_response, const void* i_context);
    virtual void ServiceRequestCanceled(const void* context);

    float GetProgress() { return m_progress; }
    bool Completed() { return m_wasDownloadSuccessful; }
    bool Failed() { return !m_downloadUpdateErrorMsg.empty(); }
	bool IsCancelled() { return m_wasDownloadCancelled; }
    bool IsActive();

    const SexyString& GetError() { return m_downloadUpdateErrorMsg; }
    const std::string& GetCurrentURL();

    void Update();
    void Reset();
	
	//Need to return localized keys from here
	virtual std::string ToString( ErrorNum inErrorNum )
	{
		switch(inErrorNum)
		{
			case ErrorNum_CouldNotCreateFile:
				return "[DOWNLOAD_FAILED_SPACE_BODY]";
				
			case ErrorNum_CouldNotWriteToFile:
				return "[DOWNLOAD_FAILED_SPACE_BODY]";
				
			case ErrorNum_FailedToCopyFile:
				return "[DOWNLOAD_FAILED_SPACE_BODY]";
				
			case ErrorNum_BadTargetFilePath:
				return "target_file_path_is_empty_or_invalid";
				
			default:
				return Sexy::NetworkServiceListener::ToString(inErrorNum);
		}
	}
	
    void SetAllowRetries(bool i_enabled);

private:
    
    void onDownloadFailed(const SexyString& inDownloadErrorMsg, int i_errorID);
    void downloadPath(const DownloadPath& i_path);
    void onDownloadCompleted(const std::string& i_file);
    
    ContentDownloaderDelegateProtocol * m_delegate;

    SexyString              m_downloadUpdateErrorMsg;
    std::string             m_lastURL;
    bool                    m_wasDownloadSuccessful;
	bool					m_wasDownloadCancelled;
    float                   m_progress;
    pvztime_t               m_retryTime;
    bool                    m_allowRetries;
    NetworkServiceManager::RequestId m_currentDownloadRequestId;

    int m_currentPath;
    std::vector<DownloadPath> m_paths;
};

namespace Message
{
	void PatchEvent(const std::string& i_eventType, int i_errorCode);
    void ContentDownloaderFinished();
}
