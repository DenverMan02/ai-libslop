//
//  ChristmasAccessory.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/12/1.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef ChristmasAccessory_H
#define ChristmasAccessory_H

//#include "Widget.h"
//#include "GameButton.h"
//#include "Core.h"
//#include "PropertySheetBase.h"
//#include "PVZTypes.h"
//#include "PlayerInfo.h"

#include "Core.h"
#include "Widget.h"
#include "PVZTypes.h"
#include "PlayerInfo.h"
#include "ActiveCenterTab.h"

class AccessoryContentUI : public Sexy::Widget, public ButtonListener
{
public:
    AccessoryContentUI(Rect i_rect, ACUI_Type i_type);
    ~AccessoryContentUI();
    
    virtual void Update() override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonPress(int i_id) override;
    virtual void ButtonDepress(int i_id) override;
    
    void SetConnected(bool i_connected) { m_unconnected = !i_connected; }
    void SetActiveClosed(bool i_closed) { m_closed = i_closed; }
    void RefreshContent();
    
    void ShowHintBox(int i_index);
    void HideHintBox(int i_index);
    
private:
    void InitView();
    
private:
    int m_accessory1Id;
    int m_accessory2Id;
    
    int m_coinPrice;
    int m_gemPrice;
    
    bool m_hintBox1Visible;
    bool m_hintBox2Visible;
    
    bool m_unconnected;
    bool m_closed;
    
    ACUI_Type m_type;
    
    Sexy::Rect m_Rect;
    Sexy::Rect m_boxRect;
    Sexy::Rect m_arrowRect;
    Sexy::Rect m_contentBgRect;
    Sexy::Rect m_accessory1Rect;
    Sexy::Rect m_accessory2Rect;
    
    Sexy::Rect m_hintBox1Rect;
    Sexy::Rect m_hintBox2Rect;
    
    ImagePtr m_boxImage;
    ImagePtr m_accessory1Image;
    ImagePtr m_accessory2Image;
    
    std::string m_accessory1Name;
    std::string m_accessory2Name;
    
    SexyString m_hintbox1Des;
    SexyString m_hintbox2Des;
    
    class PVZ2UIButton* m_buyBtn;
    class PVZ2UIButton* m_accessory1Btn;
    class PVZ2UIButton* m_accessory2Btn;
    class UIWidgetImage* m_gemImage;
    class UIWidgetImage* m_coinImage;
};

class DailyAccessoryBonusWidget : public Widget
{
public:
    DailyAccessoryBonusWidget();
    ~DailyAccessoryBonusWidget();
    
    virtual void Resize(const Rect& theRect) override;
    virtual void Update() override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    
    bool IsSelected() { return m_selected; }
    void SetSelected(bool i_selected) { m_selected = i_selected; }
    void InitView();
    void ResetRewardImage();
    void RefreshContents();
    
private:
    bool m_selected = false;
    
    time_t m_endTime = 0;
    time_t m_lastRefreshTime = 0;
    
    Sexy::Rect m_Rect;
//    Sexy::Rect m_titleRect;
    Sexy::Rect m_contentRect;
    Sexy::Rect m_seperatorRect;
    Sexy::Rect m_timeLebelRect;
    Sexy::Rect m_refreshHintRect;
    Sexy::Rect m_daysRect;
    Sexy::Rect m_timeRect;
    
    SexyString m_daysDes;
    SexyString m_timeDes;
    SexyString m_refreshHintDes;
    class ActivityConfig* m_activityConfig = nullptr;
    
    AccessoryContentUI* m_freeContent = nullptr;
    AccessoryContentUI* m_coinContent = nullptr;
    AccessoryContentUI* m_gemContent = nullptr;
};

class DailyAccessoryBonusUI : public ActiveCenterTabBase//, public ButtonListener
{
public:
    DailyAccessoryBonusUI(int i_tab, class UI::Dialog* pCenterDlg);
    virtual ~DailyAccessoryBonusUI();
    
    virtual void SetSelect(bool setting) override;
//    virtual void DrawForeground(class Sexy::Graphics* i_g) override;
    virtual void Update() override;
//    virtual void ButtonDepress(int i_id) override;
    
    void SetPayType(ACUI_Type i_type);
    void SetPaying(bool i_paying);
    bool IsPaying();
    
    void AddBonus(int i_chipId, int i_chipsCount, int i_posIndex);
    void KillBonusUI();
    
    void OnGotChristmasAccessoryStat(bool i_success);
    void OnRefreshChristmasAccessoryStat(bool i_success);
    void OnChristmasAccessoryBought(bool i_success);
    
private:
    void InitView();
    
private:
    ACUI_Type m_payType = ACUI_None;
    bool m_paying = false;
    bool m_inited = false;
    bool m_opened = false;
    Sexy::Rect m_Rect;
    
    DailyAccessoryBonusWidget* m_background = nullptr;
    class PVZ2UIButton* m_closeBtn = nullptr;
};


#endif /* ChristmasAccessory_H */
