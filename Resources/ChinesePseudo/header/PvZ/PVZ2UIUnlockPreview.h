//
//  PVZ2WorldPreview.h
//  PlantsVersusZombies2
//
//  Created by aschneider on 4/29/13
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVZ2UIUnlockPreview_h
#define PlantsVersusZombies2_PVZ2UIUnlockPreview_h

#include "Core.h"
#include "ResourceHelpers.h"
#include "MagentoService.h"

class MapEventItem;
class PVZ2UIButton;

class PVZ2UIUnlockPreview : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	PVZ2UIUnlockPreview();
	virtual ~PVZ2UIUnlockPreview();

	virtual void Draw(Sexy::Graphics* i_g);
	virtual void DrawOverlay(Sexy::Graphics* i_g);

	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);

	void SetupForWorldNamed(const std::string& i_worldName);

private:
	void	UnlockedStarGateButtonPressed();
	void	BypassStarGateButtonPressed();
    void	OnServerGemCallBack(const bool& i_Success);

	//const MapEventItem*	m_startStargateEvent;
	std::string			m_worldName;

	SexyString			m_worldNameText;
	SexyString			m_worldDescriptionText;
	SexyString			m_teaserHeaderText;
	SexyString			m_teaserBodyText;
	SexyString			m_cashCostText;
	SexyString			m_starCostText;
	SexyString			m_starUnlockText;
	SexyString			m_buyNowText;
	SexyString			m_unlockInstructionsText;

	bool				m_isPurchasable;
	bool				m_unlockStarGate;
    bool                m_widestDescriptionBox;
    
    int                 m_worldkeyPrize;

	PVZ2UIButton*		m_buyForStarsButton;
	PVZ2UIButton*		m_buyForCashButton;
	PVZ2UIButton*		m_closeButton;

	CachedUIResourcePtr<Image>* m_previewImageToUse;

	MagentoProductPropsPtr mCacheProps;
	std::string			   mCachePreWorldName;
};

#endif
