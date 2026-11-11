//
//  PinataStyleChooserFactory.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 11/13/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PinataStyleChooserFactory__
#define __PlantsVersusZombies2__PinataStyleChooserFactory__

#include "PinataStyleChooser.h"
#include "ObjectTypeDescriptor.h"
#include "PrimeText_Game.h"

#pragma mark
struct ZombieSwapData
{
	std::string ZombieTypeName;
	std::string SwapZombieTypeName;
};

class ZombieSwapListData : public ObjectTypeDescriptor
{
public:
    RT_CLASS_DEFINE(ZombieSwapListData, ObjectTypeDescriptor, RtClass);
    
    std::vector<ZombieSwapData> Value;
};

#pragma mark
class PinataSoundData : public ObjectTypeDescriptor
{
public:
    RT_CLASS_DEFINE(PinataSoundData, ObjectTypeDescriptor, RtClass);
    
    std::string	PinataDropSound = "Play_UI_LOD_Pinata_Drop";
    std::string PinataBreakSound = "Play_UI_LOD_Pinata_Break";
    std::string PinataConsolationBreakSound = "Play_UI_LOD_Zombie_Pinata_Break_Basic";
    
    std::string	MegaPinataDropSound = "Play_UI_LOD_Zombie_Pinata_Drop";
    std::string MegaPinataBreakSound = "Play_UI_LOD_Zombie_Pinata_Break_Special";
};

#pragma mark
struct HolidayEventBannerData
{
    typedef PinataStyleChooser::EventBackgroundDraw BannerBackgroundDraw;
    
    std::string             Name = "Default";
    
    std::string             ReadyBackgroundStretchImage = "IMAGE_UI_HUD_WORLDMAP_LOD_MINI_STRETCH";
    std::string             ReadyBackgroundTileImage = "";
    BannerBackgroundDraw   ReadyBackgroundDrawTechnique = PinataStyleChooser::EVENT_BG_DRAW_STRETCHED;
    std::string             ReadyLeftImage = "IMAGE_UI_HUD_WORLDMAP_LOD_PINATA";
    std::string             ReadyRightImage = "IMAGE_UI_HUD_WORLDMAP_LOD_ZOMBIES2";
    std::string             ReadyHeaderText = "[WORLDMAP_EVENT_LOD_TITLE]";
    std::string             ReadyDescriptionText = "[WORLDMAP_EVENT_LOD_DESC]";
    
    std::string             UpcomingBackgroundStretchImage = "IMAGE_UI_HUD_WORLDMAP_LOD_MINI_STRETCH";
    std::string             UpcomingBackgroundTileImage = "";
    BannerBackgroundDraw   UpcomingBackgroundDrawTechnique = PinataStyleChooser::EVENT_BG_DRAW_STRETCHED;
    std::string             UpcomingLeftImage = "IMAGE_UI_HUD_WORLDMAP_LOD_PINATA";
    std::string             UpcomingRightImage = "IMAGE_UI_HUD_WORLDMAP_LOD_MINI_CAP";
    std::string             UpcomingHeaderText = "[WORLDMAP_EVENT_LOD_UPCOMING_DESC]";
    std::string             UpcomingDescriptionText = "[WORLDMAP_EVENT_LOD_UPCOMING_TITLE]";
};

#pragma mark
class HolidayEventProperties : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(HolidayEventProperties, ObjectTypeDescriptor, RtClass);
    
	HolidayEventProperties()
	{
		UseHolidayAssetSwaps = false;
		SwapAssetsForLODsOnly = false;

        BigPinataScaleWithCenterOverride = 0.0f;
		BigPinataAnimation = "POPANIM_UI_LEVELOFTHEDAY_PRIZE_MEGA_PINATA";
		BigPinataOffset = -200;
		
		MegaPinataHitCount = 3;
        
        Banners = std::vector<HolidayEventBannerData>{ HolidayEventBannerData{} };
		
		ConfettiEffect = "POPANIM_UI_LEVELOFTHEDAY_CONFETTI";
		
		ProgressiveBigAwardHeaderImage = "IMAGE_UI_LEVELOFTHEDAY_INSTRUCTIONAL_BANNER_3SLICE";
		ProgressiveBigAwardHeaderText = "[LOD_OPEN_BIG_REWARD_HEADER]";
		ProgressiveBigAwardDescriptionText = "[LOD_OPEN_BIG_REWARD_SUBHEADER]";
		ProgressiveBigAwardHeaderTextColor = "PinataPartyHeadingTextColor";
		
		ProgressiveAwardHeaderImage = "IMAGE_UI_LEVELOFTHEDAY_INSTRUCTIONAL_BANNER_3SLICE";
		ProgressiveAwardHeaderText = "[LOD_NEXT_TIME_HEADER]";
		ProgressiveAwardDescriptionText = "[LOD_NEXT_TIME_SUBHEADER]";
		ProgressiveAwardHeaderTextColor = "PinataPartyHeadingTextColor";
		
		ProgressiveBigAwardFooterImage = "";
		ProgressiveBigAwardFooterText = "";
		ProgressiveBigAwardFooterDescriptionText = "";
		ProgressiveBigAwardFooterTextColor = "PinataPartyHeadingTextColor";
		
		ProgressiveAwardFooterImage = "";
		ProgressiveAwardFooterText = "";
		ProgressiveAwardFooterDescriptionText = "";
		ProgressiveAwardFooterTextColor = "PinataPartyHeadingTextColor";
		
		BigPinataProgressImage = "IMAGE_UI_LEVELOFTHEDAY_PROGRESS_MEGAPINATA";
		PinataProgressImage = "IMAGE_UI_LEVELOFTHEDAY_PROGRESS_PINATA";
		
		AwardsBannerHeaderImage = "IMAGE_UI_LEVELOFTHEDAY_INSTRUCTIONAL_BANNER_3SLICE";
		AwardsBannerHeaderText = "[LOD_OPEN_REWARDS_HEADER]";
		AwardsBannerDescriptionText = "[LOD_OPEN_REWARDS_SUBHEADER]";
		AwardsBannerHeaderTextColor = "PinataPartyHeadingTextColor";
		
		AwardsBannerFooterImage = "";
		AwardsBannerFooterText = "";
		AwardsBannerFooterDescriptionText = "";
		AwardsBannerFooterTextColor = "PinataPartyHeadingTextColor";
		
        BannerHeaderTextColor = PrimeText_Game::Color_Generic_Title;
		
		BannerProgressPinataImage = "IMAGE_UI_HUD_WORLDMAP_PROGRESS_PINATA_SM";
		BannerProgressMegaPinataImage = "IMAGE_UI_HUD_WORLDMAP_PROGRESS_MEGAPINATA_SM";
	}
    
    std::string				 Name;
	std::vector<std::string> PinataPopAnims;
	std::string				 BigPinataAnimation;
	int						 BigPinataOffset;
	bool					 UseHolidayAssetSwaps;
	bool					 SwapAssetsForLODsOnly;
    float                    BigPinataScaleWithCenterOverride;
	int						 MegaPinataHitCount;
	
    RtWeakPtr<PinataSoundData> PinataSounds;
    
    std::vector<HolidayEventBannerData> Banners;

	Color		BannerHeaderTextColor;
	
	std::string ConfettiEffect;
	
	std::string	BannerProgressPinataImage;
	std::string	BannerProgressMegaPinataImage;
	
	std::string LevelBackgroundGroup;
	std::string LevelBackgroundImagePrefix;
	
	std::string LevelMowerSwapGroup;
	std::string LevelMowerSwapAnim;
	
	std::string PinataPartyPianoMusicStartEvent;
	std::string PinataPartyPianoMusicStopEvent;
	std::string AudioSwitch;
	
	std::string ProgressiveBigAwardHeaderImage;
	std::string ProgressiveBigAwardHeaderText;
	std::string ProgressiveBigAwardDescriptionText;
	std::string	ProgressiveBigAwardHeaderTextColor;
	
	std::string ProgressiveAwardHeaderImage;
	std::string ProgressiveAwardHeaderText;
	std::string ProgressiveAwardDescriptionText;
	std::string	ProgressiveAwardHeaderTextColor;
	
	std::string ProgressiveBigAwardFooterImage;
	std::string ProgressiveBigAwardFooterText;
	std::string ProgressiveBigAwardFooterDescriptionText;
	std::string	ProgressiveBigAwardFooterTextColor;
	
	std::string ProgressiveAwardFooterImage;
	std::string ProgressiveAwardFooterText;
	std::string ProgressiveAwardFooterDescriptionText;
	std::string	ProgressiveAwardFooterTextColor;

	std::string BigPinataProgressImage;
	std::string PinataProgressImage;
	
	std::string AwardsBannerHeaderImage;
	std::string AwardsBannerHeaderText;
	std::string AwardsBannerDescriptionText;
	std::string	AwardsBannerHeaderTextColor;
	
	std::string AwardsBannerFooterImage;
	std::string AwardsBannerFooterText;
	std::string AwardsBannerFooterDescriptionText;
	std::string	AwardsBannerFooterTextColor;
	
	RtWeakPtr<ZombieSwapListData> ZombieSwapList;
};

#pragma mark
class PinataStyleChooserFactory
{
public:
	virtual ~PinataStyleChooserFactory() {};
	static PinataStyleChooserFactory& GetInstance();
	
	PinataStyleChooser& GetChooser();

protected:
    PinataStyleChooserFactory();
	PinataStyleChooser m_defaultChooser;
};

#endif /* defined(__PlantsVersusZombies2__PinataStyleChooserFactory__) */
