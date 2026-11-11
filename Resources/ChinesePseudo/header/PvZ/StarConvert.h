//
//  StarConvert.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/3/29.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef StarConvert_h
#define StarConvert_h

#include "PopingWidget.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "RealObject.h"
#include "Core.h"
#include "EffectAnim_UIAnim.h"
#include "Image.h"
#include "StarConvertConfig.h"
#include "PVZTypes.h"
#include "MapEventItem.h"
#include "GameFeatureType.h"

namespace Message
{
    void NotifyStarConverted(bool i_success);
    void NotifyStarConvertBoxClosed();
}

enum StarConvertType
{
    SCT_None = -1,
    SCT_Plant,
    SCT_Feature,
    SCT_Avatar,
};

class StarConvertBox : public PopingWidget, public ButtonListener
{
public:
    StarConvertBox();
    ~StarConvertBox();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    bool IsInited() { return m_inited; }
    void InitBox(ConvertObject i_convert, SexyString i_plantName, int i_level);
    
private:
    void InitView();
    
    void InitPlantView();
    void InitDescription();
    void InitShiningAnims();
    
private:
    bool m_inited;
    bool m_levelUp;
    
    int m_level;
    
    ConvertObject m_convert;
//    int m_bonusId;
    
    Rect m_titleRect;
    Rect m_descriptionRect;
    Rect m_plantViewRect;
    Rect m_levelRect;
    SexyString m_title;
    SexyString m_description;
    SexyString m_plantName;
    
    class PVZ2UIButton*     m_closeBtn;
    EffectAnim_UIAnim       m_openAnimRig;
    EffectAnim_UIAnim       m_backAnimRig;
    EffectAnim_UIAnim       m_popAnimRig;
    EffectAnim_UIAnim       m_popAnimLevelUp;
    
    Image* m_imageLevel = nullptr;
    Image* m_featureImg = nullptr;
};

class StarConvertObject : public Widget, public ButtonListener
{
public:
    StarConvertObject(ConvertObject i_convert);
    ~StarConvertObject();
    
    virtual void Update() override;
    virtual void Draw(Graphics* i_g) override;
    virtual void Resize(const Rect& theRect) override;
    virtual void ButtonDepress(int i_id) override;
    
    void OnStarConverted(bool i_success);
    void OnRefreshStarConvert();
//    void OnDraw(Graphics* i_g);
    void InitView();
    
    const ConvertObject&    GetConvertObject() const { return m_convert; }
    class PVZ2UIButton*     GetObtainBtn() { return m_obtainBtn; }
    
private:
    SexyString GetConvertObjectName();
    void CheckEnableObtain();
    
private:
    bool m_obtained;
    int m_plantStarLevel;
    int m_starReq;
    int m_btnId;
    
    ConvertObject m_convert;
    StarConvertType m_type = SCT_None;
    class PVZ2UIButton* m_obtainBtn;
    
    SexyString m_plantName;
    SexyString m_starReqString;
    Sexy::Rect m_plantBoxRect;
    Sexy::Rect m_plantNameRect;
    Sexy::Rect m_plantViewRect;
    Sexy::Rect m_levelRect;    
    Sexy::Rect m_starHintBGRect;
    Sexy::Rect m_starHintRect;
    EffectAnim_UIAnim   m_popAnimRig;
    
    Image* m_featureImg = nullptr;
    Image* m_imageLevel = nullptr;
    
    GameFeatureTypePtr m_featureTypePtr;
    PlantTypePtr m_plantTypePtr;
};

class StarConvertScrollPanel : public Widget
{
public:
    StarConvertScrollPanel(Rect &i_rect);
    virtual ~StarConvertScrollPanel();
    virtual void Draw(Graphics* i_g) override;
    
    void InitView();
    class StarConvertObject* GetObjectByName(const std::string& i_name);
    
private:
    Sexy::Rect m_rect;
    std::vector<Sexy::Rect> m_planelRects;
    std::vector<class StarConvertObject*> m_ObjectList;
};

class StarConvert : public PopingWidget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    StarConvert();
    ~StarConvert();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    bool IsConvertBoxValid() { return m_convertBox != NULL; }
    void ShowConvertBox(ConvertObject i_convert, SexyString i_plantName, int i_level = 0);
    void KillConvertBox();
    class StarConvertBox* GetConvertBox() const { return m_convertBox; }
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    // implement of Sexy::ScrollWidgetListener
    virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) override {}
    virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) override {}
    
    void OnComposePlant(bool i_success);
    void SetActivedObject(StarConvertObject* i_object);
    
private:
    void InitView();
    void InitTutorial();
    void CheckShowTutorial();
    void FinishTutorial();
    void OnNotifyStarConverted(bool i_success);
    void OnNotifyStarConvertBoxClosed();
    void onNarrationFinished();
    void ShowInfoUI();
    
private:
    Rect m_titleRect;
    Rect m_starRect;
    Rect m_starStringRect;
    Rect m_scollRect;
    
    class StarConvertObject* m_activeObject;
    class StarConvertBox* m_convertBox;
    
    SexyString m_title;
    SexyString m_starString;
    class PVZ2UIButton* m_closeBtn;
    class PVZ2UIButton* m_infoBtn;
    class PVZ2UIScrollingWidget * m_starConvertScollPanel;
    StarConvertScrollPanel* m_starConvertScollPanelWidget;
    
    MapTutorialState    m_tutorialState = TUTORIAL_NONE;
    std::string         m_tutorialItem;
};

#endif /* StarConvert_h */
