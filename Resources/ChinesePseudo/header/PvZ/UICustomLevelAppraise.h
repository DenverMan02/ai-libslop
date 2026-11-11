#ifndef __UI_CUSTOM_LEVEL_APPRAISE__
#define __UI_CUSTOM_LEVEL_APPRAISE__

#include "UISingletonDialog.h"
#include "CustomLevelMgr.h"
#include <functional>

class CustomLevelTagWidget : public Widget
{
public:
    CustomLevelTagWidget();
    ~CustomLevelTagWidget();

    virtual void Draw(Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void SetData(int i_id);
    int GetData();
    bool IsSelected();

private:
    int m_touchId;
    bool m_state;
    int m_tagID;
    SexyString m_content;
};

class UICustomLevelAppraise : public UISingletonDialog<UICustomLevelAppraise>
{
public:
    enum AppraiseType
    {
        REPORT_LEVEL,
        AWARD_LEVEL,
        AWARD_LEVEL_FULL,
        SUPPORT_LEVEL,
        SUPPORT_REASON_LEVEL,
        NOT_SUPPORT_LEVEL,
    };
public:
    UICustomLevelAppraise();
    ~UICustomLevelAppraise();

    bool OnCreate() override;
    std::string GetLayoutName() override { return "UICustomLevelAppraise"; }
    virtual void ButtonDepress(int i_id) override;

    void Init(AppraiseType i_type);

    void ObtainAward();

    void SetAfterReport(std::function<void()> i_func){ m_afterReport = i_func; }

    void InitLevelAward(int i_num, int i_current, int i_max);

protected: 
    void ReportLevel();
    void SupportLevel();
    void SupportReasonLevel();
    void NotSupportLevel();

    void RefreshTags();
    void ShowMessageBox();
    void MessageBoxClose(class UIMessageBox* box, int buttonID);

    AppraiseType m_type;
    std::vector<CustomLevelTagWidget*> m_tagList;
    CustomNetworkExtraData m_cacheData;
    
    std::function<void()> m_afterReport;
};

#endif