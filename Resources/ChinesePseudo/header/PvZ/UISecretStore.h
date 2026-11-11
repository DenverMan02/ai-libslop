/*
 * UISecretStore.h
 *
 *  Created on: 2020-6-17
 *      Author: Administrator
 */

#ifndef UISECRETSTORE_H_
#define UISECRETSTORE_H_

#include "UISingletonDialog.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "NetworkData.h"
#include "PVZ2UIButton.h"
#include "ButtonListener.h"
#include "UIRewardFrame.h"
#include "AwardEnums.h"

typedef struct SecretBundleDetail Detail;
typedef struct SecretAwardInfo AwardInfo;
typedef struct SecretAwardDisplayInfo AwardDisplayInfo;
class SecretStorePane;
class SecretStoreImage;
class SecretStoreText;
class SecretStoreButton;

namespace SecretStoreUtils
{
	SecretStorePane* AddPane(Widget* i_parent, const Detail& i_detail, const std::string& i_res, const std::string& i_sub_res, int x, int y, int width, int height);
	SecretStoreImage* AddImage(Widget* i_parent, const std::string& i_res, int x, int y, int width, int height);
	SecretStoreImage* AddImage(Widget* i_parent, const std::string& i_res, int x, int y);
	SecretStoreImage* AddImageUnScaled(Widget* i_parent, const std::string& i_res, int x, int y, int width, int height, bool stretched = false);
	SecretStoreImage* AddImageUnScaledCenterWidth(Widget* i_parent, const std::string& i_res, int x, int y, int width, int height, int i_offset_y, bool stretched = false);
	SecretStoreImage* AddImageUnScaledCenterWidth(Widget* i_parent, ImagePtr i_res, int x, int y, int width, int height, int i_offset_y, bool stretched = false);
	SecretStoreImage* AddImageUnScaledCenterWidthScale(Widget* i_parent, ImagePtr i_res, int x, int y, int width, int height, int i_offset_y, float i_scale, bool stretched = false);
	SecretStoreImage* AddImageAdaptive(Widget* i_parent, ImagePtr i_res, int x, int y, int width, int height);
	SecretStoreText* AddText(Widget* i_parent, const SexyString& i_text, int x, int y, int width, int height);
	SecretStoreText* AddTextUnScaled(Widget* i_parent, const SexyString& i_text, int x, int y, int width, int height);
	SecretStoreButton* AddButtonUnScaled(Widget* i_parent, int i_id, const std::string & normalImgPath, const std::string & downImgPath,
				int x, int y, int width, int height, Sexy::ButtonListener* i_listener);
	AwardInfo GetAwardInfoByActId(int i_actId, int i_amount);
	AwardDisplayInfo GetAwardDisplayInfoByActId(int i_actId);
}

struct SecretAwardDisplayInfo
{
	SecretAwardDisplayInfo()
	{
		Type = AWARD_None;
		Id = 0;
	}
	AwardType Type;
	int Id;
};

struct SecretAwardInfo
{
	SecretAwardInfo()
	: Reward("")
	{
		Type = UIRewardFrame::Reward_None;
		Id = 0;
		Amount = 0;
	}
	UIRewardFrame::RewardType Type;
	int Id;
	std::string Reward;
	int Amount;
};

struct SecretStoreContent
{
    int         m_count;
    int			m_objectId;

    SecretStoreContent()
    {
        m_count = 0;
        m_objectId = 0;
    }
};

struct SecretStoreBundle
{
	SecretStoreBundle()
	{
		m_leftBuyCount = 0;
		m_price = 0;
		m_objectId = 0;
	}

	int m_leftBuyCount;
	int m_price;
	int m_objectId;
	std::vector<SecretStoreContent> m_contents;
};

struct SecretBundleDetail
{
	SecretBundleDetail()
	{
		m_purchased = false;
		m_orgPrice = 0;
		m_leftBuy = 0;
	}

	std::vector<SecretAwardInfo> m_awardInfos;
	std::vector<SecretStoreContent> m_contents;
	bool m_purchased;
	int m_orgPrice;
	int m_leftBuy;
	SecretAwardDisplayInfo m_displayInfo;
};

class SecretStoreText : public Widget
{
public:
	SecretStoreText();
	SecretStoreText(const SexyString & xstr);
	~SecretStoreText();

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

class SecretStoreImage : public Widget
{
public:
	SecretStoreImage();
	SecretStoreImage(const std::string & str_id);
	SecretStoreImage(const std::string & str_id, bool i_stretched);
	SecretStoreImage(ImagePtr i_image, bool i_stretched);
	virtual ~SecretStoreImage();

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

protected:
	void internalDraw(Sexy::Graphics* i_g);
	virtual void drawImage(Sexy::Graphics* i_g);

protected:
	ImagePtr m_pImage;

private:
	Sexy::Transform m_tranForm;
	bool    m_bTrans;
	bool    m_bDisabled = false;
	bool	m_bStretched;
};


class SecretStoreCenterAdaptiveImage : public SecretStoreImage
{
public:
	SecretStoreCenterAdaptiveImage(ImagePtr i_image);

protected:
	void drawImage(Sexy::Graphics* i_g) override;
};

class SecretStoreCenterWidthImage : public SecretStoreImage
{
public:
	SecretStoreCenterWidthImage(const std::string & str_id, bool i_stretched, int i_offset_y);
	SecretStoreCenterWidthImage(ImagePtr i_image, bool i_stretched, int i_offset_y);

protected:
	void drawImage(Sexy::Graphics* i_g) override;

	int m_offsetY;
};

class SecretStoreCenterWidthScaleImage : public SecretStoreCenterWidthImage
{
public:
	SecretStoreCenterWidthScaleImage(ImagePtr i_image, bool i_stretched, int i_offset_y, float i_scale);

protected:
	void drawImage(Sexy::Graphics* i_g) override;

private:
	float m_scale;
};

class SecretStoreButton : public PVZ2UIButton
{
public:
	SecretStoreButton(int i_id,const std::string & normalImgPath,const std::string & downImgPath, Sexy::ButtonListener* i_listener);
	~SecretStoreButton();

	void SetImageType(PVZ2UIImageType imageType);
};

class SecretStorePane : public Widget, public Sexy::ButtonListener
{
public:
	SecretStorePane(const SecretBundleDetail& i_detail, const std::string & i_background, const std::string & i_title);
	~SecretStorePane();

	void Init();
	virtual void                ButtonDepress(int i_id) override;
	void SetIndex(int i_index) { m_index = i_index; }
	void SetDisable(bool i_disable);
private:
	SecretBundleDetail m_detail;
	std::string m_res;
	std::string m_titleRes;
	int m_index;
	SecretStoreButton* m_btn;
};

class UISecretStoreScrollPanel : public UISingletonDialog<UISecretStoreScrollPanel>
{
public:
	UISecretStoreScrollPanel();
	virtual ~UISecretStoreScrollPanel();
	void UpdateUI(PVZ2UIScrollingWidget* i_scrollWidget);

	virtual std::string GetLayoutName() override { return "UISecretStoreScrollPanel"; }
	virtual void	ButtonPress(int i_id) override;
	virtual void	ButtonDepress(int i_id) override;
};

class UISecretStore : public UISingletonDialog<UISecretStore>, public Sexy::ScrollWidgetListener
{
public:
	UISecretStore();
	virtual ~UISecretStore();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UISecretStore"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;
	void Update() override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	void UpdateUI();
	void SyncTime(int i_endDate);
	void UpdateTime();
	void SyncRefreshTime();
private:
	class PVZ2UIScrollingWidget* m_defaultScollingWdget;
	class UISecretStoreScrollPanel* m_defaultPanel;
	time_t m_endTime;
	time_t m_refreshTime;
};

class NetworkSecretStore : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(NetworkSecretStore, Sexy::RtObject, Sexy::RtClass);

public:
	std::vector<SecretStoreBundle> m_bundles;
	//std::vector<int> m_purchasedPresent;
};

class SecretStoreMgr : public LazySingleton <SecretStoreMgr>
{
public:
	SecretStoreMgr();
    ~SecretStoreMgr();

    void SyncActivityData(const NetworkSecretStore& i_data);
    SecretBundleDetail FindTargetBundle(int i_index);
    int GetNumBundles();
    bool Load();
    void Init();
    void InitTest();
    bool LoadTest();
    int GetTargetPrice(int i_index);
    int GetTargetPrice(const std::string& i_sku);
    void BuyOffer(int i_index, int i_price);
    std::string GetTargetSku(int i_index);
    std::string GetTargetSkuByPrice(int i_price);
    SexyString GetTargetShortDes(int i_index);
    MagentoProductPropsPtr GetBundleProductPtrByPrice(float i_price, const std::string& i_type);
    bool IsActive();
    void RequestNetwork();
    void Close();
    void NotifyBundlePurchased(const std::vector<PaymentBundleInfo>& i_infos);
    void RequestReward();

private:
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void onResultClosed();

    std::map<int, SecretBundleDetail> m_cotentList;
    int m_currentPurchasedIndex;
    bool m_requested;
    bool m_resultCreated;
};

#endif /* UISECRETSTORE_H_ */
