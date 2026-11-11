//
//  HintUI.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/9/7.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef HintUI_h
#define HintUI_h

#include "RtDelegate.h"
#include "PVZ2UIButton.h"
#include "PopingWidget.h"
#include "EffectAnim_UIAnim.h"
#include "PrimeText_Game.h"
#include "EffectAnim_UIAnim.h"

enum ButtonColor
{
    BC_Green,
    BC_Yellow,
    BC_Purple
};

struct HintBonusInfo
{
    int bonusId = 0;
    int quantity = 0;
    
    HintBonusInfo(int b, int q)
    {
        bonusId = b;
        quantity = q;
    }
};

struct HintImage
{
    ImagePtr image = nullptr;
    Rect hintRect = {0, 0, 0, 0};
};

struct HintWord
{
    SexyString word = _S("");
    Rect hintRect = {0, 0, 0, 0};
    PrimeTypeface* font = FONT_CONFIRM_DESCRIPTION;
    Color color = Color::White;
    DrawStringJustification layout = DS_ALIGN_CENTER_VERTICAL_MIDDLE;
};

struct HintAnim
{
    std::string loop = "";
    EffectAnim_UIAnim *animP;
};

class HintUI : public PopingWidget, public ButtonListener
{
public:
    HintUI();
    ~HintUI();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void ShowHintUI();
    void KillHintUI();
    
    void Default1Init();
    void Default2Init();
    
    void BonusInit();
    
    void DefaultUnconnectInit();
    
    void SetButtonString(const SexyString& i_button);
    void SetButton2String(const SexyString& i_button);
    
    void SetCloseButtonVisible(bool i_visible);
    
    void SetTitleString(const SexyString& i_title);
    void SetContentString(const SexyString& i_content);
    
    void SetButtonPressedEvent(Delegate0 i_onPressed);
    void SetButton2PressedEvent(Delegate0 i_onPressed);
    void SetClosePressedEvent(Delegate0 i_onPressed);
    
    void SetButtonColor(ButtonColor i_color);
    void SetButton2Color(ButtonColor i_color);
        
    void SetTitleImage(ImagePtr i_titleImg);
    void SetMainBGImage(ImagePtr i_bgImage);
    
    void SetNeedLight(bool i_light);
    Rect GetContentRect() { return m_contentRect; }
    
    void AddWordInRect(SexyString i_word, Rect i_rect, PrimeTypeface* font = FONT_CONFIRM_DESCRIPTION, Color color = Color::White, DrawStringJustification layout = DS_ALIGN_CENTER_VERTICAL_MIDDLE);
    void AddImageInRect(ImagePtr i_img, Rect i_rect);
    void AddAnimInRect(std::string anim, Rect i_rect, std::string loop = "", float i_scale = 1.0f, bool middleCenter = true, bool i_plant = true);
    void SetBonus(int i_bonusId, int i_quantity);
    
    Delegate0 KillMySelf();
    
private:
    void DefaultInit();
    void InitView();
    void Refresh();
    void InitButton(PVZ2UIButton* i_btn, ButtonColor i_color);
    void InitShiningAnims();
    
private:
    std::vector<HintImage> m_imgList;
    std::vector<HintWord> m_wordList;
    std::vector<HintAnim> m_animShownList;
    
    std::vector<HintBonusInfo> m_bonusList;
    
    bool m_inited = false;
    bool m_showCloseBtn = false;
    bool m_twoButton = false;
    bool m_needLight = false;
    bool m_isBonus = false;
    
    int m_hintUIIndex = 0;
    
    int m_buttonLeftId = 0;
    int m_buttonRightId = 0;
    int m_buttonCloseId = 0;
    
    Rect m_titleImgRect;
    Rect m_titleRect;
    Rect m_contentRect;
    Rect m_buttonLeftRect;
    Rect m_buttonRightRect;
    Rect m_buttonCloseRect;
    
    SexyString m_title          = _S("");
    SexyString m_mainContent    = _S("");
    SexyString m_buttonLeft     = _S("");
    SexyString m_buttonRight    = _S("");
    
    PVZ2UIButton* m_left        = nullptr;
    PVZ2UIButton* m_right       = nullptr;
    PVZ2UIButton* m_close       = nullptr;
    
    Delegate0 m_leftEvent;
    Delegate0 m_rightEvent;
    Delegate0 m_closeEvent;
    
    ButtonColor m_leftColor;
    ButtonColor m_rightColor;
    
    ImagePtr m_titleImage       = nullptr;
    ImagePtr m_bgImage          = nullptr;
    
    EffectAnim_UIAnim       m_openAnimRig;
    EffectAnim_UIAnim       m_backAnimRig;
};

#endif /* HintUI_h */
