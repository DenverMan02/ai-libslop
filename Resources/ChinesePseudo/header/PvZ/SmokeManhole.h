#ifndef SMOKEMANHOLE_h
#define SMOKEMANHOLE_h

#include "Precompile.h"
#include "GridItem.h"

class PlantFlattenedshroom;
class Plant;

enum SmokeManholeState
{
    PVZ_BEGIN_ENUM(SMOKEMANHOLE_),
    	SMOKEMANHOLE_READY,
    	SMOKEMANHOLE_ROAR,
    	SMOKEMANHOLE_FIRST_ALERT,
    	SMOKEMANHOLE_ALERT,
    	SMOKEMANHOLE_IDLE,
    	SMOKEMANHOLE_COOLDOWN,
    PVZ_END_ENUM(SMOKEMANHOLE_)
};

class Effect_SmokePollution: public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(Effect_SmokePollution, Effect_PopAnim, RtClass);

	Effect_SmokePollution(): m_hasSmokePollution(false), m_owner(nullptr){}

	bool HasSmokePollution(){ return m_hasSmokePollution; }

	void SetOwner(class GridItemSmokeManhole* owner){ m_owner = owner; }

protected:
	void PlaySmokeIdle(class GridItemSmokeManhole* owner);

	void onAnimStopped(const std::string& i_animLabel) override;

	void registerForEvents() override;
	void unregisterForEvents() override;

private:
	bool m_hasSmokePollution;
	class GridItemSmokeManhole* m_owner;
};

class Effect_SmokeManhole: public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(Effect_SmokeManhole, Effect_PopAnim, RtClass);

	Effect_SmokeManhole(): m_owner(nullptr){}

	void SetOwner(class GridItemSmokeManhole* owner){ m_owner = owner; }

protected:

	void onAnimStopped(const std::string& i_animLabel) override;

private:
	class GridItemSmokeManhole* m_owner;
};

class GridItemSmokeManhole: public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemSmokeManhole, GridItem, RtClass);

	GridItemSmokeManhole();
	virtual ~GridItemSmokeManhole();

	void SetupAnimation();

	void GetReady(float startTime);
	void AddCoolDownTime(float extraCooldownTime);

	bool CanPlantOn(){ return m_state == SMOKEMANHOLE_IDLE || m_state == SMOKEMANHOLE_COOLDOWN || m_state == SMOKEMANHOLE_ALERT; }
	void BlockSmoke(PlantFlattenedshroom* mushroom);
	void UnBlockSmoke(PlantFlattenedshroom* mushroom);
	void BlowSmoke();
	void AbsorbSmoke();

	bool HasPollutionSmoke();

	void SetDamage(float i_damage) { m_damage = i_damage; }
	float GetDamage();

	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
protected:

	void onUpdate() override;

	void onRoarEnd(class GridItemSmokeManhole* owner);
	void onSmokeEnd();

	void InReadyState();
	void InAlertState();
	void InFirstAlertState();
	void InRoarState();
	void InIdleState();
	void InCooldownState();

	void DamagePlant(int GridX, int GridY, Plant* plant);

	void registerForEvents() override;
	void unregisterForEvents() override;

protected:
	SmokeManholeState m_state;
	float m_startTime;
	float m_nextRoarTime;
	float m_nextAlertTime;
	float m_triggerDamageTime;
	float m_extraCDTime;
	float m_mushroomPlantTime;


	RtWeakPtr<Effect_SmokeManhole> m_manholeRig;
	RtWeakPtr<Effect_SmokePollution> m_smokeRig;

	PlantPtr m_mushroom;
	float m_damage;
};

class GridItemSmokeManholeProps: public GridItemPropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemSmokeManholeProps, GridItemPropertySheet, RtClass);
	GridItemSmokeManholeProps(){}

	SexyVector2 ArtCenter;
	std::string PopAnim;
	std::string PopAnimSmoke;
	float Damage;
	float CoolDown;
	float AlertTime;
};

#endif
