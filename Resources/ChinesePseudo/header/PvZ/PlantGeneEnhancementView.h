
#ifndef PlantGeneEnhancementView_H_
#define PlantGeneEnhancementView_H_

#include "PropertySheetBase.h"
#include "AdaptorHowToPlayScreen.h"
#include "HotUIAdaptor.h"
#include "ObjectTypeDescriptor.h"
#include "PlantGeneEnhancement.h"
#include "UISingletonDialog.h"
#include "NetworkData.h"
#include "PVZ2UIButton.h"
#include "Image.h"

struct GeneSequenceShopItem
{
	int Index;
	int ItemID;
	int ItemNumber;
	int CurrencyID;
	int CurrencyNumber;
	int Limit;
	int Hiden;
	int Rank = 0;
};

class PlantGeneEnhancementConfig : public INetworkData
{
public:
	RT_CLASS_DEFINE(PlantGeneEnhancementConfig, INetworkData, RtClass);

	std::vector<GeneSequenceShopItem> ShopList;
	int ToturialFactor = 0;
	int GeneFactor;
	int UniversalGene;
	int Open = 1;
	int hasDraw = 0;
	std::vector<int> GeneRankList;
};


class PlantGeneEnhancementData : public INetworkData
{
public:
	RT_CLASS_DEFINE(PlantGeneEnhancementData, INetworkData, RtClass);

    int MaterialNumber;
	std::vector<int> GeneSequences;
    std::vector<S2C_BonusInfo> RewardList;
};

//how to play
class AdaptorPlantGeneHowToPlayScreen : public HowToPlayScreen
{
    RT_CLASS_DEFINE(AdaptorPlantGeneHowToPlayScreen, HowToPlayScreen, RtClass);

public:
    void ButtonDepress(int i_buttonID) override;

protected:
    void onLoadUIView() override;
    void onLayoutFinished() override;
    void doClose();
};

//入口主界面
class PlantGeneEnhancementView : public Sexy::Widget, public Sexy::ButtonListener
{
	enum GeneToturial : int
	{
		GeneToturial_Step_None = 0,
		GeneToturial_Step_One,
		GeneToturial_Step_Two,
		GeneToturial_Step_Three,
		GeneToturial_Step_Four,
		GeneToturial_Step_Five,
		GeneToturial_Step_End,
	};

public:
	PlantGeneEnhancementView();
	virtual ~PlantGeneEnhancementView();
	
	virtual void Update() override;
	virtual void Draw(Sexy::Graphics* i_g) override; 
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;

    void InitView();
	void RefreshProgress();
	void CheckTips();
	void OnBuyGeneFactor(int i_index);


	void ShowPlantGeneDisplayView(int i_type);
	void ClosePlantGeneDisplayView();
	class PlantGeneDisplayView* GetPlantGeneDisplayView();
	void ShowPlantGeneBonus(const std::vector<int>& i_sequence, const std::vector<S2C_BonusInfo>& i_bonusInfo);
	void ClosePlantGeneBonus();
	void ShowGeneFactorShop();
	void CloseGeneFactorShop();
	void ShowGeneEnhancementInfo();
	void CloseGeneEnhancementInfo();
	void ShowIfGeneNewAdditionInfo();
	void CloseGeneNewAdditionInfo();

	void RequestConfig();
	void RequestDraw(int i_type);

	bool IsOnToturial();
	void StartToturial();
	void EndToturial();
	void onQueuedNarrationFinished();

	GeneToturial m_toturialStep;

private:
	void DrawTips(Sexy::Graphics* i_g, bool i_flag, const Sexy::Point& i_position);
	void DrawProgress(Sexy::Graphics* i_g, const std::pair<int,int>& i_value, const Sexy::Point& i_position);
	PVZ2UIButton* CreateGeneEnhancementEntry(int i_btnId, const Sexy::Point& i_position);
	void ConfirmClose(class UIMessageBox* box, int buttonID);

	bool m_tipsInfo[5];
	std::pair<int,int> m_progressValue[5];
	int m_geneFactorNumber;
	int m_geneUniversalNumber;
	class PlantGeneBonus* m_plantGeneBonus;
	class PlantGeneDisplayView* m_geneDisplayView;
	class PlantGeneFactorShop* m_geneFactorShop;
	class ActivityDescriptionUI* m_descriptionUI;
	class PlantGeneNewAdditionWidget* m_geneNewAddition;

	bool m_hasDraw;
	PVZ2UIButton* m_pButtonStore;
	PVZ2UIButton* m_pButtonBlueSequence;
public:
	std::vector<int> m_geneRankList;
};

class UIPlantGeneToturial : public UISingletonDialog<UIPlantGeneToturial>
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIPlantGeneToturial"; }
};

class UIPlantGeneSelectDrawMode : public UISingletonDialog<UIPlantGeneSelectDrawMode>
{
public:
    UIPlantGeneSelectDrawMode();
    virtual ~UIPlantGeneSelectDrawMode();
    
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIPlantGeneSelectDrawMode"; }
    void ButtonDepress(int i_id) override;

	void ConfirmDrawOne(class UIMessageBox* box, int buttonID);
	void ConfirmDrawTen(class UIMessageBox* box, int buttonID);

	void StartToturial();

};

class PlantGeneBonusItem : public Sexy::Widget
{
public:
	PlantGeneBonusItem();
	~PlantGeneBonusItem();

	virtual void Draw(Sexy::Graphics* i_g) override; 

	void InitView(int i_gene, S2C_BonusInfo i_bonus);
	void SetFirstBonus();
	void ChangeBonus();
private:
	bool m_firstBonus;
	class UIRewardFrameSelect* m_before;
	class UIRewardFrameSelect* m_after;
};

class PlantGeneBonus : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	enum PlantGeneBonusState : int
	{
		PlantGeneBonusState_Invild,
		PlantGeneBonusState_Init,
		PlantGeneBonusState_NewGene,
		PlantGeneBonusState_Moving,
		PlantGeneBonusState_CHECK,
		PlantGeneBonusState_Ending,
	};

public:
	PlantGeneBonus();
	virtual ~PlantGeneBonus();
	virtual void ButtonDepress(int i_id) override;
	virtual void Update() override;
	virtual void Draw(Sexy::Graphics* i_g) override; 
	virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;

    void InitView(std::vector<int> i_sequence, std::vector<S2C_BonusInfo> i_bonusInfo);
private:
	void SetState(PlantGeneBonusState i_state);
	void ShowPanel(PlantGenePtr i_genePtr, int i_special);
	void ShowEnd();

	bool m_isSingleDraw;
	int m_state;
	int m_currentRewardIndex;
	std::vector<int> m_geneSequence;
	std::vector<S2C_BonusInfo> m_bonusInfo;

	std::vector<Sexy::Point> m_targetPosition;
	std::vector<PlantGeneBonusItem*> m_bonusItem;

	float m_rewardFlyingTime;
	float m_rewardFlyingEndTime;
	int m_rewardIconStartX;
	int m_rewardIconEndX;
	int m_rewardIconStartY;
	int m_rewardIconEndY;

	float m_timer;
	class UtilEasyDisplayWidget* m_panel;
	Widget* m_endPanel;
	class Effect_PopAnim* m_animEffect;
};


class PlantGeneItem : public Sexy::Widget
{
public:
	PlantGeneItem();
	~PlantGeneItem();

	virtual void Draw(Sexy::Graphics* i_g) override; 
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
	void InitView(PlantGenePtr i_genePtr, int i_rareType);
	void OnGeneLevelUpSuccess(int i_geneId, int i_level);

	int GetGeneID();
	
private:
	int32 m_touchId;
	Sexy::Image* m_frame = nullptr;
	Sexy::Image* m_image = nullptr;
	Sexy::Image* m_sub = nullptr;
	Sexy::Image* m_rank = nullptr;
	int m_currentLevel;
	bool m_showTips;
	PlantGenePtr m_plantGenePtr;
};

class PlantGeneDisplayView : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	PlantGeneDisplayView();
	virtual ~PlantGeneDisplayView();
	
	virtual void Update() override;
	virtual void Draw(Sexy::Graphics* i_g) override; 
	virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView(int i_type);
	void RefreshProgress();
	void StartToturial();
	PVZ2UIButton* GetCloseButton();

private:
	Sexy::Image* m_background;
	Sexy::Image* m_title;
	SexyString m_titleStr;
	PVZ2UIButton* m_buttonClose;

	int m_geneFactorNumber;
	int m_geneUniversalNumber;

	std::vector<PlantGeneItem*> m_plantGeneItemList;
};


class UIPlantGeneLevelUpView : public UISingletonDialog<UIPlantGeneLevelUpView>
{
public:
    UIPlantGeneLevelUpView();
    virtual ~UIPlantGeneLevelUpView();
    
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIPlantGeneLevelUpView"; }
	virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    void ButtonDepress(int i_id) override;

	void LoadData(PlantGenePtr i_genePtr);
	void StartToturial();

private:
	void UpdateButtonState();
	void ConfirmBuy(class UIMessageBox* box, int buttonID);
	void ToturialFinish(class UIMessageBox* box, int buttonID);

	int32 m_touchId;
	PlantGenePtr m_plantGenePtr;
};
 
class PlantGeneFactorShopItem : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	PlantGeneFactorShopItem();
	~PlantGeneFactorShopItem();

	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;

	void InitView(int i_index); 
private:
	int m_index;
	SexyString m_title;
	SexyString m_description;

};

class PlantGeneFactorShop : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:	
	virtual void Draw(Sexy::Graphics* i_g) override; 
	virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

	void InitView();

};

class PlantGeneSequenceShopItem : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	virtual void Draw(Sexy::Graphics* i_g) override; 
    virtual void ButtonDepress(int i_id) override;

	void InitView(const GeneSequenceShopItem& i_shopItem);
	void ConfirmBuy(class UIMessageBox* box, int buttonID);

private:
	SexyString m_titleStr;
	Sexy::Image* m_rankImage;
	GeneSequenceShopItem m_item;
};

class UIPlantGeneSequenceShop : public UISingletonDialog<UIPlantGeneSequenceShop>, public Sexy::ScrollWidgetListener
{
public:
    UIPlantGeneSequenceShop();
    virtual ~UIPlantGeneSequenceShop();
    
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIPlantGeneSequenceShop"; }
	virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

	void InitView();
	void NotifyShopBuyFinishDetails(bool success, const class S2C_ShopItemPurchaseInfo* pData);
private:
	void CreatShopItem();

	PlantGeneEnhancementConfig m_geneConfig;
	class PVZ2UIScrollingWidget* m_whiteScroll;
	class PVZ2UIScrollingWidget* m_greenScroll;
	class PVZ2UIScrollingWidget* m_blueScroll;
	class PVZ2UIScrollingWidget* m_purpleScroll;
	class PVZ2UIScrollingWidget* m_orangeScroll;
};


class PlantGeneNewAdditionWidget : public Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

	void InitView();
};

namespace Message
{
	void RefreshGeneEnhancement();
	void GeneLevelUpSuccess(int i_geneId, int i_level);
}

#endif