//
//  PVZUpdater.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-5-6.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PVZUpdater__
#define __PlantsVersusZombies2__PVZUpdater__

#include "Precompile.h"
#include "ContentDownloader.h"
#include "NetworkServiceManager.h"
#include "PVZManifest.h"

enum DLCType
{
	DLCType_Immediate_Update = 1,
	DLCType_Skip,
	DLCType_Download_Finished,
    DLCType_APK_Install,
    DLCType_RES_Installed,
    DLCType_ALL_Finished,
	DLCType_Count,
};

class PVZUpdater : public Sexy::NetworkServiceListener 
{
public:
	PVZUpdater();
	virtual ~PVZUpdater();
    
    static PVZUpdater& Get();
    
    bool CheckNeedShowProgressBar();
    
    void CheckForInit();
    
    bool CheckBaseRSB();

    void CheckForManifest();

    void UpdateDownloading();
    
    void SetNetManiFestMD5(const std::string &i_net_md5);
    
    void OnRequestFinished(std::string i_json);
    void ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context);
    void ServiceRequestFailed(const Sexy::StructuredData*, const void* i_context);
    void ServiceRequestCompleted(ImageLib::Image*&, const void* i_context);
    void ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context);
    
    void SetNeedUpdater(bool i_need_updater);
    bool IsNeedUpdater() const;
    bool IsNeedInstall() const;
    
    bool IsActive();
    
    bool IsDownloadSuccessful();
    
    float GetDownloadProgress();
    
    int   GetTotalFileSize() const
    {
        return m_nTotalFileSize;
    }

    bool  GetHaveManiFest() const
    {
        return m_HaveManifest;
    }
    
    void startDownLoadUpdaterContent();
    
    void startInstallAPK();
    
    void SaveUpdaterVersionInfoToLocal(int i_version);
    
    const bool LoadNewUpdateInfo();
    void SaveNewUpdateToLocal(bool i_new);

    //UI
    void NeedUpdaterTip();
    
    void NeedInstallTip();
    
    void NeedRestartTip();

    void CheckUpdateSO();

private:

    void onContentDownloaderFinished();
    
    void CheckForManifestEntry(const PVZManifest &i_local_manifest,
                               const PVZManifest &i_net_manifest);
    
    int GetDownTotalSize(const PVZManifest &i_manifest);
    
    bool              RSBFileIsExist(const std::string &i_zip_name);
    
    bool              UnZipResFile(const std::string &i_file_path,
                                   const std::string &i_file_name);

    bool CheckFileMD5Tag(const std::string &i_file_name,
                         const std::string &i_net_md5);
    
    const std::string LoadUpdaterPathInfo();
    void              SaveUpdaterPathInfoToLocal(const std::string &i_path);

    const int32       LoadUpdaterVersionInfo();
    
    //Dialog
    
    void onUpdaterDialogCancel();
    void onUpdaterDialogOK();
    
    void onInstallDialogCancel();
    void onInstallDialogOK();
    
    void onRestartDialogOK();
    
    bool UnZipSOFile(const std::string &i_file_path, const std::string &i_file_name);

private:
    
    std::vector<DownloadPath> m_paths;
    int                       m_nTotalFileSize;
    
	ContentDownloader         m_downloader;
    
    std::string               m_net_manifest_md5;
    
    bool                      m_IsNeedUpdater;
    
    std::string               m_apk_path;
    bool                      m_IsNeedInstall;
    
    bool                      m_HaveManifest;
    bool                      m_HaveUpdaterActive;
};

namespace Message
{
	void ShowUpdateProgressButton();
    
    void ShowUpdateTipButton();
}

#endif /* defined(__PlantsVersusZombies2__PVZUpdater__) */
