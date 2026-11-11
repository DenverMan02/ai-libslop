/*
 * 	ZombiePumpkinScarecrowBird.h
 *
 * 	Created on: 2022-8-25
 * 		Author: kkdud
 */

#ifndef __ZOMBIE_PUMPKIN_SCARECROW_BIRD_H__
#define __ZOMBIE_PUMPKIN_SCARECROW_BIRD_H__


#include "Zombie.h"
#include "PvZ2IDs.h"
#include "Plant.h"

STATE_ENUM_CHILD_BEGIN(ZombieStatePumpkinScarecrowBirdState, ZombieState)
	ZS_PUMPKIN_SCARECROW_BIRD_FlyToTarget,
	ZS_PUMPKIN_SCARECROW_BIRD_AttachedToPlant,
	ZS_PUMPKIN_SCARECROW_BIRD_PickingUpPlant,
	ZS_PUMPKIN_SCARECROW_BIRD_DestroyingPlant,
	ZS_PUMPKIN_SCARECROW_BIRD_Returning,
	ZS_PUMPKIN_SCARECROW_BIRD_FlyingAway,
	ZS_PUMPKIN_SCARECROW_BIRD_FlyToScarecrow,
STATE_ENUM_END(ZombieStatePumpkinScarecrowBirdState)

class ZombiePumpkinScarecrowBird : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePumpkinScarecrowBird, Zombie, RtClass);

	void SetTargetColAndRow(int i_col, int i_row);
	void SetCaptain(ZombiePtr i_captain);
	void OnCaptainDied();
	void flyToScarecrow(SexyVector3 i_position);
	void flyAway();

	virtual bool CollidesWithType(CollisionTypeFlags i_collisionFlags) const override;

protected:
	virtual void onZombieInitialize() override;
	virtual void onPlaceOnBoard() override;
	virtual void onApplyCondition(ZombieConditions i_condition) override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    bool willDieToShrinking() override { return true; }
    virtual int CalcRenderOrder() const override;

	virtual void onTurnedToAsh() override;
	virtual void onElectrocuted() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

    // Parrot shadow changes when flying away
    virtual SexyVector2 GetShadowScaling() const override;

	virtual class Plant* findPlantTarget();
	void findNewTargetAndFlyTo();
	PlantPtr pickTarget(Point& i_targetPos);

	DECLARE_STATE_FUNCTIONS(ZombieState, FlyToTarget);
	DECLARE_STATE_FUNCTIONS(ZombieState, AttachedToPlant);
	DECLARE_STATE_FUNCTIONS(ZombieState, PickingUpPlant);
	DECLARE_STATE_FUNCTIONS(ZombieState, DestroyingPlant);
	DECLARE_STATE_FUNCTIONS(ZombieState, Returning);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyingAway);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyToScarecrow);

private:
	bool moveToDestination(const float i_destX, const float i_destY);
	bool moveToDestination(SexyVector3 i_destination);

	//PVZ2_CHINESE_START
    struct PlantCache
    {
        SexyVector3 plantPos;
        uint        plantState;
        int         plantRow;

        PlantCache()
        {
            plantPos = SexyVector3(-1, -1, 0);
            plantState = -1;
            plantRow = -1;
        }
    };

	PlantCache     m_plantCache;
	//PVZ2_CHINESE_END
	ZombiePtr		m_captain;
	PlantPtr		m_pickedUpPlant;
	int				m_targetCol = -1;
	int				m_targetRow = -1;
	SexyVector3 	m_targetLoc;
	pvztime_t 		m_birdCryTimer = PVZ_EOT();
};



#endif /* __ZOMBIE_PUMPKIN_SCARECROW_BIRD_H__ */
