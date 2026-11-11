//
//  FishingModule.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.7.7
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__FishingModule__
#define __PlantsVersusZombies2__FishingModule__

#include <stdio.h>
#include "LevelModule.h"
#include "ReviveUI.h"
#include "UIWidget.h"
#include "InitialGridItemPlacer.h"
#include "Zombie.h"
#include "Plant.h"
#include "ChallengeUI.h"
#include "PopAnimRig.h"
#include "SkyCannonTypeUI.h"


enum FishingSpecialType
{
	FishingSpecial_None,
	FishingSpecial_HighScore,
	FishingSpecial_Crazy,
};

struct FishingZombieInfo
{
	FishingZombieInfo()
		: Scale(1.0f)
		, Score(10)
		, Speed(0.3f)
		, SpecialType(0)
	{}
	ZombieTypePtr	Type;
	SexyVector2		Offset;
	float						Scale;	
	int						Score;
	float						Speed;
	int						SpecialType;
};

enum FishingActiveCondition
{
	PVZ_BEGIN_ENUM(FishingActive_),
	FishingActive_Weight,
	FishingActive_Time,
	FishingActive_Wave,
	FishingActive_Num,
	PVZ_END_ENUM(FishingActive_)
};

struct FishingZombieGroup
{
	std::string										GroupName;
	FishingActiveCondition				ActiveCondition;
	float													ActiveValue;
	std::vector<FishingZombieInfo>	Zombies;
	std::vector<std::string> DisabledPathTypes;

	// these are not saved in json
	float													NextTime;
	int													NextNum;

	FishingZombieGroup()
		: ActiveCondition(FishingActive_Weight)
		, ActiveValue(100)
		, NextTime(PVZ_EOT())
		, NextNum(0)
	{}
	bool HasSpecialZombie(int specialType) const;
};
typedef std::vector<FishingZombieGroup> VecFishingZGroup;

struct FishingPath
{
	std::string PathType;
	std::vector<SexyVector2> PathPoints;
};

//-------------------------------------------------------------------------------------------------------
enum FishingState
{
	FishingState_Normal,
	FishingState_End,		// won or failed
	FishingState_Editor,
};

//-------------------------------------------------------------------------------------------------------
namespace Message
{
	void FishingTutorial_CheckTouch(const Sexy::Touch& i_touch, bool* pCanTouch);
}


//-------------------------------------------------------------------------------------------------------
class FishingModule : public LevelModule
{
public:
	struct ZombieInfo
	{
		ZombiePtr	m_zombiePtr;
		int				m_score;
		//int				m_energy;
		int				m_special;
		ZombieInfo() : m_score(0), m_special(0) {}
	};
	typedef std::vector<ZombieInfo> VecZombieInfo;
public:
    RT_CLASS_DEFINE(FishingModule, LevelModule, RtClass);
    FishingModule();
    ~FishingModule();

	virtual void					AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
	bool								SpawnZombieGroup(Sexy::Point boardStartPos, const FishingZombieGroup* pGroup, const FishingPath* pPath);
	void								SpawnNextZombies();
	const FishingPath*	GetRandomPath(std::vector<std::string>* pDisabledPaths = NULL);
	Sexy::Point					GetRandomStartPos();		// return board position
	int								GetCannonEnergy(int level);
	int								GetCannonDamage(int level);
	int								GetCannonCoolDown(int level);
	void								SetFishingState(FishingState iState);
	void								FireAt(const Sexy::Point &i_boardSpace);
	void								SetCannonLevel(int level);
	int								GetCannonLevel();

	void								AddZombieInfo(const ZombieInfo& info);
	void								SetTutorial(bool setting) { m_bTutorial = setting; }
	bool								IsTutorial() const { return m_bTutorial; }
	SexyVector3				GetCannonFirePos(int level);

	void								InvalidUI();
	void								ArrangeUI();

protected:
    virtual void					initializeModule() override;
    virtual void					registerForEvents() override;
    virtual void					unregisterForEvents() override;
    //virtual void postInitialize();

	void								RefreshZGroupTypes();
	void								RemoveZombieInfo(Zombie* zombie);
	void								RemoveAllZombie();
	VecZombieInfo::iterator GetZombieInfo(Zombie* zombie);
	bool								IsEnergyEnough();
	bool								IsInCrazy();
	bool								IsCannonReady();
	void								SetCrazy(bool setting, bool bResetTime = true);
	bool								IsInHighScore();
	void								SetHighScore(bool setting);

	void								ChangeCannon();
	void								UpdateCannon();

	// delegate
protected:
	void onAddToRenderQueue(class RenderQueue* i_queue);
	void onRenderBackground(Graphics* i_g);
	bool onHandleTouch(const Sexy::Touch& i_touch);
	void onCancelTouch();
	bool onCheckWin();
	void onUpdate();
	void onLoadComplete();
	void onLevelStarted();
	void onGameplayStarted();
	bool onCanPreventSave() { return true; }
	void onSkyCannonTypeSelected(int i_typeID);
	void onZombieEndWillPath(Zombie* i_zombie);
	void onZombieDestroyed(Zombie* i_zombie);
	void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void onCheckBuySunManually(bool* pIsManually);
	void onReviveSucceed();
	void onReviveClose();
	void onCannonFireAnimCommand(const std::string& i_animLabel);
	void onGameplayEnded();

protected:
	Sexy::TouchID						m_touchIdent;
	bool											m_bTutorial;
	bool											m_bValidUI;
	bool											m_bHighScore;
	ImagePtr									m_backImage;
	std::vector<RtWeakPtr<SkyCannonTypeUI>>	m_CannonTypes;
	int											m_waves;
	FishingState							m_fishingState;
	pvztime_t								m_timerSpawnNext;
	pvztime_t								m_timerCannonHit;
	pvztime_t								m_timerCrazy;
	pvztime_t								m_timerCannonFrom;		// cannon change
	pvztime_t								m_timerCannonTo;		// cannon change
	pvztime_t								m_timerCoolDown;
	UIWidgetPtr							m_sunCounterUI;
	
	typedef std::map < FishingActiveCondition, VecFishingZGroup > MapZGroupTypes;
	MapZGroupTypes					m_MapZGroupTypes;
	VecZombieInfo						m_zombiesCache;

	RtWeakPtr<class Effect_PopAnim> m_airscrewEffect;
	RtWeakPtr<class Effect_PlayFrame> m_cannonEffect;
	RtWeakPtr<class Effect_PopAnim> m_crazyEffect;
	RtWeakPtr<class Effect_PopAnim> m_crazyCannonEffect;
	int											m_cannonLevel;
	SexyVector3							m_laserBeginPos;
	SexyVector3							m_laserEndPos;
};

//-------------------------------------------------------------------------------------------------------
struct CannonData
{
	int CannonType;
	int Energy;
	int Damage;
	int CoolDown;
	bool Visible;
	CannonData() : CannonType(0), CoolDown(1.0f), Damage(10), Energy(10), Visible(true)
	{}
};

struct FishingZombieInitData
{
	ZombieTypePtr	Type;
	int						Hitpoints;
};
class FishingProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(FishingProperties, LevelModuleProperties, RtClass);
    virtual RtClass* GetModuleClass() const override
    {
        return FishingModule::StaticGetClass();
    }
	FishingProperties();

	CannonData	GetCannonData(int cannon) const;
	int					GetHitpoints(ZombieTypePtr i_type) const;
	
public:
	int		InitScore;
	int		MaxScore;
	
	int		WaveNumMin;
	int		WaveNumMax;
	float		WaveRefreshTime;

	std::vector<CannonData> CannonProps;
	std::vector<FishingZombieGroup> ZombieGroups;
	std::vector<FishingPath> Paths;
	std::vector<FishingZombieInitData> ZombieInitDatas;
};


#endif /* defined(__PlantsVersusZombies2__FishingModule__) */
