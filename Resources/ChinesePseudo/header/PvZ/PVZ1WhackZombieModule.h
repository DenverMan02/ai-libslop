// PVZ1WhackZombieModule.h
// create by lfy
// 2023.12.26


#ifndef __PVZ1WHACKZOMBIEMODULE_H__
#define __PVZ1WHACKZOMBIEMODULE_H__

#include "LevelModule.h"
#include "Wave.h"
#include "BoardEnums.h"
#include "GridItem.h"
#include "Zombie.h"
#include "EffectObject.h"
#include "Utils.h"
#include "ZombieBasic.h"
#include "GravestoneAnimRig.h"



namespace WhackZombieUtils
{
    bool IsPlayingWhackZombie();
};


class PVZ1WhackZombieModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(PVZ1WhackZombieModule, LevelModule, RtClass);
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    PVZ1WhackZombieModule() {}
    void GameplayStarted();
    void GameplayEnded();
    void    onAnimStopped(const std::string &i_animName);
    void DoThrowSkiTools(int splatPosX, int splatPosY);
    void    handleTouchDown(int i_screenX, int i_screenY);
    void onUpdate();

protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
    // virtual void unregisterForEvents() override;
private:
	bool onTouchEvent(const Sexy::Touch& i_touch);
	void onCancelEvent();
    void onZombieDestroyed(Zombie *i_zombie);
private:
	bool m_bCanTouch = true;

	bool m_bIsGameStarted  = true;
    Effect_PopAnim* m_pHammerEffect;

};

class PVZ1NewWhackZombieMinigameProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PVZ1NewWhackZombieMinigameProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return PVZ1WhackZombieModule::StaticGetClass();
	}

public:
    float coin_silver;
    float coin_gold;
    float Producersun;
    int Zombie_tutorial_SunCount;
    int Zombie_armor1_SunCount;
    int Zombie_armor2_SunCount;
    int firstGravestones;
};

class WhackZombieWaveAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(WhackZombieWaveAction, WaveAction, RtClass);

    WhackZombieWaveAction():SpawnZombieWaveNumber(0)
    {

    }
	// void InitializeAction(WaveActionPropertiesPtr i_properties, Sexy::MTRand &i_random, int i_waveNumber);
	virtual void initializeAction(Sexy::MTRand &i_random, int i_waveNumber) override;

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	void SmallWave(int i_waveNumber);
    Zombie* SpawnZombie(ZombieTypePtr i_zombieType,Point zombiepot,int i_waveNumber);
    std::vector<BoardEntity*> filtrationGrid(const std::vector<BoardEntity*>& o_entityList);
public:
    void Spawngriditem(int griditem_count,bool IswaveNumber);
private:
//    void FlashScreen();
	pvztime_t m_NextsmallWaveTime;
	pvztime_t m_wavelooptime;
    std::vector<int> zombies;
    int SpawnZombieWaveNumber;
	// ValueRange m_launchInterval;
    float m_NextBigintervalWavetime;
    pvztime_t m_NextBigWavetime;
private:

};

struct WhackZombieWaveProps
{
    int Zombie_tutorial;
    int Zombie_tutorial_armor1;
    int Zombie_tutorial_armor2;
    std::vector<std::vector<int>> SpawnZombieCount;
    float SpawnZombieCooldownTimeMin;
    float SpawnZombieCooldownTimeMax;
    float NextWavesubTime;
    int SpawnGravestonesCount;
    int BoardGravestonesMin;
    int increasedWave;
    // float speedscale;
};


class WhackZombieWaveActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(WhackZombieWaveActionProps, WaveActionProperties, RtClass);

	WhackZombieWaveActionProps() {}
//	: KillRate(0){}
	RtClass* GetActionClass() const override { return WhackZombieWaveAction::StaticGetClass(); }

    WhackZombieWaveProps  whackzombie;
//    float KillRate;
};


class Pvz1GridItemProps : public GridItemGravestonePropertySheet
{
public:
	RT_CLASS_DEFINE(Pvz1GridItemProps, GridItemGravestonePropertySheet, RtClass);
	Pvz1GridItemProps() {}

    float coin_silver;
    float coin_gold;
};


class Pvz1GridItem : public GridItemGravestone
{
public:
    RT_CLASS_DEFINE(Pvz1GridItem, GridItemGravestone, RtClass);

    Pvz1GridItem() {}
	int			CalcRenderOrder() const override;
    void onGridItemInitialize() override;
    virtual void onDestroy() override;
    void Camouflage();
    void SetAnimName(const std::string i_idleanim);

	void onAnimation(const std::string &i_animName);
private:
};

class Pvz1GridItemAnimRig : public GravestoneAnimRig
{
public:
	RT_CLASS_DEFINE(Pvz1GridItemAnimRig, GravestoneAnimRig, RtClass);
	
	virtual void SetDamageState(int i_damageState, bool i_isAnimated);
};


class WhackZombie_Basic : public ZombieBasic
{
public:
    RT_CLASS_DEFINE(WhackZombie_Basic, ZombieBasic, RtClass);
public:
    int WhackTakeDamage(SexyVector3& sunPos);
    // bool canBecomeUncamel() override;
    Sexy::Rect calcTouchRect();

};

#endif
