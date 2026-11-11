/*
 * HeianStage.h
 *
 *  Created on: 2020-11-25
 *      Author: admin
 */

#ifndef HEIANSTAGE_H_
#define HEIANSTAGE_H_

#include "PVZTypes.h"
#include "RtObject.h"
#include "StageModule.h"
#include "WaveActionSpawnZombies.h"
#include "GameSubSystem.h"

class HeianStage : public StageModule
{
public:
	RT_CLASS_DEFINE(HeianStage, StageModule, RtClass);

protected:
	void initializeModule() override;
	void registerForEvents() override;
};

class HeianStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(HeianStageProperties, StageModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return HeianStage::StaticGetClass();
	}
};

struct ZombieDropData
{
	ZombieDropData(SexyVector3 i_destination, RtWeakPtr<class Zombie> i_zombie)
	:Destination(i_destination)
	,DroppedZombie(i_zombie)
	{

	}

	ZombieDropData()
	{

	}

	SexyVector3 Destination;
	RtWeakPtr<class Zombie> DroppedZombie;
};

class HeianSmokeBomb : public BoardEntity
{
public:
	RT_CLASS_DEFINE(HeianSmokeBomb, BoardEntity, Sexy::RtClass);

	HeianSmokeBomb();
	virtual ~HeianSmokeBomb();

	enum SmokeBombState
	{
		PVZ_BEGIN_ENUM(SMOKEBOMB_STATE_),
		SMOKEBOMB_STATE_FALLING,
		SMOKEBOMB_STATE_EXPLOSION,
		PVZ_END_ENUM(SMOKEBOMB_STATE_)
	};

	virtual void 	onInitialized() override;
	virtual void 	onDestroy() override;

	void 			Activate(const bool i_active, const float fallDuration, const int i_row, const int i_col, const ZombieDropData& i_dropData);
    virtual void    onUpdate() override;
    virtual void    onDraw(Graphics* i_g) override;
	inline bool		IsActive() const {return m_active;}
	SmokeBombState	getState() { return m_bombState; }
	int				getDropCol() { return m_dropCol; }
	int				getDropRow() { return m_dropRow; }
	const ZombieDropData& GetDropData() { return m_dropData; }

private:
	void 			setState(SmokeBombState state);

	void 			onAnimStopped(const std::string &i_animName);
	void			createDropEffect();

	bool						m_hasExploded;
	bool 						m_active;
	SmokeBombState 				m_bombState;
	float 						m_fallTimeElapsed;
	float 						m_fallDuration;
	RtWeakPtr<Effect_PopAnim> 	m_effectBomb;
    class Effect_PopAnim*       m_effectExplosion;

	SexyVector2					m_placementPosition;
	int							m_dropCol;
	int							m_dropRow;
	ZombieDropData				m_dropData;
};

namespace Message
{
	void SmokeBombExploded(HeianSmokeBomb* i_bomb);
}

class HeianSmokeBombSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(HeianSmokeBombSubsystem, GameSubSystem, RtClass);

    HeianSmokeBombSubsystem();
    ~HeianSmokeBombSubsystem() override;

    void ActivateSmokeBomb(const bool i_active, const float fallDuration, const int i_row, const int i_col, const ZombieDropData& i_dropData);

private:
    std::vector<RtWeakPtr<class HeianSmokeBomb> > m_bombs;
    void onSmokeBombExploded(HeianSmokeBomb* i_bomb);
	void SpawnNinjia(const ZombieDropData& i_dropData);
};

class HeianNinjaZombieSpawner : public ZombieRainSpawner
{
	RT_CLASS_DEFINE(HeianNinjaZombieSpawner, ZombieRainSpawner, RtClass);
public:
	HeianNinjaZombieSpawner()
	{
		// Do nothing.
	}

	void PostSpawnZombieSetup(Zombie* i_zombie, SexyVector3 i_destination, float i_fallDuration, float i_startHeight) override;
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
};

class HeianNinjaZombieSpawnerProps : public ZombieRainSpawnerProps
{
	RT_CLASS_DEFINE(HeianNinjaZombieSpawnerProps, ZombieRainSpawnerProps, RtClass);
public:

	HeianNinjaZombieSpawnerProps()
	{
		WaveStartMessage = "[WARNING_PARACHUTERAIN]";
	}

	RtClass* GetActionClass() const override
	{
		return HeianNinjaZombieSpawner::StaticGetClass();
	}

};

#endif /* HEIANSTAGE_H_ */
