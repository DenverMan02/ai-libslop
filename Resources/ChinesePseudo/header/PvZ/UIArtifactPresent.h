/*
 * UIArtifactPresent.h
 *
 *  Created on: 2021-6-16
 *      Author: admin
 */

#ifndef UIARTIFACTPRESENT_H_
#define UIARTIFACTPRESENT_H_

#include "UISingletonDialog.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "NetworkData.h"
#include "PVZ2UIButton.h"
#include "ButtonListener.h"

namespace Message
{
	void ArtifactPresentClose();
}

class UIArtifactPresentScrollPanel : public UISingletonDialog<UIArtifactPresentScrollPanel>
{
public:
	UIArtifactPresentScrollPanel();
	virtual ~UIArtifactPresentScrollPanel();
	void UpdateUI(PVZ2UIScrollingWidget* i_scrollWidget);

	virtual std::string GetLayoutName() override { return "UIArtifactPresentScrollPanel"; }
	virtual void	ButtonPress(int i_id) override;
	virtual void	ButtonDepress(int i_id) override;
private:
	class NewerPresentButton* AddButton(Widget* i_parent, int i_id, const std::string & normalImgPath, const std::string & downImgPath,
			int x, int y, int width, int height, Sexy::ButtonListener* i_listener);
	class NewerPresentImage* AddImage(Widget* i_parent, const std::string& i_res, int x, int y, int width, int height);
	class NewerPresentImage* AddImage(Widget* i_parent, const std::string& i_res, int x, int y);
	class NewerPresentText* AddText(Widget* i_parent, const SexyString& i_text, int x, int y, int width, int height);
};

class UIArtifactPresent : public UISingletonDialog<UIArtifactPresent>, public Sexy::ScrollWidgetListener
{
public:
	UIArtifactPresent();
	virtual ~UIArtifactPresent();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIArtifactPresent"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	void UpdateUI();
private:
	class PVZ2UIScrollingWidget* m_defaultScollingWdget;
	class UIArtifactPresentScrollPanel* m_defaultPanel;
};

struct NetworkArtifactPresentContent
{
    int         m_count;
    int			m_objectId;

    NetworkArtifactPresentContent()
    {
        m_count = 0;
        m_objectId = 0;
    }
};

class NetworkArtifactPresent : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(NetworkArtifactPresent, Sexy::RtObject, Sexy::RtClass);

public:
	std::vector<std::vector<NetworkArtifactPresentContent>> m_contents;
	std::vector<int> m_purchasedPresent;
	std::vector<int> m_orgPrices;
	std::vector<int> m_isInStock;
};

struct ArtifactPresentDetail
{
	ArtifactPresentDetail()
	{
		m_typeName = "";
		m_leftBuy = 0;
		m_orgPrice = 0;
		m_artifactId = 0;
		m_isInStock = 1;
	}

	std::string m_typeName;
	std::vector<NetworkArtifactPresentContent> m_contents;
	int m_leftBuy;
	int m_orgPrice;
	int m_artifactId;
	int m_isInStock;
};

class New_S2C_BuyArtifactPresent : public INetworkData
{
public:
    RT_CLASS_DEFINE(New_S2C_BuyArtifactPresent, INetworkData, RtClass);

    std::vector<NetworkArtifactPresentContent>   m_rewards;
};

class ArtifactPresentMgr : public LazySingleton <ArtifactPresentMgr>
{
public:
	ArtifactPresentMgr();
    ~ArtifactPresentMgr();

    void SyncActivityData(const NetworkArtifactPresent& i_data);
    void ShowNewerPresentDetail(int i_index);
    ArtifactPresentDetail FindTargetPresent(int i_index);
    int GetNumPresents();
    bool Load();
    void Init();
    void TestInit();
    bool TestLoad();
    int GetTargetPrice(int i_index);
    int GetTargetOrgPrice(int i_index);
    std::string GetTargetTypeName(int i_index);
    void BuyOffer(int i_index);
    void requestBuyOffer();
    std::string GetTargetSku(int i_index);
    SexyString GetTargetShortDes(int i_index);
    bool IsActive();
    void RequestNetwork();
    void TestRequestNetwork();
    void Close();
    void NotifyBundlePurchased(const std::vector<PaymentBundleInfo>& i_infos);
    int ConvertToServerIndex(int i_localIndex);
    int ConvertToLocalIndex(int i_serverIndex);

private:
    void onResultClosed();
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    std::map<int, ArtifactPresentDetail> m_cotentList;
    int m_currentPurchasedIndex;
    bool m_requested;
    bool m_resultCreated;
};

class UIArtifactPresentDetail : public UISingletonDialog<UIArtifactPresentDetail>
{
public:
	UIArtifactPresentDetail();
	virtual ~UIArtifactPresentDetail();

	virtual bool    OnCreate() override;
	virtual std::string GetLayoutName() override { return "UIArtifactPresentDetail"; }
	virtual void	ButtonPress(int i_id) override;
	virtual void	ButtonDepress(int i_id) override;
	void			InitView(const int i_artifactId, int i_index);
private:
	void 			Close();
	void 			DlgChildWidgetSetIgnoreMouseInput(UI::Dialog* i_dlg, const std::string & i_keyChild, const std::vector<std::string>& i_childs);
	std::string m_typeName;
	Rect m_minimapRect;
	int m_index;
};

#endif /* UIARTIFACTPRESENT_H_ */
