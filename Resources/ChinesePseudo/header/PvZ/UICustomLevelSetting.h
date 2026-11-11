#ifndef __UI_CUSTOM_LEVEL_SETTING_H__
#define __UI_CUSTOM_LEVEL_SETTING_H__

#include "UISingletonDialog.h"
#include "UIListener.h"
#include "Singleton.h"
#include "CheckboxListener.h"

class UICustomLevelSubSetting : public UISingletonDialog<UICustomLevelSubSetting>, public UI::RadioListener
{
public:
    UICustomLevelSubSetting();
    ~UICustomLevelSubSetting();

    virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UICustomLevelSubSetting"; }
	virtual void ButtonDepress(int i_id) override;
    virtual void RadioSelectionChanged(class UIWidgetRadio* pRadioBtn) override;

    void InitView(int i_subIndex);
private:
    void Certification();

    int m_subIndex;
};

class UICustomLevelMobileLink : public UISingletonDialog<UICustomLevelMobileLink>, public Sexy::CheckboxListener, public Sexy::EditListener
{
    enum LinkState
    {
        LinkState_Begin,
        LinkState_SendCode,
        LinkState_SendCodeFinish,
        LinkState_Linked,
    };
public:
     UICustomLevelMobileLink();
    ~UICustomLevelMobileLink();

    virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UICustomLevelMobileLink"; }
	virtual void ButtonDepress(int i_id) override;
	virtual void CheckboxChecked(int theId, bool checked) override;
    virtual bool AllowChar(int theId, SexyChar theChar) override;
    virtual void Update() override;

    void InitView();
    
    void LinkStart();
    void MarkRelink();

private:
    void SetState(LinkState i_state);
    bool CheckProtocol();
    bool CheckPhoneNumber();
    bool CheckCode();

    void SendCode();

    class EditWidget* m_moblieNumber;
    class EditWidget* m_codeNumber;
    class PVZ2UICheckBox* m_checkBox;
    LinkState m_codeState;
    float m_timeCounter;
};

class UICustomLevelSetting : public UISingletonDialog<UICustomLevelSetting>
{
public:
	UICustomLevelSetting();
	virtual ~UICustomLevelSetting();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UICustomLevelSetting"; }
	virtual void ButtonDepress(int i_id) override;

	void RefreshView();
private:
	
};

class CustomLevelSettingManager : public LazySingleton<CustomLevelSettingManager>
{
public:
    CustomLevelSettingManager();
    ~CustomLevelSettingManager();

    void SynizeData();

    void SetLinkPhoneNumber(const std::string& i_number) { m_phoneNumber = i_number; }
    const std::string& GetLinkPhoneNumber() { return m_phoneNumber; }
    bool GetLinkState() { return !m_phoneNumber.empty(); }
    void SetRelinkTimeStamp(int i_timeStamp) { m_relinkTimeStamp = i_timeStamp; }
    int GetRelinkDays();

    void SetCertificationState(int i_state) { m_certificationState = i_state; }
    int GetCertificationState() { return m_certificationState; }

    bool NeedShowAds() {return m_showAds; }
    bool NeedShowPlatform() {return m_showPlatform; }

private:
    std::string m_phoneNumber;
    int m_relinkTimeStamp;
    int m_certificationState;
    bool m_showAds;
    bool m_showPlatform;
public:
    std::string m_platformUrl;
};

#define gCustomLevelSettingMgr CustomLevelSettingManager::GetInstancePtr()


class UILevelEditorEncourageSetting : public UISingletonDialog<UILevelEditorEncourageSetting>, public Sexy::CheckboxListener
{
public:
    virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UILevelEditorEncourageSetting"; }
	virtual void ButtonDepress(int i_id) override;
	virtual void CheckboxChecked(int theId, bool checked) override;

    void InitView();
    void DisableSunmoneySetting();

private:
    bool m_buySunmoneyState;
    bool m_buyPlantfoodState;
    bool m_buyMowerState;
};


#endif