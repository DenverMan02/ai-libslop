#ifndef UI_REPEAT_COMPONENT_H
#define UI_REPEAT_COMPONENT_H

#include "Image.h"
#include "Widget.h"
#include "ButtonListener.h"
#include "PVZ2UIButton.h"

//任务组件
class GeneralTask;
class TemplateTaskWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:

    TemplateTaskWidget();
    virtual ~TemplateTaskWidget();

    //Only for Cheat
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void InitTask(GeneralTask* i_task);

protected:
    virtual void DrawTaskBackground(Sexy::Graphics* i_g);
    virtual void DrawTaskDescription(Sexy::Graphics* i_g);
    virtual void DrawProgress(Sexy::Graphics* i_g);
    virtual void DrawRewards(Sexy::Graphics* i_g);
    virtual void UpdateButtonState();

    virtual void RequestReward();

    Sexy::Image* m_background;
    Sexy::Image* m_material;
    SexyString m_strName;
    Sexy::Rect m_rName;
    Sexy::Rect m_rReward;
    SexyString strProgress;
    Sexy::Rect m_rProgress;
    Sexy::Rect m_rBanner;
    Sexy::Rect m_rButton;
    PVZ2UIButton* m_btnButton;
    GeneralTask* m_pTask;
    int32 m_iTouch;
    int m_rewardNum;
};

//礼包组件
class TemplateBundleWidget : public Widget, public Sexy::ButtonListener
{
public:
    TemplateBundleWidget();
    TemplateBundleWidget(int i_index);
    virtual ~TemplateBundleWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void Init(int i_index);
    void SetLimit(int i_limit);
    void SetReward(int i_gem, int i_mat);

protected:
    virtual void DrawBundleBackground(Sexy::Graphics* i_g);
    virtual void DrawBundleTitle(Sexy::Graphics* i_g);
    virtual void DrawBundleCenter(Sexy::Graphics* i_g);
    virtual void DrawBundleRewards(Sexy::Graphics* i_g);
    virtual void DrawBundleLimit(Sexy::Graphics* i_g);

    virtual void UpdateButtonState();
    virtual void OnPurchaseButtonDepress();

    int m_index;
    int m_limit;
    int m_gemNum;
    int m_materialNum;

    Sexy::Image* m_background;
    Sexy::Image* m_title;
    Sexy::Image* m_center;
    Sexy::Image* m_material;
    class PVZ2UIButton* m_purchase;
protected:
    void DrawBundleTitleOffSet(Sexy::Graphics* i_g, int i_y);
    void DrawBundleCenterOffSet(Sexy::Graphics* i_g, int i_yoff, float i_scale);

};


#endif