//
//  AssetsManagerManifest.h
//  PlantsVersusZombies2
//
//  Created by chenjd on 16/5/18.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef AssetsManagerManifest_hpp
#define AssetsManagerManifest_hpp

#include <string>
#include <unordered_map>
#include <vector>

#include "StructuredData.h"

struct DownloadUnit
{
    std::string srcUrl;
    std::string storagePath;
    std::string customId;
};

typedef std::unordered_map<std::string, DownloadUnit> DownloadUnits;

class AssetsManagerManifest
{
public:
    
    friend class AssetsManagerEx;
    
    //! The type of difference
    enum class DiffType
    {
        ADDED,
        DELETED,
        MODIFIED
    };
    
    enum class DownloadState
    {
        UNSTARTED,
        DOWNLOADING,
        SUCCESSED
    };
    
    //! Asset object
    struct Asset
    {
        std::string   md5;
        std::string   path;
        bool          compressed;
        DownloadState downloadState;
        
        Asset()
        {
            md5  = "";
            path = "";
            compressed = false;
            downloadState = DownloadState::UNSTARTED;
        }
    };
    
    //! Object indicate the difference between two Assets
    struct AssetDiff
    {
        Asset asset;
        DiffType type;
    };
    
    /** @brief Constructor for Manifest class
     * @param manifestUrl Url of the local manifest
     */
    AssetsManagerManifest(const std::string& manifestUrl = "");
    
    /** @brief Parse the manifest file information into this manifest
     * @param manifestUrl Url of the local manifest
     */
    void parse(const std::string& manifestUrl);
    
    /** @brief Check whether the version informations have been fully loaded
     */
    bool isVersionLoaded() const;
    
    /** @brief Check whether the manifest have been fully loaded
     */
    bool isLoaded() const;
    
    /** @brief Gets remote package url.
     */
    const std::string& getPackageUrl() const;
    
    /** @brief Gets remote manifest file url.
     */
    const std::string& getManifestFileUrl() const;
    
    /** @brief Gets remote version file url.
     */
    const std::string& getVersionFileUrl() const;
    
    /** @brief Gets manifest version.
     */
    const std::string& getVersion() const;
    
    /** @brief Get the search paths list related to the Manifest.
     */
    std::vector<std::string> getSearchPaths() const;
    
    /** @brief Gets Total file size.
     */
    float getTotalFileSize() const;
    
    static int getVersionToInt(std::string i_version);
    
protected:
    
    /** @brief Load the json file into local json object
     * @param url Url of the json file
     */
    void loadJson(const std::string& url);
    
    /** @brief Parse the version file information into this manifest
     * @param versionUrl Url of the local version file
     */
    void parseVersion(const std::string& versionUrl, const std::string& rsbVersion);
    
    /** @brief Check whether the version of this manifest equals to another.
     * @param b   The other manifest
     */
    bool versionEquals(const AssetsManagerManifest *b) const;
    
    /** @brief Generate difference between this Manifest and another.
     * @param b   The other manifest
     */
    std::unordered_map<std::string, AssetDiff> genDiff(const AssetsManagerManifest *b) const;
    
    /** @brief Generate resuming download assets list
     * @param units   The download units reference to be modified by the generation result
     */
    void genResumeAssetsList(DownloadUnits *units, const std::string& i_cdnUrl, const std::string& rsbVersion) const;
    
    /** @brief Prepend all search paths to the FileUtils.
     */
    void prependSearchPaths();
    
    void loadVersion(const Sexy::StructuredData &json, const std::string& rsbVersion);
    
    void loadManifest(const Sexy::StructuredData &json);
    
    void saveToFile(const std::string &filepath);
    
    Asset parseAsset(const std::string &path, const Sexy::StructuredData::Value &json);
    
    void clear();
    
    /** @brief Gets all groups.
     */
    const std::vector<std::string>& getGroups() const;
    
    /** @brief Gets all groups version.
     */
    const std::unordered_map<std::string, std::string>& getGroupVerions() const;
    
    /** @brief Gets version for the given group.
     * @param group   Key of the requested group
     */
    const std::string& getGroupVersion(const std::string &group) const;
    
    /**
     * @brief Gets assets.
     * @lua NA
     */
    const std::unordered_map<std::string, Asset>& getAssets() const;
    
    /** @brief Set the download state for an asset
     * @param key   Key of the asset to set
     * @param state The current download state of the asset
     */
    void setAssetDownloadState(const std::string &key, const DownloadState &state);
    
private:
    
    //! Indicate whether the version informations have been fully loaded
    bool _versionLoaded;
    
    //! Indicate whether the manifest have been fully loaded
    bool _loaded;
    
    //! Reference to the global file utils
    //FileUtils *_fileUtils;
    
    //! The local manifest root
    std::string _manifestRoot;
    
    //! The remote package url
    std::string _packageUrl;
    
    //! The remote path of manifest file
    std::string _remoteManifestUrl;
    
    //! The remote path of version file [Optional]
    std::string _remoteVersionUrl;
    
    //! The version of local manifest
    std::string _version;
    
    //! The Total File Size
    float _totalfilesize;
    
    //! All groups exist in manifest [Optional]
    std::vector<std::string> _groups;
    
    //! The versions of all local group [Optional]
    std::unordered_map<std::string, std::string> _groupVer;
    
    //! The version of local engine
    std::string _engineVer;
    
    //! Full assets list
    std::unordered_map<std::string, Asset> _assets;
    
    //! All search paths
    std::vector<std::string> _searchPaths;
    
    Sexy::StructuredData _json;
};

#endif /* AssetsManagerManifest_hpp */
