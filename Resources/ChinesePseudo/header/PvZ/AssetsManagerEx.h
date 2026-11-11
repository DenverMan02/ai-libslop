//
//  AssetsManagerEx.hpp
//  PlantsVersusZombies2
//
//  Created by chenjd on 16/5/18.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef AssetsManagerEx_hpp
#define AssetsManagerEx_hpp

#include "Precompile.h"
#include "RtObject.h"
#include "AssetsManagerManifest.h"
#include "ContentDownloader.h"
#include "NetworkServiceManager.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace Message
{
	void NewVersionFound();
}

//! Update events code
enum class EventCode
{
    ERROR_NO_LOCAL_MANIFEST,
    ERROR_DOWNLOAD_MANIFEST,
    ERROR_PARSE_MANIFEST,
    NEW_VERSION_FOUND,
    ALREADY_UP_TO_DATE,
    UPDATE_PROGRESSION,
    ASSET_UPDATED,
    ERROR_UPDATING,
    UPDATE_FINISHED,
    UPDATE_FAILED,
    ERROR_MD5,
    ERROR_DECOMPRESS
};

class AssetsManagerDelegateProtocol
{
public:
    virtual ~AssetsManagerDelegateProtocol()                 {};
    
public:
    
    virtual void dispatchEvent(class AssetsManagerEx * manager,
                               EventCode code,
                               float percent,
                               float percentByFile,
                               const std::string& assetId,
                               const std::string& message,
                               int curle_code,
                               int curlm_code)                      {};
};

/**
 * @brief   This class is used to auto update resources, such as pictures or scripts.
 */
class AssetsManagerEx : public Sexy::NetworkServiceListener, public ContentDownloaderDelegateProtocol
{
public:
    
    //! Update states
    enum class AssetsManagerState
    {
        UNCHECKED,
        PREDOWNLOAD_VERSION,
        DOWNLOADING_VERSION,
        VERSION_LOADED,
        PREVERSION_CHECK,
        VERSION_CHECK,
        PREDOWNLOAD_MANIFEST,
        DOWNLOADING_MANIFEST,
        MANIFEST_LOADED,
        NEED_UPDATE,
        UPDATING,
        UNZIPPING,
        UP_TO_DATE,
        FAIL_TO_UPDATE
    };
    
    const static std::string VERSION_ID;
    const static std::string MANIFEST_ID;
    
    /** @brief Create function for creating a new AssetsManagerEx
     @param manifestUrl   The url for the local manifest file
     @param storagePath   The storage path for downloaded assets
     @warning   The cached manifest in your storage path have higher priority and will be searched first,
     only if it doesn't exist, AssetsManagerEx will use the given manifestUrl.
     */
    // static AssetsManagerEx* create(const std::string &manifestUrl, const std::string &storagePath);
    
    /** @brief  Check out if there is a new version of manifest.
     *          You may use this method before updating, then let user determine whether
     *          he wants to update resources.
     */
    void checkUpdate();
    
    /** @brief Update with the current local manifest.
     */
    void update();
    
    /** @brief Reupdate all failed assets under the current AssetsManagerEx context
     */
    void downloadFailedAssets();
    
    /** @brief Gets the current update state.
     */
    AssetsManagerState getState() const;
    
    /** @brief Gets storage path.
     */
    const std::string& getStoragePath() const;
    
    /** @brief Function for retrieve the local manifest object
     */
    const AssetsManagerManifest * getLocalManifest() const;
    
    /** @brief Function for retrieve the remote manifest object
     */
    const AssetsManagerManifest * getRemoteManifest() const;
    
    /** @brief Sets delegate, the delegate will receive messages
     */
    void setDelegate(AssetsManagerDelegateProtocol * delegate);
    
    void setRsbVersion(const std::string& rsbVersion);

    bool isWaitToUpdate();

    AssetsManagerEx(const std::string& manifestUrl, const std::string& storagePath);
    
    virtual ~AssetsManagerEx();
    
protected:
    
    std::string basename(const std::string& path) const;
    
    std::string get(const std::string& key) const;
    
    void initManifests(const std::string& manifestUrl);
    
    void loadLocalManifest(const std::string& manifestUrl);
    
    void prepareLocalManifest();
    
    void setStoragePath(const std::string& storagePath);
    
    void adjustPath(std::string &path);
    
    void dispatchUpdateEvent(EventCode code, const std::string &message = "", const std::string &assetId = "", int curle_code = 0, int curlm_code = 0);
    
    void versionCheck();
    void downloadVersion();
    void parseVersion();
    void downloadManifest();
    void parseManifest();
    void startUpdate();
    void updateSucceed();
    bool decompress(const std::string &filename);
    void decompressDownloadedZip();
    
    /** @brief Update a list of assets under the current AssetsManagerEx context
     */
    void updateAssets(const DownloadUnits& assets);
    
    /** @brief Retrieve all failed assets during the last update
     */
    const DownloadUnits& getFailedAssets() const;
    
    /** @brief Function for destroying the downloaded version file and manifest file
     */
    void destroyDownloadedVersion();
    
    /** @brief  Call back function for error handling,
     the error will then be reported to user's listener registed in addUpdateEventListener
     @param error   The error object contains ErrorCode, message, asset url, asset key
     @warning AssetsManagerEx internal use only
     * @js NA
     * @lua NA
     */
    /*
    virtual void onError(const network::DownloadTask& task,
                         int errorCode,
                         int errorCodeInternal,
                         const std::string& errorStr);
    */
    
    /** @brief  Call back function for recording downloading percent of the current asset,
     the progression will then be reported to user's listener registed in addUpdateProgressEventListener
     @param total       Total size to download for this asset
     @param downloaded  Total size already downloaded for this asset
     @param url         The url of this asset
     @param customId    The key of this asset
     @warning AssetsManagerEx internal use only
     * @js NA
     * @lua NA
     */
    //virtual void onProgress(double total, double downloaded, const std::string &url, const std::string &customId);
    
    /** @brief  Call back function for success of the current asset
     the success event will then be send to user's listener registed in addUpdateEventListener
     @param srcUrl      The url of this asset
     @param customId    The key of this asset
     @warning AssetsManagerEx internal use only
     * @js NA
     * @lua NA
     */
    //virtual void onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId);
    
    /** For version.manifest and project.manifest
     */
    void ServiceRequestCompleted(const Sexy::StructuredData * i_response, const void * i_context) override;
    void ServiceRequestFailed(const Sexy::StructuredData*, const void * i_context) override;
    void ServiceRequestCompleted(ImageLib::Image*&, const void * i_context) override;
    void ServiceRequestCompleted(const Sexy::Buffer*, const void * i_context) override;
    
    
    /** For DownLoad assets files
    */
    
    void FileDownloadSuccess(const DownloadPath& i_path) override;
    void ContentDownloaderFinished() override;
    void ContentDownProgress(float i_progress) override;
    void ContentDownloaderFailed(const DownloadPath& i_path,
                                 const std::string&  i_errorMsg,
                                 int   i_errorCode) override;
    
private:
    void batchDownload();
    
    // Called when one DownloadUnits finished
    void onDownloadUnitsFinished();
    
    //! The event of the current AssetsManagerEx in event dispatcher
    std::string _eventName;
    
    //! Reference to the global event dispatcher
    //EventDispatcher *_eventDispatcher;
    
    //! Reference to the global file utils
    //FileUtils *_fileUtils;
    
    AssetsManagerDelegateProtocol *_delegate;
    
    //! State of update
    AssetsManagerState _updateState;
    
    //! Downloader
    //std::shared_ptr<network::Downloader> _downloader;
    
    ContentDownloader _downloader;
    
    //! The reference to the local assets
    const std::unordered_map<std::string, AssetsManagerManifest::Asset> *_assets;
    
    //! The path to store downloaded resources.
    std::string _storagePath;
    
    //! The local path of cached version file
    std::string _cacheVersionPath;
    
    //! The local path of cached manifest file
    std::string _cacheManifestPath;
    
    //! The local path of cached temporary manifest file
    std::string _tempManifestPath;
    
    //! The path of local manifest file
    std::string _manifestUrl;
    
    //! Local manifest
    AssetsManagerManifest *_localManifest;
    
    //! Local temporary manifest for download resuming
    AssetsManagerManifest *_tempManifest;
    
    //! Remote manifest
    AssetsManagerManifest *_remoteManifest;
    
    //! Whether user have requested to update
    bool _waitToUpdate;
    
    //! All assets unit to download
    DownloadUnits _downloadUnits;
    
    //! All failed units
    DownloadUnits _failedUnits;
    
    //! All files to be decompressed
    std::vector<std::string> _compressedFiles;
    
    //! Download percent
    float _percent;
    
    //! Download percent by file
    float _percentByFile;
    
    //! Indicate whether the total size should be enabled
    int _totalEnabled;
    
    //! Indicate the number of file whose total size have been collected
    int _sizeCollected;
    
    //! Total file size need to be downloaded (sum of all file)
    double _totalSize;
    
    //! Downloaded size for each file
    std::unordered_map<std::string, double> _downloadedSize;
    
    //! Total number of assets to download
    int _totalToDownload;
    //! Total number of assets still waiting to be downloaded
    int _totalWaitToDownload;
    
    //! Marker for whether the assets manager is inited
    bool _inited;
    
    //! relative address
    std::string m_manifestUrl;
    std::string m_cdnUrl;

    std::string _rsbVersion;
};

#endif /* AssetsManagerEx_hpp */
