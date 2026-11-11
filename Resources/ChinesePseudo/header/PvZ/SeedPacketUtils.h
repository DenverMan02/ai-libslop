//
//  SeedPacketUtils.h
//  PlantsVersusZombies2
//
//  Created by jsola on 2/20/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_SeedPacketUtils_h
#define PlantsVersusZombies2_SeedPacketUtils_h

#include "Core.h"

class SeedPacketUtils;

struct PacketRenderData
{
	ImagePtr		ContentsImage;
	Sexy::Rect		ContentsSrcRect;
	Sexy::Point		ContentsImageOffset;
	Sexy::Rect		BackgroundSrcRect;
	Sexy::Point		BackgroundImageOffset;
	Sexy::Rect		BoostedBackgroundSrcRect;
	Sexy::Point		BoostedBackgroundImageOffset;
	Sexy::Rect		BorderNormalSrcRect;
	Sexy::Point		BorderNormalImageOffset;
	Sexy::Rect		BorderHighlightSrcRect;
	Sexy::Point		BorderHighlightImageOffset;
	Sexy::Rect		LockedSrcRect;
    
	Sexy::Point		LockedImageOffset;
	Sexy::Rect		CooldownSrcRect;
	Sexy::Point		CooldownImageOffset;
    
    Sexy::Rect		DotsLeftSrcRect;
	Sexy::Point		DotsLeftImageOffset;
    Sexy::Rect		DotsRightSrcRect;
	Sexy::Point		DotsRightImageOffset;
    Sexy::Rect		DotsBottomSrcRect;
	Sexy::Point		DotsBottomImageOffset;
    
    Sexy::Rect		PriceTabSrcRect;
	Sexy::Point		PriceTabImageOffset;
    Sexy::Rect		PriceTabSelectedSrcRect;
	Sexy::Point		PriceTabSelectedImageOffset;

	Sexy::Rect		SelectBoxSrcRect;
	Sexy::Point		SelectBoxImageOffset;

	Sexy::Rect		LevelFrameSrcRect;
	Sexy::Point		LevelFrameImageOffset;

	Sexy::Rect		ProfessionSrcRect;
	Sexy::Point		ProfessionImageOffset;
    
	ImagePtr		AtlasImage;
    
private:
    friend class SeedPacketUtils;
    
    bool            IsStale; // if true, then this cached data should be cleared and refreshed.
};

struct RenderDataEx
{
    std::string strName;
    int iLevel;
    int iAvatar;
    
    bool operator < (const RenderDataEx& op) const
    {
        if (strName < op.strName)
        {
            return true;
        }
        else if (strName == op.strName)
        {
            if (iLevel < op.iLevel)
            {
                return true;
            }
            else if (iLevel == op.iLevel)
            {
                return iAvatar < op.iAvatar;
            }
        }
        
        return false;
    }
};

class SeedPacketUtils : public LazySingleton<SeedPacketUtils>
{
public:
	const PacketRenderData& GetPlantPacketRenderData(const std::string& i_plantName, int iLevel = -1, int iAvatar = -1, int i_profession = -1);
    const PacketRenderData& GetGridItemPacketRenderData(const std::string& i_plantName, int iLevel = -1, int iAvatar = -1);
    const PacketRenderData& GetZombiePacketRenderData(const std::string& i_zombieName, const std::string& prefix = "", int i_rare = -1);
	const PacketRenderData& GetPowerupPacketRenderData(const std::string& i_powerupName);
	const PacketRenderData& GetToolPacketRenderData(const std::string& i_toolName);
    const PacketRenderData& GetPlantFoodRenderData();
    const PacketRenderData& GetLevelEditorRenderData(const std::string& i_typeName);
    
    const PacketRenderData& GetPlantPiecePacketRenderData(const std::string& i_Name);

    void                    InvalidateCachedPacketRenderData();
    
    DeviceImage*			CreateDeviceImageForSeedPacket(const PacketRenderData& i_renderData, int i_targetWidth = 0, int i_targetHeight = 0);
	void					DrawPacketToDeviceImage(DeviceImage* i_image, const PacketRenderData& i_renderData, bool i_drawSelectionBorder, int i_drawCost = -1, bool i_drawLevel = false, bool i_drawProfession = false);
	void					DrawPacket(Graphics* i_g, const PacketRenderData& i_renderData, bool i_drawSelectionBorder, int i_drawCost = -1, bool i_drawLevel = false, bool i_drawProfession = false);

	void					DrawPacketToDeviceImageNoBackground(DeviceImage* i_image, const PacketRenderData& i_renderData, bool i_drawSelectionBorder, int i_drawCost = -1);
	void					DrawPacketNoBackground(Graphics* i_g, const PacketRenderData& i_renderData, bool i_drawSelectionBorder, int i_drawCost = -1);
    
    Sexy::Point         GetZombiePacketSize(const std::string& prefix = "");
    
private:
	void fillRenderData(PacketRenderData& o_renderData, ImagePtr i_contentsImage, ImagePtr i_bottomImage, ImagePtr i_topImage,
		ImagePtr i_selectedImage, ImagePtr i_lockedImage, ImagePtr i_cooldownImage, ImagePtr i_dotsLeftImage = ImagePtr(), ImagePtr i_dotsBottomImage = ImagePtr(), ImagePtr i_dotsRightImage = ImagePtr()
                        , ImagePtr i_priceTabImage = ImagePtr(), ImagePtr i_priceTabSelectedImage = ImagePtr(), ImagePtr i_selectBoxImage = ImagePtr(), ImagePtr i_levelFrameImage = ImagePtr(), ImagePtr i_boostedBackgroundImage = ImagePtr(),
                        ImagePtr i_professionImage = ImagePtr()) const;
    
	typedef std::map<RenderDataEx, PacketRenderData> PacketRenderDataMap;
	typedef PacketRenderDataMap::iterator PacketRenderDataIterator;
	
	PacketRenderDataMap m_renderData;
};

#endif
