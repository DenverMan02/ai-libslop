//
//  NetworkCacheQueue.h
//  PlantsVersusZombies2
//
//  Created by Rain Chen "Chen Liang" on 14-2-27.
//  Copyright (c) 2014年 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_NetworkCacheQueue_h
#define PlantsVersusZombies2_NetworkCacheQueue_h

#include "RtObject.h"
#include "GameObject.h"
#include "NetworkData.h"

#define MAX_LENGTH_NAME 64

namespace
{
    const int k_gemsObjectId = 3008;
}

struct NetworkCachePendant
{
    int32   id;
    int32   objectId;
    int32   level;
};

struct NetworkCacheFragement
{
    int32   fragmentId;
    int32   fragmentCount;
};

struct NetworkCacheObjects
{
    int32 objectId;
    int32 quantity;
    std::string source;
};

class NetworkCacheQueue  : public GameObject
{
public:
	RT_CLASS_DEFINE(NetworkCacheQueue, GameObject, RtClass);
    
    NetworkCacheQueue();
    ~NetworkCacheQueue();
    
    void insertCachedObject(int i_objectId, int i_quantity, std::string i_src);
    void insertCachedObject(std::vector<NetworkCacheObjects> i_needCachedObjects);
    std::vector<NetworkCacheObjects>& getCachedObjects() { return m_cachedObjects; }
    
//    void insertFragementCache(std::string fragmentId, int32 count);
    void insertAddFreeGemId(int actid);
    void insertPlantFragmentCache(int fragmentId, int count);
    void insertDressFragmentCache(int fragmentId, int count);
    void insertPendantFragmentCache(int fragmentId, int count);
    void insertPendantCache(int pendantId, int objectId, int level);
    
    void insertItemFragmentCache(const std::vector<NetworkItemInfo>& i_infos);
    void removeSyncItemFragment(const std::vector<NetworkItemInfo>& i_infos);
    
    std::vector<NetworkCacheFragement>& getPlantFragmentCache() {return m_vecPlantFragments;}
    std::vector<NetworkCacheFragement>& getDressFragmentCache() {return m_vecDressFragments;}
    std::vector<NetworkCacheFragement>& getPendantFragmentCache() {return m_vecPendantFragments;}
    std::vector<NetworkCachePendant>& getPendantCache() {return m_vecPendants;}
    
    std::vector<NetworkItemInfo>& getItemFragmentCache() {return m_vecItemFragments;}
    void clearItemFragmentCache();
    void clearPlantFragmentCache();
    bool ConvertPlantFragmentToItemFragment();
    
    std::vector<int>& getAddFreeGemIdCache() {return m_vecAddFreeGemIds;}
    bool isItemCacheEmpty();
    bool isNetCacheEmpty();
    bool flush();
    void onFlushedCachedObjects(bool success);
    void onFlushPlantFinish(int needFlush);
    void onFlushAvatarFinish(int needFlush);
    void onFlushPendantFinish(int needFlush);
    void onFlushAddFreeGemFinish(bool success);
    
    void setUserID(const std::string& userID) { m_sUserID = userID; }
    std::string getUserID() { return m_sUserID; }
    
    void setSessionKey(const std::string& sessionKey) { m_sSK = sessionKey; }
    std::string getSessionKey() { return m_sSK; }

    void setDefineID(const std::string& defineID) { m_sDefineID = defineID; }
    std::string getDefineID() { return m_sDefineID; }
    
    void setSinaAccessToken(const std::string& token) { m_sSinaAccessToken = token; }
    std::string getSinaAccessToken()                  { return m_sSinaAccessToken;  }
    void setSinaUserID(const std::string& userID)     { m_sSinaUserID = userID;     }
    std::string getSinaUserID()                       { return m_sSinaUserID;       }
    void setSinaExpireDate(const std::string& ed)     { m_sSinaExpireDate = ed;     }
    std::string getSinaExpireDate()                   { return m_sSinaExpireDate;   }
    
    void setWechatAccessToken(const std::string& token) { m_sWechatAccessToken = token; }
    std::string getWechatAccessToken()                  { return m_sWechatAccessToken;  }
    void setWechatUserID(const std::string& userID)     { m_sWechatUserID = userID;     }
    std::string getWechatUserID()                       { return m_sWechatUserID;       }
    void setWechatExpireDate(const std::string& ed)     { m_sWechatExpireDate = ed;     }
    std::string getWechatExpireDate()                   { return m_sWechatExpireDate;   }
    
    void setTencentAccessToken(const std::string& token) { m_sTencentAccessToken = token; }
    std::string getTencentAccessToken()                  { return m_sTencentAccessToken;  }
    void setTencentUserID(const std::string& userID)     { m_sTencentUserID = userID;     }
    std::string getTencentUserID()                       { return m_sTencentUserID;       }
    void setTencentExpireDate(const std::string& ed)     { m_sTencentExpireDate = ed;     }
    std::string getTencentExpireDate()                   { return m_sTencentExpireDate;   }
    
    
    bool isWorldFreeGemAlreadyGet(const std::string& bonusName);
    void addWorldFreeGemsGet(const std::string& bonusName);
    void removeWorldFreeGemsGet(const std::string& bonusName);

    bool isSyncProfile() { return m_isSyncProfile; }
    void setSyncProfile(bool i_finish) { m_isSyncProfile = i_finish; }

protected:
    int32       m_iPlayerId;
    int64       m_llReqSeq;
    
    std::string m_sUserID;
    std::string m_sSK;
    std::string m_sDefineID;
    
    std::vector<NetworkCacheObjects> m_cachedObjects;
    
    std::vector<NetworkCacheFragement> m_vecPlantFragments;
    std::vector<NetworkCacheFragement> m_vecDressFragments;
    std::vector<NetworkCacheFragement> m_vecPendantFragments;
    std::vector<NetworkCachePendant> m_vecPendants;
    
    std::vector<NetworkItemInfo> m_vecItemFragments;
    
    
    std::vector<int> m_vecAddFreeGemIds;
    std::vector<std::string> m_vecFreeGemMarks;
    bool        m_isFlushing;
    
    std::string m_sSinaAccessToken;
    std::string m_sSinaUserID;
    std::string m_sSinaExpireDate;
    
    std::string m_sWechatAccessToken;
    std::string m_sWechatUserID;
    std::string m_sWechatExpireDate;
    
    std::string m_sTencentAccessToken;
    std::string m_sTencentUserID;
    std::string m_sTencentExpireDate;
    bool		m_isSyncProfile;
};
typedef RtWeakPtr<class NetworkCacheQueue> NetworkCacheQueuePtr;

#endif
