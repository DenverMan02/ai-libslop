/*
 * UINewerPresent.h
 *
 *  Created on: 2019-5-5
 *      Author: Administrator
 */

#ifndef UINEWERPRESENT_H_
#define UINEWERPRESENT_H_

#include "UISingletonDialog.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "NetworkData.h"
#include "PVZ2UIButton.h"
#include "ButtonListener.h"

class NewerPresentText : public Widget
{
public:
	NewerPresentText();
	NewerPresentText(const SexyString & xstr);
	~NewerPresentText();

	void SetTypeface(Sexy::PrimeTypeface* t);
	void SetTypeface(PrimeText_PotentialTypeface* t);
	void SetTextColorPreDefined(Sexy::Color::PredefinedColor c);
	void SetTextColor(const Sexy::Color& color);
	void SetHAlignment(EA::Text::HAlignment ha);
	//void SetVAlignment(EA::Text::VAlignment va);


	virtual void Draw(Graphics* g);
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
private:
	SexyString m_str;
	Sexy::PrimeTypeface*    m_pTypeface;
	EA::Text::HAlignment    m_HAlignment;
	//EA::Text::VAlignment    m_VAlignment;
	Sexy::Color m_textColor;
};

class NewerPresentImage : public Widget
{
public:
	NewerPresentImage();
	NewerPresentImage(const std::string & str_id);
	virtual ~NewerPresentImage();

	virtual void Draw(Graphics* g);
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	virtual void Update();
	virtual void UpdateF(float theFrac);

	int Width();
	int Height();
	int GetWidth();
	int GetHeight();
	void SetScale(float x,float y);

	void SetDisabled(bool disabled);
	bool GetDisabled();

	void SetPurchased(bool i_purchased) { m_purchased = i_purchased; }

protected:
	void internalDraw(Sexy::Graphics* i_g);

protected:
	ImagePtr m_pImage;

private:
	Sexy::Transform m_tranForm;
	bool    m_bTrans;
	bool    m_bDisabled = false;
	bool m_purchased = false;
};

class NewerPresentButton : public PVZ2UIButton
{
public:
	NewerPresentButton(int i_id,const std::string & normalImgPath,const std::string & downImgPath, Sexy::ButtonListener* i_listener);
	~NewerPresentButton();

	void SetImageType(PVZ2UIImageType imageType);
	void SetPlantName(const std::string & i_plantName) { m_plantName = i_plantName; }
	void SetPurchased(bool i_purchased) { m_purchased = i_purchased; }
private:
	std::string m_plantName;
	bool m_purchased = false;
};

class UINewerPresentDetail : public UISingletonDialog<UINewerPresentDetail>
{
public:
	UINewerPresentDetail();
	virtual ~UINewerPresentDetail();

	virtual bool    OnCreate() override;
	virtual std::string GetLayoutName() override { return "UINewerPresentDetail"; }
	virtual void	ButtonPress(int i_id) override;
	virtual void	ButtonDepress(int i_id) override;
	void			InitView(const std::string & i_plantName, int i_index);
private:
	void 			Close();
	void 			DlgChildWidgetSetIgnoreMouseInput(UI::Dialog* i_dlg, const std::string & i_keyChild, const std::vector<std::string>& i_childs);
	class PlantDisplayFrame* m_board;
	std::string m_plantName;
	Rect m_minimapRect;
	int m_index;
};

class UINewerPresentScrollPanel : public UISingletonDialog<UINewerPresentScrollPanel>
{
public:
	UINewerPresentScrollPanel();
	virtual ~UINewerPresentScrollPanel();
	void UpdateUI(PVZ2UIScrollingWidget* i_scrollWidget);

	virtual std::string GetLayoutName() override { return "UINewerPresentScrollPanel"; }
	virtual void	ButtonPress(int i_id) override;
	virtual void	ButtonDepress(int i_id) override;
private:
	NewerPresentButton* AddButton(Widget* i_parent, int i_id, const std::string & normalImgPath, const std::string & downImgPath,
			int x, int y, int width, int height, Sexy::ButtonListener* i_listener);
	NewerPresentImage* AddImage(Widget* i_parent, const std::string& i_res, int x, int y, int width, int height);
	NewerPresentImage* AddImage(Widget* i_parent, const std::string& i_res, int x, int y);
	NewerPresentText* AddText(Widget* i_parent, const SexyString& i_text, int x, int y, int width, int height);
};

class UINewerPresent : public UISingletonDialog<UINewerPresent>, public Sexy::ScrollWidgetListener
{
public:
	UINewerPresent();
	virtual ~UINewerPresent();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UINewerPresent"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	void UpdateUI();
private:
	class PVZ2UIScrollingWidget* m_defaultScollingWdget;
	class UINewerPresentScrollPanel* m_defaultPanel;
};

struct NetworkPresentContent
{
    int         m_count;
    int			m_objectId;

    NetworkPresentContent()
    {
        m_count = 0;
        m_objectId = 0;
    }
};

class NetworkNewerPresent : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(NetworkNewerPresent, Sexy::RtObject, Sexy::RtClass);

public:
	std::vector<std::vector<NetworkPresentContent>> m_contents;
	std::vector<int> m_purchasedPresent;
	std::vector<int> m_orgPrices;
};

struct PresentDetail
{
	PresentDetail()
	{
		m_plantName = "";
		m_purchased = false;
		m_orgPrice = 0;
		m_plantLevel = 0;
	}

	std::string m_plantName;
	std::vector<NetworkPresentContent> m_contents;
	bool m_purchased;
	int m_orgPrice;
	int m_plantLevel;
};

class New_S2C_BuyNewerPresent : public INetworkData
{
public:
    RT_CLASS_DEFINE(New_S2C_BuyNewerPresent, INetworkData, RtClass);

    std::vector<NetworkPresentContent>   m_rewards;
};

class NewerPresentMgr : public LazySingleton <NewerPresentMgr>
{
public:
	NewerPresentMgr();
    ~NewerPresentMgr();

    void SyncActivityData(const NetworkNewerPresent& i_data);
    void ShowNewerPresentDetail(int i_index);
    PresentDetail FindTargetPresent(int i_index);
    int GetNumPresents();
    bool Load();
    void Init();
    bool CheckTargetUnlocked(int i_index);
    int GetTargetPrice(int i_index);
    int GetTargetOrgPrice(int i_index);
    int GetTargetPlantLevel(int i_index);
    void BuyOffer(int i_index);
    void requestBuyOffer();
    std::string GetTargetSku(int i_index);
    SexyString GetTargetShortDes(int i_index);
    bool IsActive();
    void RequestNetwork();
    void Close();
    void NotifyBundlePurchased(const std::vector<PaymentBundleInfo>& i_infos);

private:
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    std::map<int, PresentDetail> m_cotentList;
    int m_currentPurchasedIndex;
    bool m_requested;
};


#endif /* UINEWERPRESENT_H_ */
