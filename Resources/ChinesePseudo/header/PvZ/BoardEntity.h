//
//  BoardEntity.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/2/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __BOARDENTITY_H__
#define __BOARDENTITY_H__

#include <string>

#include "Color.h"
#include "ComponentBase.h"
#include "Core.h"
#include "DamageInfo.h"
#include "RealObject.h"
#include "Point.h"
#include "Rect.h"
#include "Renderable.h"
#include "PVZTypes.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "TimeMgr.h"
#include "ZombieEnums.h"
#include "Projectile.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

typedef RtWeakPtr<class BoardEntity> BoardEntityPtr;

enum BoardEntityFlags
{
	PVZ_BEGIN_FLAG_ENUM(BEFLAG_),
	PVZ_FLAG(BEFLAG_IsCutsceneEntity),			// This entity is taking part in a gameplay demo of some sort, should not be included in metrics
	PVZ_FLAG(BEFLAG_HasPlayedImpactSound),		// Prevents impact sounds from being played multiple times in a frame by the same entity
	PVZ_FLAG(BEFLAG_CollisionRectIsValid),		// Clear this flag to have our collision rect get recalculated
	PVZ_END_FLAG_ENUM(BEFLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(BoardEntityFlags);

enum BoardEntityStatType
{
	BOARDENTITYSTATTYPE_DAMAGE,
	BOARDENTITYSTATTYPE_TOUGHNESS,
    BOARDENTITYSTATTYPE_ARMOR,
	BOARDENTITYSTATTYPE_RECHARGE,
    BOARDENTITYSTATTYPE_AREA,
    BOARDENTITYSTATTYPE_RANGE,
    BOARDENTITYSTATTYPE_SPEED,
    BOARDENTITYSTATTYPE_VARIABLE,
    BOARDENTITYSTATTYPE_RESISTENCE_INSTANTKILL,
    BOARDENTITYSTATTYPE_RESISTENCE_PHYSICAL,
    BOARDENTITYSTATTYPE_RESISTENCE_POISON,
    BOARDENTITYSTATTYPE_RESISTENCE_LIGHTNING,
    BOARDENTITYSTATTYPE_RESISTENCE_MAGIC,
    BOARDENTITYSTATTYPE_RESISTENCE_FROST,
    BOARDENTITYSTATTYPE_RESISTENCE_FLAME
};

enum BoardEntityStatValue
{
	BOARDENTITYSTATVALUE_DAMAGE0,
    BOARDENTITYSTATVALUE_DAMAGE1,
    BOARDENTITYSTATVALUE_DAMAGE2,
    BOARDENTITYSTATVALUE_DAMAGE3,
    BOARDENTITYSTATVALUE_DAMAGE4,
    BOARDENTITYSTATVALUE_DAMAGE5,
    BOARDENTITYSTATVALUE_DAMAGE6,
    BOARDENTITYSTATVALUE_RECHARGE0,
    BOARDENTITYSTATVALUE_RECHARGE1,
    BOARDENTITYSTATVALUE_RECHARGE2,
    BOARDENTITYSTATVALUE_RECHARGE3,
    BOARDENTITYSTATVALUE_RECHARGE4,
    BOARDENTITYSTATVALUE_ARMOR0,
    BOARDENTITYSTATVALUE_ARMOR1,
    BOARDENTITYSTATVALUE_ARMOR2,
    BOARDENTITYSTATVALUE_ARMOR3,
    BOARDENTITYSTATVALUE_SINGLE,
    BOARDENTITYSTATVALUE_SQUARE,
    BOARDENTITYSTATVALUE_1BY4,
    BOARDENTITYSTATVALUE_3BY2,
    BOARDENTITYSTATVALUE_3BY3,
    BOARDENTITYSTATVALUE_LANE,
    BOARDENTITYSTATVALUE_FULLBOARD,
    BOARDENTITYSTATVALUE_TOUCH,
    BOARDENTITYSTATVALUE_CLOSE,
    BOARDENTITYSTATVALUE_3TILES,
    BOARDENTITYSTATVALUE_STRAIGHT,
    BOARDENTITYSTATVALUE_LOBBED,
    BOARDENTITYSTATVALUE_FRONTBACK,
    BOARDENTITYSTATVALUE_MULTIHIT,
    BOARDENTITYSTATVALUE_MULTILANE,
    BOARDENTITYSTATVALUE_5WAY,
    BOARDENTITYSTATVALUE_TOUGHNESS0,
    BOARDENTITYSTATVALUE_TOUGHNESS1,
    BOARDENTITYSTATVALUE_TOUGHNESS2,
    BOARDENTITYSTATVALUE_TOUGHNESS3,
    BOARDENTITYSTATVALUE_TOUGHNESS4,
    BOARDENTITYSTATVALUE_TOUGHNESS5,
    BOARDENTITYSTATVALUE_TOUGHNESS6,
    BOARDENTITYSTATVALUE_TOUGHNESS7,
    BOARDENTITYSTATVALUE_TOUGHNESS8,
    BOARDENTITYSTATVALUE_SPEED0,
    BOARDENTITYSTATVALUE_SPEED1,
    BOARDENTITYSTATVALUE_SPEED2,
    BOARDENTITYSTATVALUE_SPEED3,
    BOARDENTITYSTATVALUE_SPEED4,
    BOARDENTITYSTATVALUE_SPEED5,
    BOARDENTITYSTATVALUE_4WAY,
    BOARDENTITYSTATVALUE_VARIABLE,
    BOARDENTITYSTATVALUE_D,
    BOARDENTITYSTATVALUE_C,
    BOARDENTITYSTATVALUE_B,
    BOARDENTITYSTATVALUE_A,
    BOARDENTITYSTATVALUE_S,
    BOARDENTITYSTATVALUE_SS
};

struct BoardEntityStat
{
	BoardEntityStatType Type;
	BoardEntityStatValue Value;
};


struct BoardEntityBuffInfo
{
    int     buffID;
    int     damage;
//    float   everyTriggerTime;
    float   lastHitTime;
    float   endedTime;
    
    BoardEntityBuffInfo():buffID(-1),damage(0),endedTime(0),lastHitTime(0){};
};

// An abstract concept of height, allowing for some amount of emergent interaction between entities
//		On_Ground	- Ground-hugging entities, like Spikeweed. Most Zombies walk over them.
//		Low			- Short entities, like PotatoMine. Some high Zombie attacks will miss them.
//		Normal		- Sunflower height! No special properties.
//		Tall		- Will block some flying / launched Zombies. Tallnut is tall.
enum BoardEntityHeight
{
	ENTITYHEIGHT_ON_GROUND,
	ENTITYHEIGHT_LOW,
	ENTITYHEIGHT_NORMAL,
	ENTITYHEIGHT_TALL
};

class BoardEntity : public RealObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(BoardEntity, RealObject, RtClass);

protected:
	BoardEntity();
public:
	virtual ~BoardEntity();

	// PlaceOnBoard
	//	- Sets our initial location
	//	- Calls virtual onPlaceOnBoard()
	void PlaceOnBoard(const SexyVector3& i_position);
	// Update
	//	- Calls virtual onUpdate()
	void Update();
	void Draw(class Sexy::Graphics* i_g) override;

	// TakeDamage
	//	- Up to the derived class to handle the incoming damage as it sees fit,
	// no hitpoints are stored in the base class
	virtual void TakeDamage(const DamageInfo& i_damage) {}
	virtual void TakeDamageNoInvincible(const DamageInfo& i_damage) {}
	virtual void TakeFatalDamage(const DamageInfo& i_damage) {}
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return true; }
    virtual bool NeutralizeSplashDamage() { return false; }
    
    virtual void NotifyDamagedEntity(BoardEntity *entity) {}
    virtual bool TryApplyDamageToEntity(DamageInfo &damageInfo, BoardEntity *entity) { return false; }
    virtual void NotifyComponentOwner() {}

	//Healing
	virtual void HealByAmount(float amount);
	
	// Shovel
	// - Removes object via 'shoveling' it
	// - Override to implement shoveling
	// - Returns amount of sun this object is worth to 'sell'
	virtual int Shovel() { return 0; }
	virtual bool CanBeShoveled() { return false; }
	
	// Gravestone blocking
	virtual bool BlocksGravestoneSpawning() { return false; }

	// OverrideProjectileCollision
	//	- Called immediately before normal projectile collision handling
	//	- Return 'true' if you want the collision to be ignored by the Projectile, or
	//	if you have handled the collision yourself
	virtual bool OverrideProjectileCollision(class Projectile* i_projectile);

	// GetRenderOrder
	//	- PROBABLY WON'T STICK AROUND!
	//	- Attempts to build a valid render order from just our position
	//	- Override this if you need better control
	virtual int GetRenderOrder() const override { return CalcRenderOrder(); }
	virtual int CalcRenderOrder() const override;
	static int CalcRenderOrderFromPosition(const SexyVector3& i_position);
	
	virtual const Sexy::Rect & GetCollisionRect();

	// GetEntityHeight
	//	- Returns our BoardEntityHeight value (see comments above the enum for more info)
	//	- Must be implemented by each derived class, returns 'Normal' by default
	virtual BoardEntityHeight GetEntityHeight() const;

	/// Accessors
	inline bool			HasPlayedImpactSound() const;
	inline void			SetHasPlayedImpactSound(const bool i_hasPlayedImpactSound);

	inline bool			IsCutsceneEntity() const;
	inline void			SetIsCutsceneEntity(const bool i_isCutsceneEntity);
	
	void				SetPosition(const SexyVector3& i_newPosition) override;
	void				MovePosition(const SexyVector3& i_translation);

	virtual BoardEntityTypeFlag	GetBoardEntityType() { return ENTITYTYPE_OTHERBOARDENTITIES; }

	// CalcGridFootprint
	//	- Uses m_position and GetGridExtents() to build a rectangle containing
	//	the grid squares that we lie within
	virtual Sexy::Rect CalcGridFootprint() const;

	// CalcGridPosition
	//	- Ignores our GridExtents and returns the grid square that our m_position resides in
	//	- Similarly, CalcRowPosition and CalcColumnPosition use our m_position for their return value
	Sexy::Point CalcGridPosition() const;
	int CalcRowPosition() const;
	int CalcColumnPosition() const;
	
    bool IsInRow(int i_row) const;
    bool IsInCol(int i_col) const;

	bool IntersectsGrid();
    
    bool IsOnScreen();
	
    //PVZ2_CHINESE_START
    bool 	GetIsIntro() const { return m_bIsIntro; }
	void 	SetIsIntro(bool i_IsIntro) { m_bIsIntro = i_IsIntro; }
    
    void    SetShowHealthBar(bool i_showHealthBar) { m_bShowHealthBar = i_showHealthBar; }
    
    //PVZ2_CHINESE_END
	int		GetCurrentLevel() const { return m_currentLevel; }
	virtual void	SetCurrentLevel(int i_level){ m_currentLevel = i_level; }

	virtual bool CanLevelUp(int i_targetLevel) { return true; }
	void	LevelUp(int i_targetLevel);
	virtual void onLevelUp(int i_targetLevel);
	virtual void onLevelUpFailed(int i_targetLevel) {}

	bool	HasBeHitted(RtWeakPtr<class Projectile> i_projectile);
	void	SetHitted(RtWeakPtr<class Projectile> i_projectile);
    
    BoardEntityBuffInfo     burnDebuff;
    
    static bool BoardEntityLeftToRightSortFunc(BoardEntity *i_a, BoardEntity *i_b);
	static bool BoardEntityRightToLeftSortFunc(BoardEntity *i_a, BoardEntity *i_b);
    
    ComponentRunner& GetComponentRunner() { return *m_componentRunner; }
    
    void SetIsTransparent(bool bTransparent) { m_bTransparent = bTransparent; }
    bool GetIsTransparent() { return m_bTransparent;  }

    virtual bool HasGravity() { return false; }
protected:
	inline void invalidateCollisionRect();

	void onPostLoad() override;
	void onInitialized() override;

	/// Virtual Interface
	virtual void onPlaceOnBoard() 
	{}
	virtual void onUpdate()
	{}
	virtual void CreateLevelEffect()
	{}
   
	int  m_currentLevel;
    
    bool m_bShowHealthBar;

private:
	
    // Serialized
	Sexy::Rect          m_collisionRect;
    BoardEntityFlags	m_boardEntityFlags;
	RtWeakPtr<ComponentRunner>		m_componentRunner;
    
    bool m_bIsIntro;
    bool m_inPooyan;
    std::vector<RtWeakPtr<class Projectile> > m_hitProjectiles;
    bool m_bTransparent;
};

/// Inlines

inline bool BoardEntity::IsCutsceneEntity() const
{
	return TestFlag(m_boardEntityFlags, BEFLAG_IsCutsceneEntity);
}

inline void BoardEntity::SetIsCutsceneEntity(const bool i_isCutsceneEntity)
{
	SetFlag(m_boardEntityFlags, BEFLAG_IsCutsceneEntity, i_isCutsceneEntity);
}

inline bool	BoardEntity::HasPlayedImpactSound() const
{
	return TestFlag(m_boardEntityFlags, BEFLAG_HasPlayedImpactSound);
}

inline void BoardEntity::SetHasPlayedImpactSound(const bool i_hasPlayedImpactSound)
{
	SetFlag(m_boardEntityFlags, BEFLAG_HasPlayedImpactSound, i_hasPlayedImpactSound);
}

inline void BoardEntity::invalidateCollisionRect()
{
	SetFlag(m_boardEntityFlags, BEFLAG_CollisionRectIsValid, false);
}

#endif
