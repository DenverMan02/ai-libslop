//
//  GachaItemDisplayer.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 16/8/30.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef GachaItemDisplayer_h
#define GachaItemDisplayer_h

#include "PVZ2UIButton.h"
#include "MagentoService.h"
#include "EASquared.h"

enum GachaItemButtonId
{
    GACHA_BTN_CLOSE = 100,
    GACHA_BTN_PREVIEW,
    GACHA_BTN_DRAW
};

class GachaItemDisplayer : public Sexy::Widget, public ButtonListener
{
public:
    static GachaItemDisplayer* Create(GachaType i_type,const Rect &i_rect);
    
    GachaItemDisplayer(GachaType i_type,const Rect &i_rect);
   
    virtual ~GachaItemDisplayer();
    
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    //PVZ2_CHINESE_END
    virtual void Draw(Sexy::Graphics* i_g);
    virtual void Resize(int i_x, int i_y, int i_width, int i_height);
    
    Sexy::Image* getGachaImage(GachaType i_type);
    
    virtual void ButtonDepress(int i_id);
    GachaType GetType() { return m_type; }
    PVZ2UIButton* m_buyButton;
    
private:    
    
    void OnNotifyTutorialResponse();

    //PVZ2UIButton* m_buyButton;
    Image* m_imgObtain;
    Image* m_backgroundImage;
    Image* m_imgBanner;
    Image* m_imgIsPlantlocked;
    Image* m_imgIcon;
    Image* m_imgTimingFree;
    
    SexyString m_headerLabel;
    SexyString m_descriptionLabel;
    int m_headerHeightScaled;    
    
    Sexy::Point m_iconPos;
    DrawStringJustification m_drawAlign;
    
    int         m_button_width;
    GachaType m_type;
    class PVZ2UIGameObjectCard* m_card;
};

class GachaDisplayerDialog : public Sexy::Widget, public ButtonListener
{
public:
    GachaDisplayerDialog(GachaType i_type);
    virtual ~GachaDisplayerDialog();

    void ShowMask();
    
    virtual void ButtonDepress(int i_id);
    virtual void Draw(Sexy::Graphics* i_g);

private:
    Rect m_dialogRect;
    Image* m_backgroundImage;
    SexyString m_headerLabel;
    class GachaItem* m_leftGachaItem;
    class GachaItem* m_rightGachaItem;
};

class GachaItem : public Sexy::Widget, public ButtonListener
{
public:
    static GachaItem* Create(GachaType i_type, bool isMutiDraw, MagentoProductPropsPtr i_props);
    
    GachaItem(GachaType i_type, bool isMutiDraw, MagentoProductPropsPtr i_props);
    
    virtual ~GachaItem();
    
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    //PVZ2_CHINESE_END
    virtual void Draw(Sexy::Graphics* i_g);
    virtual void Resize(int i_x, int i_y, int i_width, int i_height);
    
    Sexy::Image* getGachaImage(GachaType i_type, bool isMutiDraw);
    void UpdateViewForKeyMode(GachaType eType, bool bMulti);
    
    virtual void ButtonDepress(int i_id);

    void ShowMask();
    
private:
    void TryToDraw();
    void OnNotifyDrawFinish();

    void RefreshButton(SexyString label, Image* img);// this will for ads button and normal button change
    bool IsAdvertiseEnable();
    void onAdsFinish(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);\
    bool CheckAdvertisementCoolDown();
    void RefreshAdvertisementTime();
    void RefreshAdsButton();
    void OnNotifyTutorialResponseInner();
    void onADFinished(int i_type);

    PVZ2UIButton* m_buyButton;
    Image* m_imgObtain;
    Image* m_backgroundImage;
    Image* m_imgBanner;
    Image* m_imgIsPlantlocked;
    Image* m_imgIcon;
    Image* m_imgTimingFree;
    
    SexyString m_headerLabel;
    SexyString m_descriptionLabel;
    int m_headerHeightScaled;
    
    Sexy::Point m_iconPos;
    DrawStringJustification m_drawAlign;
    
    int         m_button_width;
    GachaType m_type;
    class PVZ2UIGameObjectCard* m_card;
    bool    m_isMutiDraw;
    MagentoProductPropsPtr m_props;
};


#endif /* GachaItemDisplayer_h */
