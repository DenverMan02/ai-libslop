/*
 * PlantBundleUI.h
 *
 *  Created on: 2017-8-18
 *      Author: Administrator
 */

#ifndef PLANTBUNDLEUI_H_
#define PLANTBUNDLEUI_H_

#include "NetworkData.h"
#include "Widget.h"
//#include "core.h"
#include "ButtonListener.h"
#include "Effect_PopAnim.h"
#include "PVZ2UIButton.h"

struct PlantBundleData
{
	PlantBundleData()
    {
    	Amount = 0;
    	ObjectId = 0;
    }

	int Amount;
	int ObjectId;
};

struct NetworkBundleData
{
	NetworkBundleData()
	{
		ObjectId = 0;
		Quantity = 0;
	}

	int ObjectId;
	int Quantity;
};

class PlantBundleInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(PlantBundleInfo, Sexy::RtObject, Sexy::RtClass);

public:
    time_t expireTime;
    int originalPrice;
    int salePrice;
    int discount;
    std::string purchaseType;
    int limitedBuy;
    int itemObjectId;
    std::vector<NetworkBundleData>     bundleInfos;
};

class PlantBundleMgr : public LazySingleton <PlantBundleMgr>
{
public:
	PlantBundleMgr();
    ~PlantBundleMgr();

    void requestNetwork();
    void RefreshActivity();
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class PlantBundleContent : public Sexy::Widget
{
public:

	PlantBundleContent(const PlantBundleData & data);
	virtual ~PlantBundleContent();

	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

private:

    void            setupScreen();

private:

    PlantBundleData  m_data;
};

class PlantBundleUI : public Sexy::Widget, Sexy::ButtonListener
{
public:

	PlantBundleUI();
    ~PlantBundleUI();

    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	void InitView();
	void SyncActivityData(const PlantBundleInfo& i_data);

private:
	void InitTestData();
	void RefreshUI();
    //PVZ2UIButton* m_shopBtn;
	ImagePtr m_plantImage;
	int m_startX;
	int m_startY;
	Sexy::Point m_des_pos;
	std::vector<PlantBundleData> m_bundleDatas;
	// Sync datas
	int m_discount;
	int m_originalPrice;
	int m_salePrice;
	int m_limitedBuy;
	time_t m_expireTime;
	int m_itemObjectId;

	PVZ2UIButton* m_purchaseButton;
};


#endif /* PLANTBUNDLEUI_H_ */
