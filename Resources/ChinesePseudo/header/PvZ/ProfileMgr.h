//
// Popcap (c) 2012
// 
// Original pvz code, refurbed for pvz2. 
// 

#ifndef __PROFILEMGR_H__
#define __PROFILEMGR_H__

#include <string>
#include <map>
#include "SexyAppFramework/Common.h"
#include "PlayerInfo.h"
#include "MagentoService.h"
#include "PurchaseBroker.h"

typedef std::map<long, PlayerInfoPtr > IndexToPlayerInfoMap;
typedef std::map<long, PlayerInfoPtr >::iterator IndexToPlayerInfoMapIter;
typedef std::map<long, PlayerInfoPtr >::const_iterator IndexToPlayerInfoMapConstIter;

class GameEventNotification;
class Throttles;
class DataPersistorFactory;
class PlayerIdentityService;
class ProfileSolver;

//
// Profile Manager - manage player information.
//
class ProfileMgr : public LazySingleton<ProfileMgr>
{

public:
    enum PROFILE_ERR
    {
        PROFILE_NOT_FOUND,
        PROFILE_OK,
        PROFILE_NO_PROFILE,
    };
    
    ProfileMgr();
    ~ProfileMgr();
    
    void                    Init();
    void                    Update();
	void                    LoadAndSetProfile(const std::wstring& i_profileName);
	//void                    LoadAndSetProfile(const std::wstring& i_profileName);
    void                    LoadAndSetProfile(const int i_profileId);
	void 					LoginiCloudServer();
    void                    ReloginiCloudServer();
	bool 					SyncProfileFromServer();

    void                    Save(bool i_bwait = false, bool i_forceSave = false);
    void                    SaveResult(bool i_success);
    bool					isSaving(){ return m_isSaving;}
    void                    SaveAs(PlayerInfo* i_sourcePlayerInfo, const std::wstring& i_newname);
    void                    SaveAsAutoName();
    void                    RequestSave();
    
    void                    SetLockdownForProfileConversion();
    void                    RemoveLockdownForProfileConversion();
    
    void                    SetReadOnlyMode(bool i_status);
    bool                    GetReadOnlyMode();

    PurchaseBroker*         GetPurchaseBroker() { return &m_purchaseBroker; }

	bool                    HasValidProfile() const;
	int                     GetNumProfiles() const;

	PlayerInfoPtr           FindProfile(const std::wstring &i_name);
	PlayerInfoPtr           FindProfileByIndex(long i_index);
	PlayerInfoPtr           FindProfile(const int profileId);
	PlayerInfoPtr           FindProfileByIndex(int32_t i_index);
	PlayerInfoPtr           CreateProfile(const std::wstring &i_name);
	PlayerInfoPtr			CreateProfileFromServer(const std::string i_profileStr);
    PlayerInfoPtr           DuplicateProfile(const PlayerInfo* i_existingProfile, const std::wstring& i_newName);
    void                    ClearAllProfile();

	// Initializes the specified profile to the state it would be in if it were just created
	void                    InitializeProfile(PlayerInfo* i_profile);
	void                    UpdateProfileToLatestVersion(PlayerInfo* i_profile);
    
    PROFILE_ERR             SetCurrentProfile(const std::wstring& i_name); 
    ProfileMgr::PROFILE_ERR SetCurrentProfile(const int profileId);
    PlayerInfo*             GetCurrentProfile();
    PlayerInfo*             GetPurchaseProfile(std::string i_productId = "");
    bool                    UpdateCurrentProfile();
    
	PROFILE_ERR             DeleteProfile(const std::wstring &i_name);  
	PROFILE_ERR             RenameProfile(const std::wstring &i_oldName, const std::wstring &i_newName);
	//PROFILE_ERR             DeleteProfile(const std::wstring &i_name);
    ProfileMgr::PROFILE_ERR DeleteProfile(const int profileId);
	//PROFILE_ERR             RenameProfile(const std::wstring &i_oldName, const std::wstring &i_newName);
    
    std::string             GetAccountName();
    bool                    populateProfiles();
    
    bool                    ChangeHackDataForAug05(PlayerInfo *i_profile);
    bool                    needCheckFakeFromServer();
    bool                    hasPopulateProfiles();
    bool                    replaceUUID();
    inline void				setCanUploadProfileToiCloud( bool i_bcan ){ m_canUpload = i_bcan;}
    inline bool				isCanUploadProfileToiCloud(){ return m_canUpload;}
    void                    removeInvalidProfile();
    void                    removeProfileOwnerError(const std::vector<int>& _vaildProfileIdVec);
    void                    setCurrentProfileIndex(PlayerProfileIndex index) {m_currentProfileIndex = index;}
    PlayerProfileIndex      getCurrentProfileIndex() {return m_currentProfileIndex;}
    void                    closeNeedUpdateUI(){ m_needUpdateUI = false;}
    bool                    getNeedUpdateUI(){return m_needUpdateUI;};
    
    bool					IsSaveDataExist();
    
#ifdef HOST_ANDROID
    void					SetSaveInterval(pvztime_t save_interval){ m_save_interval = save_interval; }
#endif

protected:
    DataPersistorFactory&   m_dataPersistorFactory;

private:
    
	void                                forceReload();
	void								onDialogButtonPressed();
    PROFILE_ERR                         setAnyProfileAsCurrent();
    void                                RealSave();
    
    PlayerInfo*                         m_originalProfile;
	PlayerIdentityService&              m_playerIdentityService;
    
    PurchaseBroker                      m_purchaseBroker;

    PlayerProfileIndex                  m_currentProfileIndex;
    pvztime_t                           m_lastSaveTime;
    pvztime_t                           m_lastCloudSaveTime;
    bool                                m_saveRequested;
    bool                                m_readOnlyMode;
	bool                                m_previousReadOnlyValue;
	std::wstring                        m_profileNameForLoad;
	//std::wstring                        m_profileNameForLoad;
    int                                 m_profileIdForLoad;
	Throttles&                          m_throttles;
    bool                                m_onLockdownDuringProfileConversion;
	bool								m_canUpload;
    
    bool                                m_bHasPopulateProfiles;
    bool 								m_isSaving;
    bool								m_checkErrorSave;
    bool                                m_profileListDirty;
    bool                                m_needUpdateUI;
    bool                                m_needUpLoad;
    bool                                m_wait;

#ifdef HOST_ANDROID
    pvztime_t							m_save_interval;
#endif
};

class PlayerProfileProperties : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PlayerProfileProperties, PropertySheetBase, RtClass);
	
	PlayerProfileProperties()
	{}
	
	// The plants that all new players start with
	std::vector<std::string> InitialPlantList;
private:
};

namespace Message
{
    void ProfileCreated(const PlayerInfoPtr& i_playerInfo);
    void ProfileAboutToBeDeleted(const PlayerInfoPtr& i_playerInfo);
    void ProfileListChanged();
}

#endif
