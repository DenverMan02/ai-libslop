

#ifndef ARTIFACT_GASHAPON_TOOLS_H_
#define ARTIFACT_GASHAPON_TOOLS_H_



#include <string>
#include "Graphics.h"
#include "GameSubSystem.h"
#include "TimeMgr.h"
#include "RtReflectionDelegate.h"
#include "StandaloneEffect.h"
#include "Effect_PopAnim.h"
#include "Zombie.h"
#include "RtDelegate.h"


class SunRainSubSystem;

typedef RtReflectionDelegate<Delegate1<bool> > AffectDelegate;

enum ArtifactGashaponSubSystemState
{
    ArtifactGashaponState_Invaild = 0,
    ArtifactGashaponState_Start,
    ArtifactGashaponState_Affect,
    ArtifactGashaponState_End,
};

enum ArtifactGashaponAffectType
{
	ArtifactGashaponAffect_Invaild = 0,
	ArtifactGashaponAffect_ShadowShroom, 		/* 1: 毒影菇 */
	ArtifactGashaponAffect_Guacodile,			/* 2: 鳄梨 */
	ArtifactGashaponAffect_Caulipower,			/* 3: 超能花菜 */
	ArtifactGashaponAffect_Iceburg,				/* 4: 冰冻生菜 */
	ArtifactGashaponAffect_Sun,					/* 5: 阳光 */
	ArtifactGashaponAffect_ConvallariaChemist,	/* 6: 芦藜药师 */
	ArtifactGashaponAffect_Parsnip,				/* 7: 防风草 */
	ArtifactGashaponAffect_HypnoShroom,			/* 8: 魅惑菇 */
	ArtifactGashaponAffect_Monotropa,			/* 9: 水晶兰 */
	ArtifactGashaponAffect_SunPlus,				/* 10: 阳光 */
};

struct ArtifactGashaponAffectInfo
{
	ArtifactGashaponAffectType Type;
	float Possibility2;
	float Possibility3;
	AffectDelegate AffectFun;
	SexyString DesStr2;
	SexyString DesStr3;
};

struct ArtifactGashaponResultInfo
{
	ArtifactGashaponAffectType Type;
	bool IsSame3;
	float PossibilityRX;

	ArtifactGashaponResultInfo& operator=(const ArtifactGashaponResultInfo& p)
	{
		Type = p.Type;
		IsSame3 = p.IsSame3;
		PossibilityRX = p.PossibilityRX;
		return *this;
	}
};


class ArtifactGashaponSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ArtifactGashaponSubSystem, GameSubSystem, RtClass);

	ArtifactGashaponSubSystem();
    ~ArtifactGashaponSubSystem();

    void setPossibility(std::vector<float> i_possibility2s, std::vector<float> i_possibility3s);
    void setPamAndLabel(std::string i_pamName, std::string i_label) { m_pamName = i_pamName, m_animLableToPlay = i_label; }
    void playAnimation();

    void Start();
	void Update() override;
	void AddToRenderQueue(class RenderQueue* i_queue) override;
    void setState(ArtifactGashaponSubSystemState i_state);
    void setArtifactLevelAndStage(int i_level, int i_stage) { m_artifactLevel = i_level; m_artifactStage = i_stage; }

    bool IsValidTargete(Zombie* i_zombie);

    void registerHandTouchEvents();
    void unregisterHandTouchEvents();

protected:
    virtual void onDestroy() override;
    virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param);

private:
    bool handleTouch(const Sexy::Touch& i_touch);
    void cancelTouch();
	
    void onDrawResultDescription(Sexy::Graphics *i_g);
    void onDrawDardBackground(Sexy::Graphics *i_g);
    void onStandaloneEffectFinishedCallback(StandaloneEffect *i_effect);

    void initAffectInfos();
    void initResultPool();
    void initResultPoolPlus();
    void doAffect();
    void getResult();
    void displayResult();

    void AffectShadowShroom(bool i_flg);
    void AffectGuacodile(bool i_flg);
    void AffectCaulipower(bool i_flg);
    void AffectIceburg(bool i_flg);
    void AffectSun(bool i_flg);
    void AffectConvallariaChemist(bool i_flg);
    void AffectParsnip(bool i_flg);
    void AffectHypnoShroom(bool i_flg);
    void AffectMonotropa(bool i_flg);
    void AffectSunPlus(bool i_flg);

	Effect_PopAnim* CreateProjectileEffectByBoardSpace(const std::string pamName, const std::string animName, SexyVector3 pos, int renderOrder);

    void OnSpawnGuacodile(Projectile* i_projPtr, int i_index);
    void OnSpawnParsnip(Projectile* i_projPtr, int i_index);

    bool m_shouldDrawDescription;
    int m_cardDrawNum;
    pvztime_t m_timer;;
    bool m_isLastSame3;
    bool m_isSame3;
    ArtifactGashaponAffectType m_affectType;
    ArtifactGashaponSubSystemState m_state;
    std::vector<ArtifactGashaponAffectInfo> m_affectInfos;
    RtWeakPtr<Effect_PopAnim> m_effect;
    std::string m_pamName;
    std::string m_animLableToPlay;
    int m_artifactLevel;
    int m_artifactStage;
    SunRainSubSystem* m_rainSys;
    std::vector<ArtifactGashaponResultInfo> m_resultPool;
    std::vector<ArtifactGashaponResultInfo> m_resultPoolPlus;
    std::vector<ArtifactGashaponAffectType> m_result;
};

class SunRainSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(SunRainSubSystem, GameSubSystem, RtClass);

public:
	SunRainSubSystem();

	void Start();
	void Update() override;
	void SetSunCurrency(int i_largeSuns, int i_midumSuns, int i_smallSuns);
	void SetVelocity(SexyVector3 i_velocity) { m_velocity = i_velocity; }

private:
	std::vector<std::string> m_sunTypes;
	SexyVector3 m_velocity;
	bool m_isAlive;
	int m_index;
	int m_sunPerFrame;
	float m_sunAutoCollectDelay;


};


typedef RtReflectionDelegate<Delegate2<Projectile*, int> > ProjSpawnedDelegate;
class ProjectilesGroup : public RtObject
{
	RT_CLASS_DEFINE(ProjectilesGroup, RtObject, RtClass);

public:
	ProjectilesGroup();

	void setProjectilePropPtr(ProjectilePropertySheetPtr i_ptr) { m_projectilePropPtr = i_ptr; }
	void setProjectileBasePos(SexyVector3 i_pos) { m_basePosition = i_pos; }
	void setSpawnInterval(float i_interval) { m_interval = i_interval; }
	void setProjectileNum(int i_num) { m_num = i_num; }
	void setProjectileSpawnedDelegate(ProjSpawnedDelegate i_delegate) { m_projectileSpawnedDelegate = i_delegate; }

	void start();
	void update();
	bool isDone() { return m_isDone; }

private:
	ProjectilePropertySheetPtr m_projectilePropPtr;
	SexyVector3 m_basePosition;
	float m_interval;
	bool m_isAlive;
	bool m_isDone;
	int m_index;
	int m_num;

	float m_nextProjTime;
	ProjSpawnedDelegate m_projectileSpawnedDelegate;
};

class SpawnProjectilesSubSystem : public GameSubSystem
{
	RT_CLASS_DEFINE(SpawnProjectilesSubSystem, GameSubSystem, RtClass);

public:
	virtual ~SpawnProjectilesSubSystem();

	void Update() override;
	void addProjectilesGroup(ProjectilePropertySheetPtr i_ptr, SexyVector3 i_pos, int i_num, float i_interval, ProjSpawnedDelegate i_delegate = ProjSpawnedDelegate());

	bool Serialize(const RtSerializeContext& i_serializeContext) override;

private:
	std::vector<ProjectilesGroup*> m_groups;
	std::vector<ProjectilesGroup*> m_newGroups;

};

//
class ArtifactGashaponGuacodileProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ArtifactGashaponGuacodileProjectile, Projectile, RtClass);

	bool OnCollideEntity(BoardEntity* i_entity) override;
	void SetJumpState();
	bool ShouldClipWithWater() const override { return true; }

	void setDamageAmount(float i_damageAmount) { m_damageAmount = i_damageAmount; }

    void SetIsAvatar(bool i_avatar) { m_IsAvatar = i_avatar; }

protected:

private:
	void onProjectileInitialized() override;
	void onUpdate(pvztime_t i_dt) override;
	void onPostLoad() override;

	void onAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);
	void chomp(BoardEntity* i_entity);

	pvztime_t m_nextChompTime;

	enum State
	{
		JUMPING,
		MOVING
	};
	State m_state;
	AnimHandle m_animHandle;
    bool       m_turnedAround;
    bool       m_IsAvatar;
    float 	   m_damageAmount;
    std::vector<BoardEntityPtr> m_hasAttackedEntities;
};

class ArtifactGashaponGuacodileProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(ArtifactGashaponGuacodileProjectileProps, ProjectilePropertySheet, RtClass);

	ArtifactGashaponGuacodileProjectileProps()
	: ChompsPerSecond(1.0f)
	, DamagePerChomp(100.0f)
	{
		// Do nothing.
	}

	float ChompsPerSecond;
	float DamagePerChomp;
};


class ArtifactGashaponParsnipProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ArtifactGashaponParsnipProjectile, Projectile, RtClass);

	bool OnCollideEntity(BoardEntity* i_entity) override;
	void StartAnimation(bool i_isInPlantfoodState);
	bool ShouldClipWithWater() const override { return true; }
	void SetDamageRatio(float i_ratio) { m_damageRatio = i_ratio; }
	void setDamageAmount(float i_damageAmount) { m_damageAmount = i_damageAmount; }

protected:

//private:
	void onProjectileInitialized() override;
	void onUpdate(pvztime_t i_dt) override;

	void onAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);
	virtual void chomp(BoardEntity* i_entity);
	virtual void playAnimation();

	pvztime_t m_nextChompTime;
	bool m_isInPlantFoodState;

	AnimHandle m_animHandle;
	float m_damageRatio;
	float m_damageAmount;
	std::vector<BoardEntityPtr> m_hasAttackedEntities;
};

class ArtifactGashaponParsnipProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(ArtifactGashaponParsnipProjectileProps, ProjectilePropertySheet, RtClass);

	ArtifactGashaponParsnipProjectileProps()
	: ChompsPerSecond(1.0f)
	, DamagePerChomp(100.0f)
	{
		// Do nothing.
	}

	float ChompsPerSecond;
	float DamagePerChomp;
};

#endif
