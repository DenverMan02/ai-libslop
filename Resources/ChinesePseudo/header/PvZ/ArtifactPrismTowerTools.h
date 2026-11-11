/*
 * 	ArtifactPrismTowerTools.h
 *
 * 		Created on:	2022-4-23
 * 			Author:	kkdud
 */

#ifndef PLANTSVERSUSZOMBIES2_PVZ2_ARTIFACTPRISMTOWERSUBSYSTEM_H_
#define PLANTSVERSUSZOMBIES2_PVZ2_ARTIFACTPRISMTOWERSUBSYSTEM_H_

#include "GameSubSystem.h"
#include "Artifact.h"
#include "BoardArtifactButton.h"

namespace Message
{
    void ArtifactPrismTowerActivate();
    void ArtifactPrismTowerDeActivate();
}

/*
 * Draws a laser beam between the artiact and the target and deals damage.
 */
class ArtifactPrismTowerSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ArtifactPrismTowerSubSystem, GameSubSystem, RtClass);

	enum LaserState
	{
	    LS_STATE_INACTIVE = 0,
	    LS_STATE_WARMINGUP,
	    LS_STATE_ACTIVE,
	    LS_STATE_DISABLING
	};

	enum LaserShooter
	{
	    LSNone = 0,
	    LSLevel1,
	    LSLevel2,
	    LSLevel3
	};

	enum LaserType
	{
	    LT_Laser,
	    LT_Impact,
	    LT_Shooter,
	};

	struct LaserShooterProps
	{
		RtWeakPtr<ArtifactPrismTower> owner = nullptr;
		float maxDist = 900.0f;
		float maxAngleRadd = 2000.0f;
		float durationOnLv1 = 1.0f;
		float durationOnLv2 = 1.0f;
		float timeTakesToBreakTheShield = 2.0f;
		float explodeDamageMultiplier = 2.0f;
	};

	ArtifactPrismTowerSubSystem() {}
	~ArtifactPrismTowerSubSystem() {}

	void Update() override;
	void AddToRenderQueue(class RenderQueue* i_queue) override;
	static bool CanBeTarget(BoardEntity* i_entity);
    void SetLaserState(LaserState i_newState);
    void SetLaserProps(LaserShooterProps i_props) { m_laserProps = i_props; }

private:
	void RenderLaser(Graphics *i_g);
	void RenderLaserUpdate();
	SexyVector2 GetLaserShooterPos();
    BoardEntity* FindLaserTargetByType(BoardEntityTypeFlag i_type, float& targetDistSqr);
    BoardEntity* FindLaserTarget();
    bool LaserNeedLevelUp();
    void LaserLevelUp();
    void UpdateLaserShooterLayer();
    void LaserHitBlasting(BoardEntity* i_entity, const SexyVector2& i_laserPivotScreenSpace);
    void ApplyLaserDamage(BoardEntity* i_entity);
    SexyVector2 CollsionCenter(BoardEntity* i_target);
    bool IsLaserInLevel(LaserShooter i_level);
    float CalcAngleForVector(const SexyVector2& i_vector);

    void CheckShouldBreakFogShield();
    void CheckShouldExplodeZombie(BoardEntity* i_entity, float i_dps);

    RtWeakPtr<class Effect_PopAnim> GetLaserRig();
    RtWeakPtr<class Effect_PopAnim> GetLaserImapctRig();
    RtWeakPtr<class Effect_PopAnim> GetLaserShooterRig();
    RtWeakPtr<GameObject> LoadLaserEffect(std::string i_name, LaserType i_laserType);

private:
    LaserShooterProps m_laserProps;
    LaserState m_laserState = LS_STATE_INACTIVE;
    LaserShooter m_laserShooter = LSNone;
    pvztime_t m_laserStartTime = 0.f;
    BoardEntityPtr m_laserTarget = nullptr;
    SexyVector2 m_laserPos;
    SexyVector2 m_laserTargetPos;

    RtWeakPtr<class Effect_PopAnim> m_laserRig;
    RtWeakPtr<class Effect_PopAnim> m_laserImpactRig;
    RtWeakPtr<class Effect_PopAnim> m_laserShooterRig;

};

/*
 * 	A customized "BoardArtifactButton" for "artifact_prismtower".
 */
class BoardArtifactButtonWithPrismTower : public BoardArtifactButton
{
public:
	RT_CLASS_DEFINE(BoardArtifactButtonWithPrismTower, BoardArtifactButton, RtClass);

	BoardArtifactButtonWithPrismTower() {}
	~BoardArtifactButtonWithPrismTower() {}

	void Draw(Graphics* i_g) override;
};

enum ArtifactPrismTowerAnimState
{
    Artifact_PrismTower_Activate,
    Artifact_PrismTower_DeActivate
};

/*
 * 	A customized "AnimateArtifactMowerWithPrismTower" for "artifact_prismtower".
 */
class AnimateArtifactMowerWithPrismTower : public AnimateArtifactMower
{
public:
    RT_CLASS_DEFINE(AnimateArtifactMowerWithPrismTower, AnimateArtifactMower, RtClass);

    static AnimateArtifactMowerWithPrismTower* Create() {
        return GameObject::Create<AnimateArtifactMowerWithPrismTower>(PVZDB::TABLE_GAMEOBJECTS);
    }

    void Init(std::string artifactName) override;
    void PlayAnimation(ArtifactAnimState state) override {}
    void PlayPrismTowerAnimation(ArtifactPrismTowerAnimState state);

    SexyVector3 effectPosition;
};

#endif // PLANTSVERSUSZOMBIES2_PVZ2_ARTIFACTPRISMTOWERSUBSYSTEM_H_
