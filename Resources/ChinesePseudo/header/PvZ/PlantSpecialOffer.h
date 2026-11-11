/*
 * PlantSpecialOffer.h
 *
 *  Created on: 2018-3-2
 *      Author: Administrator
 */

#ifndef PLANTSPECIALOFFER_H_
#define PLANTSPECIALOFFER_H_

#include "NetworkData.h"
#include "Widget.h"
//#include "core.h"
#include "ButtonListener.h"
#include "Effect_PopAnim.h"
#include "PVZ2UIButton.h"

namespace Message
{
	void NotifyPurchasedSpecialOffer();
}

struct SpecialOfferInfo
{
	SpecialOfferInfo()
	{
		PlantId = 0;
		AvatarId = 0;
		EndTime = 0;
		CoinNum = 0;
		GemNum = 0;
	}

	int PlantId;
	int AvatarId;
	time_t EndTime;
	int CoinNum;
	int GemNum;
};

struct BuyOfferInfo
{
	BuyOfferInfo()
	{
		ObjectId = 0;
		Amount = 0;
	}
	int ObjectId;
	int Amount;
};

class CustomDisplayBoard : public Sexy::Widget, Sexy::ButtonListener
{
public:
	CustomDisplayBoard(const std::string& i_plantName, const Rect& i_rect);
	~CustomDisplayBoard();

	virtual void	Draw(Sexy::Graphics* i_g) override;
	virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;

	void InitView();
	virtual void	ButtonPress(int i_id) override;
	virtual void	ButtonDepress(int i_id) override;

	void SetVisible(bool isVisible) override;

	void SetAvatarIndex(int i_avatarIndex);

private:
	class PlantDisplayBoard* m_plantDisplay;
	std::string m_plantName;
	Rect m_drawRect;
};

class NetworkOfferInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkOfferInfo, Sexy::RtObject, Sexy::RtClass);

public:
    int plantId;
    int avatarId;
    int coinNum;
    int gemNum;
};

class NetworkBuyOfferInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkBuyOfferInfo, INetworkData, RtClass);

public:
	std::vector<BuyOfferInfo> itemInfos;
};

class PlantSpecialOfferUI : public Sexy::Widget, Sexy::ButtonListener
{
public:

	PlantSpecialOfferUI();
    ~PlantSpecialOfferUI();

    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void 	DrawOverlay(Sexy::Graphics* i_g);

	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	void InitView();
	void InitTestData();
	ImagePtr GetImgPtrFromObjectId(int i_objectId);

	static void requestNetwork();
	void RefreshActivity();
	void SyncActivityData(int i_plantId, int i_avatarId, int i_endDate, int i_coinNum, int i_gemNum);

	void BuyOffer(const std::string& i_sku);
	void requestBuyOffer();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void onNotifyBundlePurchased(int i_type, const std::vector<PaymentBundleInfo>& i_infos);

private:
	// main board
	Rect m_dialogRect;
	// mini board
	Rect m_minimapRect;
	CustomDisplayBoard* m_board;
	// plant detail & avatar detail
	Image* m_plantBg;
	Image* m_plantImg;
	Rect m_plantBgRect;
	Rect m_plantImgRect;
	Image* m_avatarBg;
	Image* m_avatarImg;
	Rect m_avatarBgRect;
	Rect m_avatarImgRect;
	// left time
	Rect m_leftTimeRect;
	// network detail
	SpecialOfferInfo m_info;
	// plant piece & avatar piece
	ImagePtr m_pieceImg;
	Rect m_pieceImgRect;
	ImagePtr m_avatarPieceImg;
	Rect m_avatarPieceImgRect;
	Rect m_rewardDesRect;
	Rect m_rewardDesRect2;
	// purchase button
	PVZ2UIButton* m_purchaseBtn;
	Rect m_crossRect;
	// main bg
	Image* m_mainBg;
	Rect m_mainBgRect;
	// banner
	Image* m_bannerImg;
	Rect m_bannerRect;
	// title
	Image* m_titleImg;
	Rect m_titleRect;
	// add
	Image* m_addImg;
	Rect m_addRect;
	// title text
	Rect m_titleTextRect;
	// plant des & avatar des
	SexyString m_plantName;
	SexyString m_avatarName;
	Image* m_plantTextImg;
	Rect m_plantTextRect;
	Image* m_avatarTextImg;
	Rect m_avatarTextRect;
	// preview button
	PVZ2UIButton* m_previewBtn;
	// gray bg
	Image* m_grayBg;
	Rect m_grayBgRect;
	// label
	Image* m_labelImg;
	Rect m_labelRect;
	// label text
	SexyString m_labelName;
	Rect m_labelTextRect;
	// coin text & gem text
	SexyString m_coinText;
	Rect m_coinTextRect;
	SexyString m_gemText;
	Rect m_gemTextRect;
	bool m_hasPurchased;
};


#endif /* PLANTSPECIALOFFER_H_ */
