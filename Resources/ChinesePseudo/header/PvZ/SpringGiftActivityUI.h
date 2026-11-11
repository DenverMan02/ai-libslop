//
//  StoreUI.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 8/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SpringGiftActivityUI__
#define __PlantsVersusZombies2__SpringGiftActivityUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "MagentoService.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "ActivityConfig.h"

class CRewardDisplayUI:public Widget
{
public:
    CRewardDisplayUI(int iGems);
    CRewardDisplayUI();
    virtual ~CRewardDisplayUI();
    virtual void DrawAll(Sexy::ModalFlags* theFlags, Graphics* g);
    virtual void Draw(Graphics* i_g);
    virtual void Resize(int theX, int theY, int theWidth, int theHeight);
    virtual void Update();
    virtual void SetRewardGemsCount(int i_rewardGemsCount);
    const struct SSpringRewardInfo* GetReward(){return m_pRewardInfo;};
private:
    SexyString                    m_strPlantDes;
    SexyString                    m_strGemDes;
    int                           m_rewardGems;

    class PlantAnimRig*           m_pAniRig;
    class PlantPropertySheet*     m_pPropSheet;
    SexyTransform2D m_AniTrans;
    int   m_iGems;
    class Effect_PopAnim*   m_pBkAnimRig;
    SexyTransform2D m_BkAniTrans;
    
    const struct SSpringRewardInfo*     m_pRewardInfo;
};

class CSpringGiftActivityRewardUI : public Widget, public ButtonListener
{
public:
    CSpringGiftActivityRewardUI( int iGem);
    CSpringGiftActivityRewardUI( );
    virtual ~CSpringGiftActivityRewardUI();
    
    virtual void DrawAll(Sexy::ModalFlags* theFlags, Graphics* g);
    virtual void Draw(Graphics* i_g);
    virtual void ButtonPress(int i_id);
    virtual void ButtonDepress(int i_id);
    virtual void SetRewardGemsCount(int i_rewardGemCount);
    virtual void OnOK();
private:
    Rect  m_bksizeRect;
    Rect  m_internalRect;
    Rect  m_bkRect;
    Rect  m_rewardTitleRect;
    Rect  m_rewardDesRect;
    Rect  m_rewardRect;
    CRewardDisplayUI* m_pRewardDisplayUI;
};


class CSpringGiftActivityUI : public Widget, public ButtonListener
{
public:
	CSpringGiftActivityUI();
	virtual ~CSpringGiftActivityUI();

	virtual void DrawAll(Sexy::ModalFlags* theFlags, Graphics* g);
    virtual void Draw(Graphics* i_g);
	virtual void Update();
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
    virtual void OnOK();
    
    void OnGet2015NewTearChargeReward(bool i_success, bool i_neednext);
#ifdef HOST_ANDROID
    static void GenerateReward(bool bAutoOpenPay,int iGetGem = 330);
#else
    static void GenerateReward(bool bAutoOpenPay);
#endif
	static SSpringRewardInfo GetSpringGiftReward();
private:

    void    GetGift();

//    class PlantAnimRig*           m_pAniRig;
    class Effect_PopAnim* m_pGetButtonAnimRig;
    int                           m_iGems;
  //  SexyString                    m_strPlantDes;
  //  SexyString                    m_strGemDes;
    SexyString                    m_strActivityDataDes;
    //class PlantDisplayBoard*      m_pPlantDisplayBoard;
 //   SexyTransform2D m_AniTrans;
    CRewardDisplayUI* m_pRewardDisplayUI;
    Rect  m_bksizeRect;
    int m_offsetX;
    int m_offsetY;
    Rect  m_rewardpools;
    class PVZ2UIButton* m_getButton;
  
};

#endif
