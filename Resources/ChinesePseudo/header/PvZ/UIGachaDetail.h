
#ifndef _UI_GACHA_DETAIL_H_
#define _UI_GACHA_DETAIL_H_

#include "DNode/DNodeWidget.h"

struct S2C_PlayerGetGachaInfo
{
    std::vector<int> m_plantGroup;
    std::vector<int> m_pieceGroup;
};

struct S2C_PlayerGetAvatarInfo
{
    std::vector<int> m_plantGroup;
    std::vector<int> m_pieceGroup;
};

struct S2C_PlayerGetGachaGroupInfo
{
    S2C_PlayerGetGachaInfo m_chest1;
    S2C_PlayerGetGachaInfo m_chest2;
    S2C_PlayerGetGachaInfo m_chest3;
    S2C_PlayerGetAvatarInfo m_chest4;
};

class GachaDetailCacheMgr:public DSingleton<GachaDetailCacheMgr>
{
public:
    GachaDetailCacheMgr();
    void requestGetGachaDetail();
    void updateFromNetWork();
    void saveGachaDetail();
    void loadNativeInfos();
    int  getTimeLimitedId(int index,bool isPlant);
    
    bool isTimeLimited(int index);
    bool isNew(int index);
    void clean(int chestId,bool isPlant);
    
    bool                                bHasDoc = false;
    std::string                         version = "20130101";
    S2C_PlayerGetGachaGroupInfo         nativeRewardList;
    S2C_PlayerGetGachaGroupInfo         netWorkRewardList;
    S2C_PlayerGetGachaGroupInfo         timeLimitedRewardList;
};

class UIGachaChest:public DNodeWidget
{
public:
    static UIGachaChest* create(int chestId,const Rect& rect);
    
    virtual void Initialize() override;
    virtual void UserInit() override;
    void updateNew(bool force = false);
public:
    int  m_pChestId = 0;
    bool m_isNew = false;
    bool m_isTimeLimited = false;
};

class UIGachaDetail:public DNodeWidget
{
public:
    static bool createWithNetwork();
    
    static UIGachaDetail* create(bool focus = true);
    
    static void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    static void onMsgErrorRequest(int erroId, const std::string& i_reqID);
    
    static bool isActive(){return s_isActive;}
    static void setUnactive();
    
    virtual ~UIGachaDetail();
    
    virtual void Initialize() override;
    
    virtual void UserInit() override;
    
    void loadWithNetMessage();
    
    void setGachaInfo(int index);
    
    void updatePlantsShow();
    void updatePlantPiecesShow();
    void updateItems(const std::vector<int>& list,const std::map<int,int>& mp);
    void updateInfo();
    std::string getInfoAliases(int i_chestIndex);
    void getGachaDetailFromNetwork(const std::vector<int>& plantInfos,const std::vector<int>& newPlantInfos,const std::vector<int>& limitedPlantInfos,const std::vector<int>& plantPieceInfos,const std::vector<int>& newPieceInfos,const std::vector<int>& limitedPieceInfos);
private:
    std::vector<int>            m_plantslist;
    std::map<int,int>           m_newPlantsMap;
    std::vector<int>            m_pieceslist;
    std::map<int,int>           m_newPiecesMap;
public:
    int    m_chestIndex = 0;
    bool   m_bIsPlantMode = true;
    bool   m_bIsInfoMode = false;
    static UIGachaDetail* s_pWidgetHandler;
    static bool s_isActive;
};

/// UICornucopiaBonusDetail
class UICornucopiaBonusDetail : public DNodeWidget
{
public:
    static UICornucopiaBonusDetail* create(bool focus = true);

    virtual ~UICornucopiaBonusDetail();
    virtual void Initialize() override;
    virtual void UserInit() override;

    void InitPlantsList(const std::vector<int>& list);
    void updateItems(const std::vector<int>& list);
    void updatePlantsShow();
    void updateInfo();

    std::vector<int> GetTestData();

private:
    std::vector<int>            m_plantslist;

public:
    bool   m_bIsPlantMode = true;
    bool   m_bIsInfoMode = false;
    static UICornucopiaBonusDetail* s_pCornucopiaBonusDetailWidgetHandler;
};


#endif
