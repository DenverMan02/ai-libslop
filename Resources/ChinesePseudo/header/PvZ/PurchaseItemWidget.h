//
//  PurchaseItemWidget.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 5/1/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PurchaseItemWidget__
#define __PlantsVersusZombies2__PurchaseItemWidget__

#include "Widget.h"

class PurchaseItemWidget : public Sexy::Widget
{
public:
	PurchaseItemWidget(const class MagentoProductProps* i_props);
	virtual ~PurchaseItemWidget();

	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);
	
	virtual void Resize(int x, int y, int w, int h);
	
	static bool SupportsProduct(const class MagentoProductProps* i_props);
    
    Sexy::Image* GetGachaFlagImage(const std::string& strObjectItem);
    
    bool HasGemSpecialOffer(const std::string& sku);

private:

	Sexy::Image* getCoinsImage(const int i_coinCount);
    Sexy::Image* GetPvpCoinsImage(const int i_coinCount);
    Sexy::Image* getStaminaImage(const int i_coinCount);
    //PVZ2_CHINESE_START
    Sexy::Image* getGemsRetImage(const int i_gemCountId);
    Sexy::Image* getGemsBackgroundImage(const std::string& sku);
    Sexy::Image* getGemsImage(const int i_gemCount);
    Sexy::Image* getSunsImage(const int i_Count);
    Sexy::Image* getFuelImage(const int i_Count);
    Sexy::Image* getTimeEnergyImage(const int i_Count);
    Sexy::Image* getMysteryCrystalImage(const int i_Count);
    Sexy::Image* getZTicketImage(const int i_Count);
    Sexy::Image* getGiftImage(const std::string & sSku);
    Sexy::Image* getGachaImage(const std::string& strObjectItem);
    Sexy::Image* getRedPackImage(const std::string& strObjectItem);
    Sexy::Image* getPlantGiftImage(const std::string & sSku);
    //PVZ2_CHINESE_END
	void createPlantRig(const std::string& i_plantTypeName);
	void drawGameUpgrade(Sexy::Graphics* i_g, const Sexy::Rect i_drawRect, const std::string& i_objectItem);
	void drawPlant(Sexy::Graphics* i_g, const Sexy::Rect i_drawRect, const std::string& i_objectItem, int& io_animIndex);
	void drawCoins(Sexy::Graphics* i_g, const Sexy::Rect i_drawRect, const std::string& i_objectItem);
    void drawGacha(Sexy::Graphics* i_g, const Sexy::Rect i_drawRect, const std::string& i_objectItem);
	std::vector<class PopAnimRig*> m_animRigs;
	std::vector<Sexy::Rect> m_animRigRects;
	const class MagentoProductProps* m_props;
	class PVZ2UIGameObjectCard* m_card;
};

#endif /* defined(__PlantsVersusZombies2__PurchaseItemWidget__) */
