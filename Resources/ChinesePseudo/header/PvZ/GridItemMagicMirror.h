/*
 * 	GridItemMagicMirror.h
 *
 * 		Created on: 2022-05-30
 * 			Author: kkdud
 */


#ifndef PLANTSVERSUSZOMBIES2_PVZ2_GRIDITMEMAGICMIRROR_H_
#define PLANTSVERSUSZOMBIES2_PVZ2_GRIDITMEMAGICMIRROR_H_

#include "Precompile.h"
#include "GameSubSystem.h"
#include "GridItemAnimation.h"
#include "Zombie.h"

namespace Message
{
	void NotifyEnterMagicMirror();
}

enum GridItemMagicMirrorState
{
	MAGIC_MIRROR_INVALID,
	MAGIC_MIRROR_APPEARING,
	MAGIC_MIRROR_WORKING,
	MAGIC_MIRROR_DISAPPEARING
};

enum GridItemMagicMirrorType
{
	MAGIC_MIRROR_TYPE_ENTRANCE,
	MAGIC_MIRROR_TYPE_EXIT,
	MAGIC_MIRROR_TYPE_ENTRANCEANDEXIT
};

class GridItemMagicMirrorProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemMagicMirrorProps, GridItemAnimationProps, RtClass);

	std::vector<std::string> ZombieTypeNameCannotBeTeleported;
	std::vector<std::string> ProjectileClassNameCannotBeTeleported;
};

class GridItemMagicMirror: public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemMagicMirror, GridItemAnimation, RtClass);

	GridItemMagicMirror();

	int CalcRenderOrder() const override;

	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

	void setState(GridItemMagicMirrorState i_state);
	GridItemMagicMirrorState getState() { return m_state; }

	void setValues(float i_existDuration);
	void setBrotherMagicMirror(GridItemMagicMirror* i_mirror) { m_brotherMagicMirror = i_mirror->GetPtr(); }

private:
	void onGridItemInitialize() override;
	void onUpdate() override;
	bool canGameObjectBeTeleported(RtWeakPtr<GameObject> i_objPtr);
	void onDraw(Graphics* i_g) override;

	void onAnimStoppedCallback(const std::string& i_animLabel);
	void onPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params);
	void tryToThrowPlant();

	GridItemMagicMirrorState m_state;
	float m_existDuration;

	RtWeakPtr<GridItemMagicMirror> m_brotherMagicMirror;
	pvztime_t m_disappeartime;
};

class GridItemMagicMirrorRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemMagicMirrorRig, PopAnimRig, RtClass);

	void playAppearAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void playWorkingAnim();
	void playDisappearAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	const std::string getAppearingAnimLabel();
	const std::string getWorkingAnimLabel();
	const std::string getDisAppearingAnimLabel();
};

enum TeleportationArrayState
{
	TELEPORTATION_ARRAY_INVALID,
	TELEPORTATION_ARRAY_APPEARING,
	TELEPORTATION_ARRAY_WORKING,
	TELEPORTATION_ARRAY_DISAPPEARING
};

enum MagicMirrorTeleportationObjectState
{
	OBJECT_STATE_TELEPORT_INVALID,
	OBJECT_STATE_TELEPORT_OUT,
	OBJECT_STATE_TELEPORT_DISAPPEARED,
	OBJECT_STATE_TELEPORT_IN,
	OBJECT_STATE_TELEPORT_DONE
};

class MagicMirrorTeleportationObject
{
public:
	MagicMirrorTeleportationObject()
	: m_state(OBJECT_STATE_TELEPORT_INVALID)
	{}

	RtWeakPtr<GameObject> m_objPtr;
	SexyVector3 m_startPos;
	SexyVector3 m_endPos;
	pvztime_t m_startTime;

	MagicMirrorTeleportationObjectState m_state;
};

class MagicMirrorTeleportationArraySubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(MagicMirrorTeleportationArraySubSystem, GameSubSystem, RtClass);

	void Update() override;

	void addGameObject(RtWeakPtr<GameObject> i_objPtr, SexyVector3 i_startPos, SexyVector3 i_endPos);

	MagicMirrorTeleportationObject* findTeleportingGameObject(GameObject* i_object);

private:
	void warpOutGameObject(MagicMirrorTeleportationObject& i_obj);
	void disappearGameObject(MagicMirrorTeleportationObject& i_obj);
	void warpInGameObject(MagicMirrorTeleportationObject& i_obj);
	void recoverGameObject(MagicMirrorTeleportationObject& i_obj);

	std::vector<MagicMirrorTeleportationObject> m_teleportingGameObjects;
	std::vector<MagicMirrorTeleportationObject> m_newTeleportingGameObjects;
	std::vector<GameObject*> m_deleteGameObjects;
};

#endif /* PLANTSVERSUSZOMBIES2_PVZ2_GRIDITMEMAGICMIRROR_H_ */
