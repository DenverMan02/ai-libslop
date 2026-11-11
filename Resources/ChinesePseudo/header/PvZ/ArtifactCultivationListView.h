
#ifndef ArtifactCultivationListView_h
#define ArtifactCultivationListView_h

#include "UISingletonDialog.h"
#include "UIListener.h"
#include "UIScrollWidget.h"
#include "Artifact.h"
#include "Image.h"
#include "UIUtil.h"
#include "NetworkData.h"
#include "ArtifactMgr.h"

class ArtifactSkillButtonUI : public TouchWidget
{
public:
    ArtifactSkillButtonUI();
    virtual ~ArtifactSkillButtonUI();

    virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void UpdateTouchInfo() override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    
    void SetContent(int i_artifactId, int i_skillLevel);
	void SetIsUnlocked(bool i_unlocked);

	void ShowArtifactLevel(int i_level);
	void DisableShowArtifactLevel();

private:
	Sexy::Image* m_image;
	bool m_unlocked;
	bool m_showLevel;
	int m_artifactId;
	int m_skillLevel;
	int m_cacheRank;
	int m_cacheLevel;
	int m_cacheArtifact;
	SexyString m_levelStr;
};


class ArtifactSkillPreview : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener
{
public:
	ArtifactSkillPreview();
	virtual ~ArtifactSkillPreview();
	
	virtual void Draw(Sexy::Graphics* i_g) override; 
	virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

	void InitView(int i_artifactId);
	void SetArtifactCultivationWidget(class ArtifactCultivationWidget* i_widget);

private:
	class PVZ2UIButton* m_pButtonClose;
	class ArtifactCultivationWidget* m_artifactCultivationWidget;
};

class ArtifactCultivationWidget : public Sexy::Widget, Sexy::ButtonListener
{
public:
	ArtifactCultivationWidget();
	~ArtifactCultivationWidget();

	virtual void Update() override;
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
	virtual void DrawOverlay(Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;

	void InitView(int i_artifactId);
	void RefreshInfo();
	void OnArtifactLevelUp(bool i_success, int i_artifactId);
	void OnArtifactRankUp(bool i_success, int i_artifactId);
	void RequestLevelUp(class UIMessageBox* box, int buttonID);
	void RequestRankUp(class UIMessageBox* box, int buttonID);

	void ShowArtifactSkillPreview(int i_artifactId);
	void CloseArtifactSkillPreview();

private:
	int m_artifactId;
	int m_level;
	int m_rank;
	bool m_isLevelUp;
	bool m_isRankUp;
	SexyString m_rankUpSkillStr;
	bool m_matEnough;
	SexyString m_matConsumeStr;
	bool m_coinEnough;
	SexyString m_coinConsumeStr;
	class UIWidgetAnim* m_artifactAnim;
	class PVZ2UIButton* m_pButtonClose;	
	class PVZ2UIButton* m_pButtonCultivation;
	class PVZ2UIButton* m_pButtonArtifactSkillPreview;
	class ArtifactSkillPreview* m_artifactSkillPreview;
	std::vector<ArtifactSkillButtonUI*> m_skillButtonList;
};

class ArtifactBlessWidget : public Sexy::Widget, Sexy::ButtonListener
{
public:
	ArtifactBlessWidget();
	~ArtifactBlessWidget();

	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;

	void InitView(int i_artifactId);
	void Refresh();

	void showDescriptionWidget();
	void closeDescriptionWidget();

private:
	void SaveBoost(bool i_saveOld);
	void Bless(bool i_useNormal);
	bool CheckBless(bool i_useNormal);
	void refreshOthers();
	void onButtonDepressed();
	bool CheckLeftIsBetter(bool i_reverse);

	void SaveOldBoost(class UIMessageBox* box, int buttonID);
	void SaveNewBoost(class UIMessageBox* box, int buttonID);
	void BlessNormalBoost(class UIMessageBox* box, int buttonID);
	void BlessAdvanceBoost(class UIMessageBox* box, int buttonID);
	void BuyMaterial(class UIMessageBox* box, int buttonID);


private:
	int m_artifactId;
	class UIWidgetAnim* m_artifactAnim = nullptr;
	class PVZ2UIButton* m_pButtonClose = nullptr;
	class PVZ2UIButton* m_pButtonSaveLeft = nullptr;
	class PVZ2UIButton* m_pButtonSaveRight = nullptr;
	class PVZ2UIButton* m_pButtonBlessNormal = nullptr;
	class PVZ2UIButton* m_pButtonBlessAdvanced = nullptr;
	class PVZ2UIButton* m_pButtonLockFirst = nullptr;
	class PVZ2UIButton* m_pButtonLockSecond = nullptr;
	class UIWidgetImage* m_legendTipImage = nullptr;
	class UIWidgetText* m_legendTipStr = nullptr;
	class UIWidgetText* m_normalBlessTicketCount = nullptr;
	class UIWidgetText* m_advancedBlessTicketCount = nullptr;
	class ActivityDescriptionUI* m_descriptionUI = nullptr;
	bool m_lockFirst = false;
	bool m_lockSecond = false;
	SexyString m_currentBoost[2];
	SexyString m_refreshBoost[2];
};

class UIArtifactBoostDetails : public UISingletonDialog<UIArtifactBoostDetails>, public Sexy::ScrollWidgetListener
{
public:
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UIArtifactBoostDetails"; }
	virtual void							ButtonDepress(int i_id) override;
    virtual void							ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void							ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void InitView(int i_artifactId);
};

class UIArtifactBoostPreview : public UISingletonDialog<UIArtifactBoostPreview>, public Sexy::ScrollWidgetListener
{
public:
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UIArtifactBoostPreview"; }
	virtual void							ButtonDepress(int i_id) override;
    virtual void							ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void							ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void InitView(int i_artifactId);
};

class ArtifactCultivationListView : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener
{
public:
	ArtifactCultivationListView();
	virtual ~ArtifactCultivationListView();
	
	virtual void Update() override;
	virtual void Draw(Sexy::Graphics* i_g) override; 
	virtual void DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void DrawOverlay(Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();
	void OnSelectArtifact(int i_artifactId);
	void UpdateSkillButtons();
	void UpdateArtifactButton();
	void TriggerTutorial();
	void onNarrationFinished();

	void OnEquipArtifact(int i_artifactId);
	void OnUnEquipArtifact(int i_artifactId);

	void ShowCultivationWidget(int i_artifactId);
	void CloseCultivationWidget();

	void ShowBlessWidget(int i_artifactId);
	void CloseBlessWidget();

private:
	int m_currentArtifact;
	SexyString m_currentArtifactString;
	class UIWidgetAnim* m_artifactAnim;
    class PVZ2UIButton* m_pButtonClose;
	class PVZ2UIButton* m_pButtonEquip;
	class PVZ2UIButton* m_pButtonArtifact;
	class PVZ2UIButton* m_pButtonBoostPreview;
	class ArtifactDisplayBoard* m_artifactDisplay;
	class ArtifactCultivationWidget* m_cultivationWidget;
	class ArtifactBlessWidget* m_blessWidget;
	std::vector<ArtifactSkillButtonUI*> m_skillButtonList;

	bool m_isMaxLevel;
	Sexy::Image* m_firstBlessIcon = nullptr;
	Sexy::Image* m_secondBlessIcon = nullptr;
	SexyString m_firstBlessDescription;
	SexyString m_secondBlessDescription;
};

class ArtifactCultivationItem : public Sexy::Widget
{
public:
    ArtifactCultivationItem();
	virtual ~ArtifactCultivationItem();
	
	virtual void Update() override;
	virtual void Draw(Sexy::Graphics* i_g) override;
	
    virtual void TouchBegan(const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch ) override;

	void InitView(ArtifactPropertiesPtr i_property);
	void RefreshData();
	void OnSelectArtifact(int i_artifactId);
	void OnEquipArtifact(int i_artifactId);
	void OnUnEquipArtifact(int i_artifactId);
	void OnArtifactLevelUp(bool i_success, int i_artifactId);
	void OnArtifactRankUp(bool i_success, int i_artifactId);

private:
    int m_touchId;
	bool m_selected;
	bool m_equiped;
	bool m_unlocked;
	int m_rank;
	int m_level;
	Sexy::Image* m_image;
	ArtifactPropertiesPtr m_property;
};


class ArtifactCultivationConsumeData : public INetworkData
{
public:
	RT_CLASS_DEFINE(ArtifactCultivationConsumeData, INetworkData, RtClass);

	int ArtifactId;
	int Level;
	int Rank;
	std::vector<S2C_BonusInfo> MaterialCost;
};

namespace Message
{
	void SelectArtifact(int i_artifactId);
	void ArtifactLevelUp(bool i_success, int i_artifactId);
	void ArtifactRankUp(bool i_success, int i_artifactId);
	void EquipArtifact(int i_artifactId);
	void UnEquipArtifact(int i_artifactId);
}

#endif
