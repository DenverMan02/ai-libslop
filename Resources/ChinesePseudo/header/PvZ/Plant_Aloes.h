/*
 * Plant_Aloes.h
 *
 *  Created on: 2019-8-7
 *      Author: zhousen
 */

#ifndef PLANT_ALOES_H_
#define PLANT_ALOES_H_

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "GameSubSystem.h"
#include "PlantUtils.h"

class PlantAloes;
class PlantAloesProps;

///
/// GridItemWaterMistProps
///
class GridItemWaterMistProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemWaterMistProps, GridItemAnimationProps, RtClass);

	GridItemWaterMistProps();

	pvztime_t GetAliveTimeThreshold(bool plantfood) const {
		if (plantfood) return _aliveTimeThresholdPlantfood;
		else		   return _aliveTimeThreshold;
	}

	float	  GetAttackUpPercent(bool plantfood) const {
		if (plantfood) return _attackUpPercentPlantfood;
		else 		   return _attackUpPercent;
	}

	float	  GetHealthUpPercent(bool plantfood) const {
		if (plantfood) return _healthUpPercentPlantfood;
		else 		   return _healthUpPercent;
	}

	float	  GetSpeedUpPercent() const { return _speedUpPercent; }
	pvztime_t GetFreezeTimeThreshold() const { return _freezeTimeThreshold; }

private:
	pvztime_t _aliveTimeThreshold;// water mist alive time
	pvztime_t _aliveTimeThresholdPlantfood;// water mist alive time in plantfood state
	float _attackUpPercent;// increase plant attack
	float _attackUpPercentPlantfood;// increase plant attack in plantfood state
	float _healthUpPercent;// increase plant life
	float _healthUpPercentPlantfood;// increase plant life in plantfood state
	float _speedUpPercent;// increase plant speed
	pvztime_t _freezeTimeThreshold;// freeze zombie time threshold
};

// the type of aloes projectile
enum AloesSprayType {
	Aloes_Normal,// normal
	Aloes_Special,// skill lv.2 special 
	Aloes_Plantfood,// normal plantfood
	Aloes_Plantfood_Avatar,// avatar plantfood
};

enum WaterMistState {
	WaterMist_Init,
	WaterMist_Start,// play start effect
	WaterMist_Loop,// play loop effect
	WaterMist_End,// play end effect
	WaterMist_Destroy,// destroy this water mist
	WaterMist_Max,
};

///
/// GridItemWaterMist
///
class GridItemWaterMist : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemWaterMist, GridItemAnimation, RtClass);

	GridItemWaterMist();
	virtual ~GridItemWaterMist();

	bool IsDamageable() const override { return false; }
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

	void onGridItemInitialize() override;
	void onUpdate() override;
	void KillGridItem() override;
	int CalcRenderOrder() const override;

	void SetType(int type);
	void SetAvatar(bool avatar);
	void SetExtraAttackRate(float i_rate);
	void TurnToLoop();// make water mist alive longer

	virtual void NerfZombie(Zombie* zombie);
	virtual void AffectZombie(Zombie* zombie) {}
	int GetState() { return _state; }

private:
	void OnCreatePlant(Plant* plant);// a new plant created post message, callback
	void OnZombieEnter(Zombie* zombie);// a zombie entered the water mist post message, callback

	void BufferPlant(Plant* plant);// buffer plant
	void BufferPlantAttack(Plant* plant);// buffer attack
	void BufferPlantHealth(Plant* plant);// buffer health
	void BufferPlantSpeed(Plant* plant);// buffer speed
	void RecoverPlant(Plant* plant);// recover plant from poison status
	// freeze zombie in water mist

	void DoWaterMistEffect(Sexy::Point point);// apply real effect on water

	void PlayStartEffect();// fog and water start effect
	void PlayLoopEffect();// fog and water loop effect
	void PlayEndEffect();// fog and water end effect
	void PlayUpEffect();// buffer plant effect
	void PlayFreezeEffect();// freeze effect
	void PlayExplodeEffect();// explode effect

	void OnStartEffectCompleted(StandaloneEffect* i_effect);// callback when start effect end
	void OnEndEffectCompleted(StandaloneEffect* i_effect);// callback when end effect end

	// loop : if the anim is loop 
	// callback : when it stop to do callback function
	RtWeakPtr<GameObject> PlayEffect(std::string pam, std::string anim, int x, int y, bool loop = false, std::string callbackName = "");
	bool PlayEffect(RtWeakPtr<GameObject> effect, std::string anim, bool loop = false, std::string callbackName = "");
	RtWeakPtr<GameObject> CreateEffect(std::string pam, int x, int y, RenderLayer layer = RENDER_LAYER_PROJECTILE);// create factory

private:
	int _state;// WaterMistState
	int _type; // AloesSprayType
	bool _isAvatar;// if this grid item is avatar grid item
	Sexy::Point _position;// water mist grid position
	pvztime_t _startTime;// water mist start time
	pvztime_t _aliveTimeThreshold;// water mist alive time
	float _extraAttackRate;// gene enhancement action

	// for water mist effect
	RtWeakPtr<GameObject> _fogEffectObj;
	RtWeakPtr<GameObject> _waterEffectObj;
	RtWeakPtr<GameObject> _upEffectObj;
	RtWeakPtr<GameObject> _freezeEffectObj;
	RtWeakPtr<GameObject> _explodeEffectObj;
};

class GridItemIceWaterMistProps : public GridItemWaterMistProps
{
public:
	RT_CLASS_DEFINE(GridItemIceWaterMistProps, GridItemWaterMistProps, RtClass);

	GridItemIceWaterMistProps()
	: EffectRectRight(0)
	, EffectRectLeft(0)
	, EffectRectTop(0)
	, EffectRectBottom(0){}

	int EffectRectRight;
	int EffectRectLeft;
	int EffectRectTop;
	int EffectRectBottom;
	std::vector<std::string> ZombieBlacklist;
};

class GridItemIceWaterMist : public GridItemWaterMist
{
public:
	RT_CLASS_DEFINE(GridItemIceWaterMist, GridItemWaterMist, RtClass);

	GridItemIceWaterMist();
	virtual ~GridItemIceWaterMist();

	void AffectZombie(Zombie* zombie) override;
	void onDestroy() override;
	void onUpdate() override;
	bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
	void applyChill();

private:
	std::vector<RtWeakPtr<class Zombie>> m_affectZombies;
};

///////////////////////////
/// AloesSprayProjectile
///////////////////////////
class AloesSprayProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(AloesSprayProjectile, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual bool OnCollideGround() override;

	void InitParam(Plant* plant, Sexy::Point target);

protected:
	void CreateWaterMist(std::vector<Sexy::Point> list);// create water mist grid item or make it alive longer
	std::vector<Sexy::Point> FillSprayFields(Sexy::Point center);// calc spray fields

private:
	int _projectileType;// AloesSprayType
	bool _isAvatar;// if plant is avatar
	Sexy::Point _target;// target grid pos
	float _extraAttackRate;
	std::vector<Sexy::Point> _sprayFields;// which blocks can be effected by spray
};

///////////////////////////////
///      plant aloes
///////////////////////////////
enum AloesState {
	Aloes_Init = STATE_FRAMEWORK_BEGIN,
	Aloes_Charge,
	Aloes_Splash,// aloes throw water on itself
	Aloes_Spread,// 
	Aloes_SpecialAttack,// plantfood
	Aloes_Max,
};

class PlantAloes : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantAloes, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void UpdateActions() override;
	virtual bool CanApplyPlantfood() override;

	virtual void ApplyPlantfood() override;
	virtual void UpdatePlantfood() override;
	virtual void CancelPlantfood() override;

	virtual bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	virtual void onAnimStoppedCallback(const std::string& i_animCommand) override;

	int GetProjectileType() const { return _projectileType; }

	// override this function is to not let the default fire logic run because we make projectile property in sheet
	virtual class Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override	{ return nullptr; }
	// even we have projectile in sheet, we should not make this automatically.so this func should be override
	virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override { return false; }

private:
	void UpdateInit();
	void UpdateCharge();
	void UpdateSplash();

	void LaunchSpecialAttack();
	
	std::vector<Projectile*> CreateAloesSprayProjectile(std::vector<Sexy::Point> locationList, int projectType);// locationList is the projectile which throw the target position.
	Projectile* CreateAloesSprayProjectile(Sexy::Point pos, int projectType);// shoot in plantfood status
	bool CheckSpecialAttack();// check if this is a special attack ( not plant food attack )
	void CreateWaterMist(std::vector<Sexy::Point> locations);// create grid item
	void CreateWaterSprayEffect(int x, int y, bool isAvatar);// create normal or special attack effect
	void onStandaloneEffectFinishedCallback(StandaloneEffect* i_effect) override;// callback when WaterSprayEffect end
	std::vector<Sexy::Point> FillSprayFields(Sexy::Point center);// get all avaliable grid location for waterMist
	void RemoveProjectielPos(Sexy::Point point);// this is for plantfood projectile
	
private:
	pvztime_t _splashStartTime;
	pvztime_t _splashChargeTime;
	int _projectileType;// AloesSprayType
	bool _isAvatar;
	Sexy::Point _position;
	std::vector<Sexy::Point> _projectileList;// when we shoot plantfood project, we should fill the vector first, then create projectile
};


///////////////////////////////
///      plant props
///////////////////////////////
class PlantAloesProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PlantAloesProps, PlantPropertySheet, RtClass);

	PlantAloesProps();

	float GetSpecialSprayRandomRatio() const { return _specialSprayRandomRatio; }
	float GetSplashChargeTimeThreshold() const { return _splashChargeTimeThreshold; }
	float GetPlantfoodSprayRandomRatio() const { return _plantfoodSprayRandomRatio; }

private:
	float _specialSprayRandomRatio;// the ratio that throw special water mist
	float _splashChargeTimeThreshold;// the time aloes should charge to splash water mist
	float _plantfoodSprayRandomRatio;// the ratio that throw plantfood projectile when level is above 4.
};


///////////////////////////////
///      plant anim rig
///////////////////////////////
class PlantAnimRig_Aloes : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Aloes, PlantAnimRig, RtClass);
	PlantAnimRig_Aloes();

private:
	std::string getPlantFoodMainAnimName() override;
};


#endif /* PLANT_ALOES_H_ */
