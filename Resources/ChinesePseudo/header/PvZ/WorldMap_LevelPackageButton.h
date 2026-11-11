/*
 * WorldMap_LevelPackageButton.h
 *
 *  Created on: 2023-1-31
 *      Author: zhousen
 */

#ifndef WORLDMAP_LEVELPACKAGEBUTTON_H_
#define WORLDMAP_LEVELPACKAGEBUTTON_H_

#include "RtObject.h"
#include "UIEasyButtonWidget.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "UIRewardFrame.h"
#include "UISingletonDialog.h"

// World Level Package Button
class WorldMap_LevelPackageButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_LevelPackageButton, UIEasyButtonWidget, RtClass);

    WorldMap_LevelPackageButton();
    virtual ~WorldMap_LevelPackageButton();

    // Public Interface (Inheritable)

    virtual void		Draw(Graphics* i_g) override;

    static bool         CheckVisibility(bool i_init = false);

    void onNotifyRefreshActivityList(bool result, const std::set<int>& changeList);

    void UpdateExpireTime();

protected:
    time_t GetRecentExpirePackageTime();

protected:
    time_t m_expireTime;
};

// World level Package Data
struct WorldLevelPackageItem
{
	std::vector<S2C_BonusInfo> BonusData;
    int32   Price;
    int32   State;// buy left times.

    WorldLevelPackageItem() {
    	BonusData.clear();
    	Price = 0;
    	State = 0;
    }
};

struct WorldLevelPackageData
{
    std::string WorldName;
    std::vector<WorldLevelPackageItem> PackageList;

    WorldLevelPackageData() {
    	WorldName == "";
    	PackageList.clear();
    }
};

class WorldLevelPackageNetworkData : public INetworkData
{
public:
    RT_CLASS_DEFINE(WorldLevelPackageNetworkData, INetworkData, RtClass);

    std::vector<WorldLevelPackageData> WorldList;
};

// World Level Package Manager
class WorldLevelPackageManager : public LazySingleton <WorldLevelPackageManager>
{
public:
	WorldLevelPackageManager();
	virtual ~WorldLevelPackageManager();

    void LoadData(const WorldLevelPackageNetworkData& shopData);
    const WorldLevelPackageNetworkData& GetData() const;
    WorldLevelPackageData GetWorldLevelPackageData(std::string world);
    void RequestNetwork(bool onlyOnce = false);
    bool CheckPackageValid(std::string worldName, int index);
    bool CheckTimeValid(std::string worldName, int index);
    bool HasValidPackage(std::string worldName);
    std::string GetLatestValidPackageWorldName();
    SexyString GetWorldLevelPackageCountdownStr(std::string worldName, int index, int days);

    std::string GetCurrentValidWorldName() { return m_currentValidWorldName; }
    void SetCurrentValidWorldName(std::string worldName) { m_currentValidWorldName = worldName; }
    void RefreshValidPackage();// latest valid package world name.

    void onNotifyRefreshActivityList(bool result, const std::set<int>& changeList);
    bool IsInitRequest();
    void ResetInitRequest();

private:
    void TestData();

private:
    WorldLevelPackageNetworkData m_data;
    std::string m_currentValidWorldName;
    bool m_initRequest;
};

// UI World Level Package Bonus Widget
class WorldLevelPackageBonusWidget : public Sexy::Widget
{
public:
	WorldLevelPackageBonusWidget(int id, int quantity);

	void Draw(Sexy::Graphics* i_g) override;
	void Resize(int theX, int theY, int theWidth, int theHeight);

protected:
	void InitView();

protected:
	UIRewardFrame* m_reward;
	int m_id;
	int m_count;
	SexyString m_countStr;
};

// UI World Level Package Button
class WorldLevelPackageButton : public PVZ2UIButton, public ButtonListener
{
public:
	typedef Delegate0 LevelPackageCallback;
	WorldLevelPackageButton(int buttonID);

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView();
    void SetClickCallback(LevelPackageCallback callback){ m_callback = callback; }

protected:
    void BuyConfirm(class UIMessageBox* box, int buttonID);

    Image* m_bgImage;
    Image* m_bonusImage;
    Image* m_countDownBgImage;
    Image* m_priceImage;
    Image* m_discountImage;
    SexyString m_titleString;
    SexyString m_countDownString;
    SexyString m_boughtCountString;

    LevelPackageCallback m_callback;// click callback

    int m_index;
    std::string m_worldName;
    int m_buyLeftTimes;
    std::vector<S2C_BonusInfo> m_bonusInfo;
};

// UI World Level Package
class UIWorldLevelPackage : public UISingletonDialog<UIWorldLevelPackage>
{
public:
	enum {
		WorldLevelPackageButton_Close = 1000,
		WorldLevelPackageButton_Info = 1001,
		WorldLevelPackageButton_StartId = 2000,

	};
	UIWorldLevelPackage();
	virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "UIWorldLevelPackage"; }
    virtual void ButtonDepress(int i_id) override;

private:
    void InitView();
    void ShowTips();
};

// UI World Level Package Detail Reward Item
class WorldLevelPackageRewardWidget : public PVZ2UIButton, public ButtonListener
{
public:
	WorldLevelPackageRewardWidget(int buttonID, int id, int count);
	~WorldLevelPackageRewardWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
	virtual void Resize(int theX, int theY, int theWidth, int theHeight) override;

    void SetSelected(bool selected) { m_selected = selected; }
    bool IsSelected() const { return m_selected; }
    void InitView();

protected:
    int m_index;
    bool m_selected;
    UIRewardFrame* m_rewardFrame;
};

// UI World Level Package Detail Reward Detail Item
class WorldLevelPackageRewardDetailWidget : public Sexy::Widget
{
public:
	WorldLevelPackageRewardDetailWidget(int id);

    virtual void Draw(Graphics* g) override;

    virtual void InitView();
    virtual void SetImage(std::string bgName);

protected:
    Image* m_bgImage;
    int m_id;
    SexyString m_str;
};

class WorldLevelPackageRewardDetailPlant : public WorldLevelPackageRewardDetailWidget
{
public:
	WorldLevelPackageRewardDetailPlant(int id);
	~WorldLevelPackageRewardDetailPlant();

    virtual void Draw(Graphics* g) override;
    virtual void InitView() override;

protected:
    void InitHeadshotPopanim(std::string plantName);
};

class WorldLevelPackageRewardDetailWidgetFactory
{
public:
	static WorldLevelPackageRewardDetailWidget* CreateWidget(int id);
};

// UI World Level Package Detail Reward Banner Item
class WorldLevelPackageRewardBannerWidget : public Sexy::Widget
{
public:
	WorldLevelPackageRewardBannerWidget(int id);

    virtual void Draw(Graphics* g) override;

    virtual void InitView();
    virtual void SetImage(std::string bgName);

protected:
    Image* m_bgImage;
    int m_id;
};

class WorldLevelPackageRewardBannerPlant : public WorldLevelPackageRewardBannerWidget
{
public:
	WorldLevelPackageRewardBannerPlant(int id);
	virtual ~WorldLevelPackageRewardBannerPlant();

    virtual void Draw(Graphics* g) override;
    virtual void InitView() override;

    void SetPlant(std::string plantName);

protected:
    class PlantDisplayFrame* m_board;
};

class WorldLevelPackageRewardBannerWidgetFactory
{
public:
	static WorldLevelPackageRewardBannerWidget* CreateWidget(int id);
};

// UI World Level Package Detail
class UIWorldLevelPackageDetail : public UISingletonDialog<UIWorldLevelPackageDetail>
{
public:
	enum {
		WorldLevelPackageDetailButton_Close = 1000,
		WorldLevelPackageDetailButton_Buy,
		WorldLevelPackageDetailButton_StartId = 2000,
	};

	UIWorldLevelPackageDetail();
	~UIWorldLevelPackageDetail();
	virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "UIWorldLevelPackageDetail"; }
    virtual void ButtonDepress(int i_id) override;
    virtual void Update() override;

    void InitView(int index);
    void SetPlantDisplayFrame(class PlantDisplayFrame* plantPtr);
    class PlantDisplayFrame* GetPlantDisplayFrame();

private:
	void Close();
    SexyString GetLevelPackageCountdownStr(std::string worldName, int index, int days);
    void BuyConfirm(class UIMessageBox* box, int buttonID);
    void SelectRewardItem(int index);

private:
    int m_index;
    std::string m_worldName;
    UIWidgetText* m_countDownText;
    PVZ2UIButton* m_buyBtn;
    std::vector<WorldLevelPackageRewardWidget*> m_rewardItemList;
    class PlantDisplayFrame* m_plantDisplayBoard;
    std::vector<Widget*> m_rewardDetailList;
    std::vector<Widget*> m_rewardBannerList;

    std::vector<int> m_bonusIdList;
    WorldLevelPackageRewardBannerPlant* m_bannerPlant;
    WorldLevelPackageRewardBannerWidget* m_bannerImage;
};

namespace Message
{
	void LevelPackageSelectRewardItem(int index);
}

#endif /* WORLDMAP_LEVELPACKAGEBUTTON_H_ */
