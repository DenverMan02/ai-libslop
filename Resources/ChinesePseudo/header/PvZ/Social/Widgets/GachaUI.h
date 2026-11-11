//
//  GachaUI.h
//  PlantsVersusZombies2
//
//  Created by Rain Chen on 14-05-18.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GachaUI_h
#define PlantsVersusZombies2_GachaUI_h
#include "Precompile.h"

#include "Widget.h"
#include "RtObject.h"
#include "PVZ2UIButton.h"
#include "Core.h"
#include "Effect_PopAnim.h"
#include "LawnAppEnums.h"

namespace Message
{
    void GachaTutorialFinished();
}

struct GachaRewardUI
{
    int m_rateMin = 0; //used for rolling
    int m_rateMax = 0;
    int m_DisplayId = 0;
    std::string m_type;
    std::string m_sku;
    int mX;
    int mY;
    float mScale;
    bool mDrawEffect;
    bool mIsPlant;
    bool mShouldDrawPlant = true;
    int  mPieceCount;
    bool mNewPlant;
    
    GachaRewardUI(int rateMin, int rateMax, std::string sku, std::string type)
    {
        mX = -1;
        mY = -1;
        m_rateMin = rateMin;
        m_rateMax = rateMax;
        m_sku = sku;
        m_type = type;
        mIsPlant = false;
        mDrawEffect = false;
        mScale = 1.0f;
        mPieceCount = 0;
        mNewPlant = false;
    }
    
    GachaRewardUI(std::string sku, std::string type, bool isPlant, int count, bool isNew)
    {
        mX = -1;
        mY = -1;
        m_sku = sku;
        m_type = type;
        mIsPlant = isPlant;
        mDrawEffect = false;
        mScale = 1.0f;
        mShouldDrawPlant = !mIsPlant;
        if(m_type == "avatar" || m_type == "new_avatar"){
            mShouldDrawPlant = false;
        }
        mPieceCount = count;
        mNewPlant = isNew;
    }
    GachaRewardUI()
    {
        mX = -1;
        mY = -1;
        m_sku = "";
        mIsPlant = false;
        mDrawEffect = false;
        mScale = 1.0f;
        mShouldDrawPlant = !mIsPlant;
        mPieceCount = 0;
    }
    
};

struct RewardItemData
{
    std::string productName;
    std::string productType;
    int         count;
    bool        isPlant;
    bool        isNew;
};


class GachaUI: public Sexy::Widget, public ButtonListener
{
public:
    enum
    {
        gacha_btn_close = 0,
        gacha_btn_again,
    };
    
    
    
    GachaUI(const std::string &i_objectItem, bool bDiamond);
    GachaUI(const std::string &i_objectItem, bool bDiamond, GachaType i_type);
    ~GachaUI();
    
    void Init();
    void InitRewardPool();
    void InitView();
    
    void dealGachaPoolResult();
    
    void ResetGachaGeneralTime();
    void ResetGachaSpecialTime();
    
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void Update();
    //PVZ2_CHINESE_END
    
	virtual void Draw(Graphics* i_g);
	virtual void ButtonDepress(int i_id);
    virtual void TouchEnded(const Sexy::Touch& i_touch);

    
    static void setRewardItemList(const std::vector<RewardItemData>& rewardDatas)
    {
        s_rewardItemList = rewardDatas;
    }
    
public:
	static std::string GetPlantNameByType(const std::string & i_type, const std::string & strSku);
    
    void    addRewardName(std::vector<RewardItemData>& rewardList);
    
private:
    int getGachaGlobalResult();
    int getGachaPlantResult();
    int getGachaFreeResult();
    void dealGacha1Time();
    void dealFirstGacha1Time();
    void dealGacha10Times();
    void dealGachaFree(int i_type = 0);

    void resetUIDisplay();
    void PushGachaResult(GachaRewardUI* gachaReward);
    void ClearGachaResult();
    void DealGachaDayFirstPay(int iIndex);
    void ShowCurrentPlant();
    SexyString getGachaRewardName(int i_index);

	void DrawPlantID_Debug(Graphics* i_g, GachaRewardUI* gachaReward);
    
    
    uint64 GachaGeneralRefreshTime;
    uint64 GachaSpecialRefreshTime;
    time_t lastGachaGeneralTime;
    time_t lastGachaSpecialTime;
    PVZ2UIButton* m_backButton = nullptr;
    PVZ2UIButton* m_redoButton = nullptr;
    
    std::string m_objectType;
    GachaType m_newType;
    bool    m_IsDiamond;
    std::vector<GachaRewardUI* > m_rewardList;
    int m_totalRewardNum;
    int m_currentRewardNum;
    int m_effectAnimIndex;
    
    pvztime_t m_rewardFlyingTime;
    pvztime_t m_rewardFlyingEndTime;
    pvztime_t m_rewardStartAnimTime;
    pvztime_t m_rewardPlantAnimTime;
    pvztime_t m_rewardPlantShowTime;
    
    bool m_isShowingAnim;
    bool m_isShowingPlant;
    bool m_isPaused;
    bool m_isShowAvatarHint;
    
    PopAnimRig   *  m_pAnimRig = nullptr;
    Effect_PopAnim* m_gachaEnterAnimEffect = nullptr;
    Effect_PopAnim* m_gachaPlantAnimEffect = nullptr;
    Effect_PopAnim* m_gachaPlantLightEffect = nullptr;
    std::vector<class Effect_PopAnim* > m_gachaLightAnimEffect;
    
    static std::vector<RewardItemData> s_rewardItemList;
    
    int m_rewardIconStartX;
    int m_rewardIconStartY;
    int m_rewardIconEndX;
    int m_rewardIconEndY;
    int m_rewardIconGapWidth;
    int m_rewardIconGapHeight;
    float m_rewardDrawScale;
};

#endif
