//
//  PinataStyleChooser.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 11/13/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PinataStyleChooser_h
#define PlantsVersusZombies2_PinataStyleChooser_h

#include <string>
#include "ResourceHelpers.h"
#include "PrimeText_Game.h"

namespace Sexy
{
	class Image;
	class PopAnim;
}
class EventBackgroundDraw;
class HolidayEventBannerData;
class HolidayEventProperties;

class PinataStyleChooser
{
public:
	virtual ~PinataStyleChooser() {}
	enum EventBackgroundDraw
    {
        EVENT_BG_DRAW_STRETCHED,
        EVENT_BG_DRAW_TILED,
        EVENT_BG_DRAW_BOTH_STRETCH_AND_TILE,
    };

	/* These parts are data driven through lod_config.json as much as possible */
	Sexy::PopAnim*			GetRegularPinataArt();
	Sexy::PopAnim*			GetBigPinataAnimation();
	int						GetBigPinataOffset();
	bool					UseHolidayAssetSwaps();
	
	int						GetHitsMax();
	const std::string&		GetSoundBreak(bool i_isLastBox, bool i_isConsolationReward);
	const std::string&		GetSoundDrop(bool i_isLastBox);
	
	const std::string&		GetBannerProgressPinataImage();
	const std::string&		GetBannerProgressMegaPinataImage();
	
	// world map banner setup
	virtual void            PrepareLODDisplayCommon( Sexy::ImagePtr& o_backgroundStretchImage,
													Sexy::ImagePtr& o_backgroundTileImage,
													EventBackgroundDraw& o_backgroundDrawTechnique,
													Sexy::ImagePtr& o_leftZombieImage,
													Sexy::ImagePtr&  o_rightZombieImage,
													std::string& o_headerReadyText,
													std::string& o_descReadyText);
    virtual void            PrepareLODDisplayUpcoming(Sexy::ImagePtr& o_backgroundStretchImage,
													  Sexy::ImagePtr& o_backgroundTileImage,
													  EventBackgroundDraw& o_backgroundDrawTechnique,
													  Sexy::ImagePtr& o_leftZombieImage,
													  Sexy::ImagePtr&  o_endCapImage,
													  std::string& o_headerUpcomingText,
													  std::string& o_descUpcomingText);
    
	const char*				GetPianoZombiePlayEventName(bool i_isPlayingPinataParty);
	const char*				GetPianoZombieStopEventName(bool i_isPlayingPinataParty);
	void					PlaySwitchAudio();
	
	Sexy::Image*			GetProgressImage(bool i_isLastBox);
	void					GetPartyProgressiveAwardHeaderInfo(bool i_isLastBox, std::string& o_imageName, std::string& o_headerText, std::string& o_descText);
	void					GetPartyProgressiveAwardFooterInfo(bool i_isLastBox, std::string& o_imageName, std::string& o_headerText, std::string& o_descText);
	
	void					GetPartyOpenAwardsHeaderInfo(std::string& o_imageName, std::string& o_headerText, std::string& o_descText);
	void					GetPartyOpenAwardsFooterInfo(std::string& o_imageName, std::string& o_headerText, std::string& o_descText);
	
	void					SpawnEffectFromTop(Sexy::Widget* i_parentWidget, int i_x, int i_dis);
	Sexy::Rect				CalculateBigPinataRect(Sexy::Widget* i_widget, Sexy::Widget* i_containerWidget, Sexy::PopAnim* i_anim);
	
	
	Sexy::Color					GetPinataPartyWorldBannerTextColor();
	Sexy::Color					GetAwardsHeaderTextColor();
	Sexy::Color					GetAwardsFooterTextColor();
	Sexy::Color					GetProgressiveBigAwardHeaderTextColor();
	Sexy::Color					GetProgressiveBigAwardFooterTextColor();
	Sexy::Color					GetProgressiveAwardHeaderTextColor();
	Sexy::Color					GetProgressiveAwardFooterTextColor();
	
	//anim related stuff
	
	void UpdateLevelBackgroundResources(std::set<std::string> &io_resourceGroupNames, std::string i_backgroundResourceGroup) const;
	void UpdateLevelBackgroundResources(std::vector<std::string> &io_resourceGroupNames, std::string i_backgroundResourceGroup) const;
	std::string UpdateLevelImagePrefix(std::string i_backgroundLevelImagePrefix) const;
	bool HasHolidayLevelBackground() const;
	
	void UpdateLevelMowerResources(std::set<std::string> &io_resourceGroupNames, std::string i_mowerResourceGroup) const;
	void UpdateLevelMowerResources(std::vector<std::string> &io_resourceGroupNames, std::string i_mowerResourceGroup) const;
	std::string UpdateLevelMowerPopanim(std::string i_levelMowerPopanim) const;
	bool HasHolidayMowerSwap() const;
	
	const std::string& GetZombieHolidaySwapForType(const std::string& i_zombieTypeName);
    const std::string GetHolidayName() const;
    const HolidayEventProperties* GetEventProperties() const;
	
private:
    const HolidayEventBannerData&   GetCurrentBannerData();
    bool                            isScaledBigPinata();
    Sexy::Rect                      calculateScaledBigPinataRect(Sexy::Widget* i_containerWidget, Sexy::PopAnim* i_anim);
};

#endif
