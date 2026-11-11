//
//  SeedPacket.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  Displays a plant that can be planted. Is typically a child of a seed bank. When attached
//  to a seedbank, the art that is drawn will be on an atlas that the seed bank controls.
//

#ifndef __SEEDPACKET_H__
#define __SEEDPACKET_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "PlantEnums.h"
#include "PrimeTextWidget.h"
#include "SeedPacketUtils.h"
#include "ObjectTypeDescriptor.h"

class Plant;

enum SeedPacketFlags
{
	PVZ_BEGIN_FLAG_ENUM(PACKETFLAG_),
	
	// AFFORDABLE
	//	- Set when seed packet is affordable due to having enough sun.
	PVZ_FLAG(PACKETFLAG_AFFORDABLE),

	// DISABLED
	//	- Set when seed packet is to be always grayed out and not clickable.
	PVZ_FLAG(PACKETFLAG_DISABLED),
	
	// BLACKLISTED
	//  - Set when a seed packet should be grayed out with a lock and not clickable.
	PVZ_FLAG(PACKETFLAG_BLACKLISTED),

	// ALWAYS_PLANTABLE
	//	- Set when seed packet is always plantable, even if it is on cooldown or there isn't enough sun.
	//    Useful for the conveyor belt and inventory-based packet count.
	PVZ_FLAG(PACKETFLAG_ALWAYS_PLANTABLE),

	// ON_DISPLAY
	//	- Set when seed packet is to be fully lit, but not really plantable. Used for the seed chooser screen
	//    and when the seed bank is traveling around during the level intro.
	PVZ_FLAG(PACKETFLAG_ON_DISPLAY),

	// FREE_PLANT
	//	- Set when seed packet is in free plant mode. Cheat related
	PVZ_FLAG(PACKETFLAG_FREE_PLANT),
	
	// FLASHING
	// - Set when you want the seed packet to flash. Used for tutorials, usually.
	PVZ_FLAG(PACKETFLAG_FLASHING),
	
	// SELECTED
	// - Set when you want the seed packet to be selected, but not pressed. Used for seed chooser
	PVZ_FLAG(PACKETFLAG_SELECTED),
	
	// IMITATER
	// - Special flag for packets that contain Imitater'ed plants
	PVZ_FLAG(PACKETFLAG_IMITATER),

	// PURCHASABLE
	// - Set when you can purchase this plant from the seed chooser
	PVZ_FLAG(PACKETFLAG_PURCHASABLE),

	// FAVORITE
	// - Set when it is a favorite (specially sorted) plant
	PVZ_FLAG(PACKETFLAG_FAVORITE),
	
	PVZ_END_FLAG_ENUM(PACKETFLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(SeedPacketFlags);

class SeedPacket : public UIWidget
{
public:
	RT_CLASS_DEFINE(SeedPacket, UIWidget, RtClass);	
	
	SeedPacket();
	virtual ~SeedPacket();
	
	// Public Interface (Inheritable)
	
	virtual void				Draw(Graphics* i_g) override;
	virtual bool				IsUsable();
	virtual void				SetPlantType(const PlantTypePtr i_plantType);
    virtual void				SetZombieType(const ZombieTypePtr i_zombieType);
    virtual void                SetGridItemType(const GridItemTypePtr i_gridItemType);

	virtual bool				OnTouch(const Sexy::Touch& i_touch) override;
    virtual const Sexy::Rect	GetHitRect() override;

    void SetScale(float i_scale) { m_scale = i_scale; }
    float GetScale() { return m_scale; }
	
	// Public Interface (Core)
    void                    SetHitInsets(const Insets& val);
	void						InitializeTimer();
	void						SetToReady();

	const PlantTypePtr			GetPlantType();
	const PlantTypePtr 			GetPlantTypeOrImitater();
    const ZombieTypePtr			GetZombieType();
    const GridItemTypePtr       GetGridItemType();
    
    virtual const PacketRenderData& GetZombieRenderData();

    virtual const ObjectTypeDescriptorPtr GetSeedType();
    void                        SetSeedType(const ObjectTypeDescriptorPtr i_seedType);
    bool                        IsEmpty();
    void                        SetPacketsPrefix(const std::string& prefix);
    const std::string&          GetPacketsPrefix() const { return m_packetsPrefix; }
	
	inline void					SetContentsTypeName(const std::string& i_type);
	const std::string&			GetContentsTypeName() const;
	
	inline virtual bool			IsAffordable();
    inline void					setAffordable(bool i_isAffordable);

	inline void					SetOnDisplay(bool i_isOnDisplay);
	inline bool					IsOnDisplay();

	inline void					SetDisabled(bool i_isDisabled);
	inline bool					IsDisabled();

	inline void					SetBlacklisted(bool i_isBlacklisted);
	inline bool					IsBlacklisted();

	inline void					SetPurchasable(bool i_isPurchasable);
	inline bool					IsPurchasable();
	
	inline void					SetAlwaysPlantable(bool i_isAlwaysPlantable);
	
	inline void					SetIsFlashing(bool i_isFlashing);
	inline bool					IsFlashing();

	inline void					SetFavorite(bool i_isFavorite);
	inline bool					IsFavorite();
	
	inline void					SetIsSelected(bool i_isSelected);
	inline bool					IsSelected();
	
	inline void					SetIsImitater(bool i_isImitater);
	inline bool					IsImitater();

	void						SetUsesCooldownTimer(const bool i_usesCooldownTimer) { m_usesCooldownTimer = i_usesCooldownTimer; }
	
	void						SetLockedDuringLastStandSetup(bool i_locked) { m_lockedDuringLastStandSetup = i_locked; }
    
    int                         GetPlantLevel() const { return m_iPlantLevel; }
    
    int                         GetPlantAvatar() const { return m_iPlantAvatar; }
    
    void                        SetPlantAvatarAndLevel(int iLevel = -1, int iAvatar = -1);

    bool						GetBoostIsActive() { return m_useBoostedBackground; }

    void						onAccessoryActionComplete();
    
    void                        SetIsPlantTrialPacket(bool bPlantTrial) { m_bPlantTrialSeed = bPlantTrial; }
	void							SetPlantTrialTimes(int times) { m_iPlantTrialTimes = times; }
	bool							GetIsPlantTrialForFree() const;

	void						SetFreePlant();
	bool						IsFreePlant();
    
    bool                        IsPressState();

    virtual bool                TryUse(class PacketCursor* pCursor) { return false; }
    virtual void                CopyFrom(SeedPacket* pCopy);
    
    void                        PlayCardAffordEffect();
    
    void                        PlayWordAffordEffect(int iOffsetX = 0, int iOffsetY = 0);
    void                        CheckResourceLoaded();
    void                        ShowBoarderEffect(bool show);

	bool 						IsShowExpHit();
	void						setIsNeedShowExpTip(bool bIsNeedShowExpTip);
protected:
	
	// Protected Interface (Inheritable)

	OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
	OVERRIDE_STATE_ONENTER(WidgetState, NotReady);
	OVERRIDE_STATE_UPDATE(WidgetState, NotReady);
	OVERRIDE_STATE_ONENTER(WidgetState, Ready);
	OVERRIDE_STATE_ONENTER(WidgetState, Pressed);
	OVERRIDE_STATE_ONEXIT(WidgetState, Pressed);

	virtual void				onCheatEnabled();
	virtual void				onCheatDisabled();
	virtual void				onSunCurrencyChanged(SunCurrency i_upcomingAmount);
	virtual void				onSeedPacketPlanted(SeedPacket* i_packet);
    virtual void                onSunClicked(class CollectableSun* i_sun, SunCurrency i_upcomingAmount);
	virtual void				onCursorDestroyed(class BaseCursor* i_cursor);
	void 						onGameplayEnded();
	void						onPlantCostChanged(Plant* i_plant, int i_newCost);
	void						onPlantDieCostChanged(Plant* i_plant, int i_newCost);

	virtual void				initLoadingResourcesGroupList() override;
	virtual void				registerForEvents() override;
	virtual void				unregisterForEvents() override;
    virtual void				onUpdate() override;
	// Protected Interface (core)
	
	virtual void					updateAffordability(const SunCurrency i_newSunCurrency);
	inline bool					isAlwaysPlantable();
    
	virtual void                InitText();
    
    void                        DrawRenderData(Graphics* i_g, const PacketRenderData& renderData);
    virtual void                DrawText(Graphics* i_g);
	void						drawPlantFavoriteIcon(Graphics* i_g, Image* i_atlasImage, const PacketRenderData& i_renderData);
    virtual SunCurrency         GetSunCost();
private:
    
    class Effect_PopAnim*       CreateAffordEffect(const std::string& strAnim
                                                   , const std::string& strLabel
                                                   , int iX, int iY
                                                   , int iOffsetX = 0, int iOffsetY = 0);

protected:

    // Protected Members (serialized)
    PlantTypePtr				m_plantType;
    GridItemTypePtr				m_gridItemType;
    ZombieTypePtr               m_zombieType;
    
    int							m_plantLevel;// for special mode level.

	std::string					m_contentsTypeName;
	SeedPacketFlags				m_packetFlags;
	pvztime_t					m_cooldownEndTime;
	bool						m_usesCooldownTimer;
	bool						m_lockedDuringLastStandSetup;
    
	Sexy::PrimeTextWidget*      m_costTextWidget;
	bool						m_useBoostedBackground;
    std::string                 m_packetsPrefix;
    Insets                        m_hitInsets;

private:
	int							m_reducedCost;
    int                         m_iPlantLevel;
    int                         m_iPlantAvatar;

    int							m_boostPower;

    float						m_extraReducedCooldown;
    float						m_specialReducedCooldown;
    float 						m_rateClearPlantingCD;
    bool                        m_bPlantTrialSeed;
	int							m_iPlantTrialTimes;
    bool                        m_bResLoaded = false;
    class Effect_PopAnim*       m_borderEffect;

	bool m_bIsNeedShowExpTip;
	float m_scale;
};

namespace Message
{
	void SeedPacketTypeChanged(SeedPacket* i_packet);
    void ZombieSeedPacketSelected(SeedPacket* i_packet);
    void BeghouledPlantUpgraded(std::string& i_plantName);
}

inline void SeedPacket::setAffordable(bool i_isAffordable)
{
	SetFlag(m_packetFlags, PACKETFLAG_AFFORDABLE, i_isAffordable);
}

inline bool SeedPacket::IsAffordable()
{
	// We are affordable if we are, or if we're always plantable.
	bool isAffordable = (isAlwaysPlantable() || TestFlag(m_packetFlags, PACKETFLAG_AFFORDABLE));
	isAffordable |= (m_bPlantTrialSeed && m_iPlantTrialTimes > 0);
	return isAffordable;
}

inline void	SeedPacket::SetOnDisplay(bool i_isOnDisplay)
{
	SetFlag(m_packetFlags, PACKETFLAG_ON_DISPLAY, i_isOnDisplay);
}

inline bool SeedPacket::IsOnDisplay()
{
	return TestFlag(m_packetFlags, PACKETFLAG_ON_DISPLAY);
}

inline bool SeedPacket::IsDisabled()
{
	return TestFlag(m_packetFlags, PACKETFLAG_DISABLED);
}

inline void	SeedPacket::SetDisabled(bool i_isDisabled)
{
    SetFlag(m_packetFlags, PACKETFLAG_DISABLED, i_isDisabled);
}

inline void	SeedPacket::SetBlacklisted(bool i_isBlacklisted)
{
	SetFlag(m_packetFlags, PACKETFLAG_BLACKLISTED, i_isBlacklisted);
}

inline bool SeedPacket::IsBlacklisted()
{
	return TestFlag(m_packetFlags, PACKETFLAG_BLACKLISTED);
}

inline void SeedPacket::SetPurchasable(bool i_isPurchasable)
{
	SetFlag(m_packetFlags, PACKETFLAG_PURCHASABLE, i_isPurchasable);
}

inline bool SeedPacket::IsPurchasable()
{
	return TestFlag(m_packetFlags, PACKETFLAG_PURCHASABLE);
}

inline void SeedPacket::SetIsFlashing(bool i_isFlashing)
{
	SetFlag(m_packetFlags, PACKETFLAG_FLASHING, i_isFlashing);
}


inline bool SeedPacket::IsFlashing()
{
	return TestFlag(m_packetFlags, PACKETFLAG_FLASHING);
}

inline void SeedPacket::SetIsSelected(bool i_isSelected)
{
	SetFlag(m_packetFlags, PACKETFLAG_SELECTED, i_isSelected);
}

inline bool SeedPacket::IsSelected()
{
	return TestFlag(m_packetFlags, PACKETFLAG_SELECTED);
}

inline void SeedPacket::SetIsImitater(bool i_isImitater)
{
	SetFlag(m_packetFlags, PACKETFLAG_IMITATER, i_isImitater);
}

inline bool SeedPacket::IsImitater()
{
	return TestFlag(m_packetFlags, PACKETFLAG_IMITATER);
}

inline bool SeedPacket::isAlwaysPlantable()
{
	return (TestFlag(m_packetFlags, PACKETFLAG_ALWAYS_PLANTABLE) || TestFlag(m_packetFlags, PACKETFLAG_FREE_PLANT));
}

inline void	SeedPacket::SetAlwaysPlantable(bool i_isAlwaysPlantable)
{
	SetFlag(m_packetFlags, PACKETFLAG_ALWAYS_PLANTABLE, i_isAlwaysPlantable);
}

inline void SeedPacket::SetContentsTypeName(const std::string &i_type)
{
	m_contentsTypeName = i_type;
}

inline void SeedPacket::SetFavorite(bool i_isFavorite)
{
	SetFlag(m_packetFlags, PACKETFLAG_FAVORITE, i_isFavorite);
}

inline bool SeedPacket::IsFavorite()
{
	return TestFlag(m_packetFlags, PACKETFLAG_FAVORITE);
}

typedef RtWeakPtr<SeedPacket> SeedPacketPtr;

#endif //__SEEDPACKET_H__



