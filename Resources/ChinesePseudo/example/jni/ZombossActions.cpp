#include "ZombossActions.h"
#include "ReflectionBuilder.h"
#include "ZombieWithActions.h"
#include "ZombieZombossMech.h"
#include "ZombieAnimRig_ZombossMech.h"
#include "Board.h"
#include "BoardTransforms.h"
#include "EffectAnimRig_ZombiePortal.h"

#include "SingletonExtern.h"

/* Header */

class ZombossWalkActionDefinition2 : public ZombieActionDefinition
{
public:
    RT_CLASS_DEFINE(ZombossWalkActionDefinition2, ZombieActionDefinition, RtClass);

    ZombossWalkActionDefinition2() {};

    bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions *i_zomboss) const override;

    bool PickWalkTarget(class ZombieZombossMech *i_zomboss, Point &o_targetPosition, ZombossWalkDirection &o_walkDirection) const;

    float WalkVerticalChance = 0.5f;
    float WalkPreferSquashChance = 0.0f;
};


class ZombossWalkActionHandler2 : public ZombieActionHandler
{
public:
    RT_CLASS_DEFINE(ZombossWalkActionHandler2, ZombieActionHandler, RtClass);

    ZombossWalkActionHandler2() {};

    void SetWalkTarget(const Point &i_walkTarget, ZombossWalkDirection i_walkDirection);

protected:
    void onStartAction() override;
    void onUpdateAction() override;
    void onEndAction() override {};

private:
    void buildWalkCurve(const SexyVector3 &i_startPosition, const SexyVector3 &i_endPosition, pvztime_t i_startTime, pvztime_t i_walkDuration, CurveType i_curveType, CurveCollection_Float &i_movementCurves);

    Point m_walkTarget;
    ZombossWalkDirection m_walkDirection = ZombossWalkUp;
    CurveCollection_Float m_movementCurves;
};


class ZombossJumpActionDefinition2 : public ZombieActionDefinition
{
public:
    RT_CLASS_DEFINE(ZombossJumpActionDefinition2, ZombieActionDefinition, RtClass);

    ZombossJumpActionDefinition2() {}

    bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions *i_zomboss) const override;

    float JumpHeight = 200.0f;
    float JumpHangTime = 1.0f;
    float JumpAnimRateModifier = 1.0f;
};

class ZombossJumpActionHandler2 : public ZombieActionHandler
{
public:
    RT_CLASS_DEFINE(ZombossJumpActionHandler2, ZombieActionHandler, RtClass);

    ZombossJumpActionHandler2() {}

    void SetJumpTarget(const Point &i_jumpTarget);

protected:
    void onStartAction() override;
    void onUpdateAction() override;
    void onEndAction() override;
    virtual void onLanding();

private:
    void onJumpStartAnimDone(const std::string &i_animName);

    void buildJumpCurve(const Sexy::SexyVector3 &i_startPosition, const Sexy::SexyVector3 &i_endPosition, float i_apexHeight, pvztime_t i_startTime, pvztime_t i_windupDuration, pvztime_t i_jumpDuration, pvztime_t i_landDuration, CurveCollection_Float &i_movementCurves) const;
    void appendJumpCurve(const Sexy::SexyVector3 &i_startPosition, const Sexy::SexyVector3 &i_endPosition, float i_apexHeight, pvztime_t i_windupDuration, pvztime_t i_jumpDuration, pvztime_t i_landDuration, CurveCollection_Float &i_movementCurves) const;

    CurveCollection_Float m_movementCurves;
    Point m_jumpTarget = Point(-1, -1);
    bool m_jumpMidAir = false;
    pvztime_t m_jumpLandStartTime = PVZ_EOT();
};


class ZombossSpawnActionDefinition2 : public ZombieActionDefinition
{
public:
    RT_CLASS_DEFINE(ZombossSpawnActionDefinition2, ZombieActionDefinition, RtClass);

    ZombossSpawnActionDefinition2() {}

    bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions *i_zomboss) const override;
    void GatherResourceRequirements(std::set<std::string> &io_resourceGroupNames) const override;

    RtWeakPtr<ZombossJumpActionDefinition2> SpawnJumpAction;
    std::vector<std::string> SpawnZombieTypes;
    float SpawnChargeTime = 1.0f;
    float SpawnCooldownTime = 0.0f;
    ValueRange SpawnWavesBetweenPlantFood = ValueRange(1.0f, 1.0f);
    ValueRange SpawnZombieWavePointRange = ValueRange(1500, 7500);
};

class ZombossSpawnActionHandler2 : public ZombieActionHandler
{
public:
    RT_CLASS_DEFINE(ZombossSpawnActionHandler2, ZombieActionHandler, RtClass);

    ZombossSpawnActionHandler2() {}

    void AddToRenderQueue(class RenderQueue *i_queue) override;

protected:
    void onStartAction() override;
    void onUpdateAction() override;
    void onEndAction() override;

private:
    void pickZombiesForSpawn();
    class Zombie *spawnZombie();
    void drawZombieSpawnPortal(Sexy::Graphics *i_graphics);
    int pickPlantfoodSpawnDelay() const;
    bool waveHasPlantfoodCarryingZombie(const std::vector<ZombieTypePtr> i_zombies) const;
    bool isZombieValidForSpawnLocation(const ZombieTypePtr i_zombieType) const;

    void onPortalStartAnimDone(const std::string &i_animName);
    void onPortalStopAnimDone(const std::string &i_animName);
    void onZombiePortalOpenAnimDone(const std::string &i_animName);
    void onZombiePortalCloseAnimDone(const std::string &i_animName);

    std::vector<ZombieTypePtr> m_zombiesToSpawn;
    RtWeakPtr<class EffectAnimRig_ZombiePortal> m_zombiePortalAnim;
    pvztime_t m_portalOpenedTime = PVZ_EOT();
    bool m_spawnedZombie = false;
};


class ZombossRushActionDefinition2 : public ZombieActionDefinition
{
public:
    RT_CLASS_DEFINE(ZombossRushActionDefinition2, ZombieActionDefinition, RtClass);

    ZombossRushActionDefinition2() {}

    bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions *i_zomboss) const override;

    float RushDamageToInterrupt = 100.0f;
    float RushTime = 1.0f;
    float RushLeadupTime = 1.5f;
    float RushLeadupStartRate = 1.0f;
    float RushLeadupEndRate = 1.0f;
    float RushLeadupBackup = 60;
    float RushStartRate = 1.5f;
    float RushEndRate = 8.0f;
    float RushOvershoot = 200.0f;
    std::string RushSound = "Play_Zomb_Egypt_Zomboss_Attack_Rush";
};

class ZombossRushActionHandler2 : public ZombieActionHandler
{
public:
    RT_CLASS_DEFINE(ZombossRushActionHandler2, ZombieActionHandler, RtClass);

    ZombossRushActionHandler2() {}

protected:
    void onStartAction() override;
    void onUpdateAction() override;
    void onEndAction() override;
    void onRushStompAnimDone(const std::string &i_animName);

    virtual bool CheckRushingDone();

    bool m_rushStartedRushing = false;
    CurveSequence_Float m_rushAnimRateCurve;
    CurveCollection_Float m_movementCurves;

protected:
    void startRushForward();
};

/* Header End */

RT_CLASS_IMPLEMENT(ZombossWalkActionDefinition2)
void ZombossWalkActionDefinition2::StaticClassInit()
{
    REFLECTION_CLASSBUILDER_BEGIN(ZombossWalkActionDefinition2);
    REFLECTION_CLASSBUILDER_RTCLASS_BIND;
    REFLECTION_CLASSBUILDER_ANCESTOR(ZombieActionDefinition);

        REFLECTION_CLASSBUILDER_FIELD(float, WalkVerticalChance);
        REFLECTION_CLASSBUILDER_FIELD(float, WalkPreferSquashChance);

    REFLECTION_CLASSBUILDER_END(ZombossWalkActionDefinition2);
}

bool ZombossWalkActionDefinition2::TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions *i_zomboss) const
{
    ZombossWalkDirection walkDirection = ZombossWalkLeft;
    Sexy::Point walkTarget;

    if (PickWalkTarget(i_zomboss->Cast<ZombieZombossMech>(), walkTarget, walkDirection)) {
        i_zomboss->QueueAction<ZombossWalkActionHandler2>(i_actionDef)->SetWalkTarget(walkTarget, walkDirection);
        return true;
    }
    return false;
}

bool ZombossWalkActionDefinition2::PickWalkTarget(class ZombieZombossMech *i_zomboss, Point &o_targetPosition, ZombossWalkDirection &o_walkDirection) const
{
    Point zombossGridPos = i_zomboss->CalcGridPosition();
    std::vector<Point> validPositions;

    if (Rand(1.0f) < WalkVerticalChance) {
        std::vector<Point> tempPositions = i_zomboss->GatherValidAdjacentPositions(true, false);
        validPositions.insert(validPositions.end(), tempPositions.begin(), tempPositions.end());
    }
    if (validPositions.empty()) {
        std::vector<Point> tempPositions = i_zomboss->GatherValidAdjacentPositions(false, true);
        validPositions.insert(validPositions.end(), tempPositions.begin(), tempPositions.end());
    }

    if (Rand(1.0f) < WalkPreferSquashChance) {
        std::vector<Point> filteredPositions;

        for (auto pos : validPositions) {
            if (i_zomboss->IsPositionOverAttackTarget(pos))
                filteredPositions.push_back(pos);
        }
        if (!filteredPositions.empty())
            validPositions = filteredPositions;
    }

    bool foundDirection = false;
    if (!validPositions.empty()) {
        o_targetPosition = validPositions[Rand((int)validPositions.size())];

        if (o_targetPosition.mX < zombossGridPos.mX) {
            o_walkDirection = ZombossWalkLeft;
            foundDirection = true;
        } else if (o_targetPosition.mX == zombossGridPos.mX) {
            if (o_targetPosition.mY < zombossGridPos.mY) {
                o_walkDirection = ZombossWalkUp;
                foundDirection = true;
            } else {
                foundDirection = true;
                if (o_targetPosition.mY > zombossGridPos.mY) {
                    o_walkDirection = ZombossWalkDown;
                }
            }
        } else {
            o_walkDirection = ZombossWalkRight;
            foundDirection = true;
        }
    }

    return foundDirection;
}


RT_CLASS_IMPLEMENT(ZombossWalkActionHandler2)
void ZombossWalkActionHandler2::StaticClassInit()
{
    REFLECTION_CLASSBUILDER_BEGIN(ZombossWalkActionHandler2);
    REFLECTION_CLASSBUILDER_RTCLASS_BIND;
    REFLECTION_CLASSBUILDER_ANCESTOR(ZombieActionHandler);

        REFLECTION_CLASSBUILDER_FIELD(Point, m_walkTarget);
        REFLECTION_CLASSBUILDER_FIELD(ZombossWalkDirection, m_walkDirection);
        REFLECTION_CLASSBUILDER_FIELD(CurveCollection_Float, m_movementCurves);

    REFLECTION_CLASSBUILDER_END(ZombossWalkActionHandler2);
}

void ZombossWalkActionHandler2::SetWalkTarget(const Point &i_walkTarget, ZombossWalkDirection i_walkDirection)
{
    m_walkTarget = i_walkTarget;
    m_walkDirection = i_walkDirection;
}

void ZombossWalkActionHandler2::buildWalkCurve(const SexyVector3 &i_startPosition, const SexyVector3 &i_endPosition, pvztime_t i_startTime, pvztime_t i_walkDuration, CurveType i_curveType, CurveCollection_Float &i_movementCurves)
{
    i_movementCurves.Clear();
    i_movementCurves["x"].StartSequence(i_startTime, i_startPosition.x);
    i_movementCurves["x"].AddCurve(i_walkDuration, i_endPosition.x, i_curveType);
    i_movementCurves["y"].StartSequence(i_startTime, i_startPosition.y);
    i_movementCurves["y"].AddCurve(i_walkDuration, i_endPosition.y, i_curveType);
    i_movementCurves["z"].StartSequence(i_startTime, i_startPosition.z);
    i_movementCurves["z"].AddCurve(i_walkDuration, i_endPosition.z, i_curveType);
}

void ZombossWalkActionHandler2::onStartAction()
{
    SexyVector3 walkTarget(
        BoardTransforms::GridToBoardSpaceX(m_walkTarget.mX),
        BoardTransforms::GridToBoardSpaceY(m_walkTarget.mY),
        0.0f
    );
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();

    PopAnimRig::AnimStoppedReflectionDelegate onAnimStop; 
    zombossMech->GetAnimRig<ZombieAnimRig_ZombossMech>()->PlayWalkForDirection(m_walkDirection, onAnimStop);
    zombossMech->ForceAnimRateModifierForActiveStage();
    pvztime_t animLength = zombossMech->GetAnimRig()->CalcAnimLengthSeconds(zombossMech->GetAnimRig()->CalcPlayingAnimLabelName());

    buildWalkCurve(
        zombossMech->GetPosition(),
        walkTarget,
        zombossMech->GetZomboss_T(),
        zombossMech->GetZomboss_T_Modifier() * animLength,
        CURVE_EASE_IN_OUT,
        m_movementCurves
    );
}

void ZombossWalkActionHandler2::onUpdateAction()
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();
    if (!zombossMech->TryChangeStage()) {
        SexyVector3 position;
        position.x = m_movementCurves["x"][zombossMech->GetZomboss_T()];
        position.y = m_movementCurves["y"][zombossMech->GetZomboss_T()];
        position.z = m_movementCurves["z"][zombossMech->GetZomboss_T()];
        zombossMech->SetPosition(position);
        if (zombossMech->IsPlantfoodedPlantUnderfoot()) {
            zombossMech->DoStun();
        } else {
            zombossMech->KillEntitiesUnderfoot();
            if (!m_movementCurves["x"].IsTimeInSequence(zombossMech->GetZomboss_T()))
                markActionDone();
        }
    }
}


RT_CLASS_IMPLEMENT(ZombossJumpActionDefinition2)
void ZombossJumpActionDefinition2::StaticClassInit()
{
    REFLECTION_CLASSBUILDER_BEGIN(ZombossJumpActionDefinition2);
    REFLECTION_CLASSBUILDER_RTCLASS_BIND;
    REFLECTION_CLASSBUILDER_ANCESTOR(ZombieActionDefinition);

        REFLECTION_CLASSBUILDER_FIELD(float, JumpHeight);
        REFLECTION_CLASSBUILDER_FIELD(float, JumpHangTime);
        REFLECTION_CLASSBUILDER_FIELD(float, JumpAnimRateModifier);

    REFLECTION_CLASSBUILDER_END(ZombossJumpActionDefinition2);
}

//ZombossJumpActionDefinition is not in Zomboss "Actions", so this is never called unless for testing.
bool ZombossJumpActionDefinition2::TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions *i_zomboss) const
{
#if 0
    //Orig code
    i_zomboss->QueueAction<ZombossJumpActionHandler2>(i_actionDef);
#else
    Point jumpTarget;
    i_zomboss->Cast<ZombieZombossMech>()->PickRetreatTarget(jumpTarget);
    i_zomboss->QueueAction<ZombossJumpActionHandler2>(i_actionDef)->SetJumpTarget(jumpTarget);
#endif
    return true;
}


RT_CLASS_IMPLEMENT(ZombossJumpActionHandler2)
void ZombossJumpActionHandler2::StaticClassInit()
{
    REFLECTION_CLASSBUILDER_BEGIN(ZombossJumpActionHandler2);
    REFLECTION_CLASSBUILDER_RTCLASS_BIND;
    REFLECTION_CLASSBUILDER_ANCESTOR(ZombieActionHandler);

        REFLECTION_CLASSBUILDER_FIELD(CurveCollection_Float, m_movementCurves);
        REFLECTION_CLASSBUILDER_FIELD(Point, m_jumpTarget);
        REFLECTION_CLASSBUILDER_FIELD(bool, m_jumpMidAir);
        REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_jumpLandStartTime);
        REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG(onJumpStartAnimDone, onJumpStartAnimDone, const std::string&)

    REFLECTION_CLASSBUILDER_END(ZombossJumpActionHandler2);
}

void ZombossJumpActionHandler2::SetJumpTarget(const Point &i_jumpTarget)
{
    m_jumpTarget = i_jumpTarget;
}

void ZombossJumpActionHandler2::onStartAction()
{
    ZombossJumpActionDefinition2 *zombossJumpDef = getDefinition<ZombossJumpActionDefinition2>();
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();
    ZombieAnimRig_ZombossMech *zombossMechRig = zombossMech->GetAnimRig<ZombieAnimRig_ZombossMech>();

    PopAnimRig::AnimStoppedReflectionDelegate onAnimStop(GetPtr().GetId(), "onJumpStartAnimDone");
    zombossMechRig->PlayJumpStart(onAnimStop);
    zombossMech->SetAnimRateModifier(zombossJumpDef->JumpAnimRateModifier);

    SexyVector3 jumpTarget(
        BoardTransforms::GridToBoardSpaceX(m_jumpTarget.mX),
        BoardTransforms::GridToBoardSpaceY(m_jumpTarget.mY),
        0.0f
    );

    pvztime_t animStartLength = zombossMech->GetAnimRig()->CalcAnimLengthSeconds(zombossMechRig->getJumpStartAnimName());
    pvztime_t animLandLength = zombossMech->GetAnimRig()->CalcAnimLengthSeconds(zombossMechRig->getJumpLandAnimName());

    buildJumpCurve(
        zombossMech->GetPosition(),
        jumpTarget,
        zombossJumpDef->JumpHeight,
        zombossMech->GetZomboss_T(),
        animStartLength,
        zombossJumpDef->JumpHangTime,
        animLandLength,
        m_movementCurves
    );

    m_jumpMidAir = false;
    m_jumpLandStartTime = animStartLength + zombossMech->GetZomboss_T() + zombossJumpDef->JumpHangTime;
}

void ZombossJumpActionHandler2::onUpdateAction()
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();

    zombossMech->UpdatePositionFromCurve(m_movementCurves);

    if (m_jumpMidAir) {
        if (zombossMech->GetZomboss_T() > m_jumpLandStartTime) {
            PopAnimRig::AnimStoppedReflectionDelegate onAnimStop; 
            zombossMech->GetAnimRig<ZombieAnimRig_ZombossMech>()->PlayJumpLand(onAnimStop);
            zombossMech->ForceAnimRateModifierForActiveStage();
            zombossMech->StompEntitiesUnderfoot();
            m_jumpMidAir = false;

            //In CH change for steam zomboss it was:
            //if onLanding == ZombossJumpActionHandler::onLanding {if Plantfooded Plant call DoStun} else {call onLanding}
            //ZombossJumpActionHandler::onLanding and ZombossSteamJumpActionHandler::onLanding were empty
            //Might be releated to optimization somehow, but -fno-inline was set in that build
            onLanding();
        }
        if (m_jumpMidAir && !m_movementCurves["x"].IsTimeInSequence(zombossMech->GetZomboss_T())) {
            markActionDone();
        }
    }
    if (!m_movementCurves["x"].IsTimeInSequence(zombossMech->GetZomboss_T())) {
        markActionDone();
    }
}

void ZombossJumpActionHandler2::onLanding()
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();
    if (zombossMech->IsPlantfoodedPlantUnderfoot())
        zombossMech->DoStun();
}

void ZombossJumpActionHandler2::onEndAction()
{
    getZombie()->Cast<ZombieZombossMech>()->ForceAnimRateModifierForActiveStage();
}

void ZombossJumpActionHandler2::onJumpStartAnimDone(const std::string &i_animName)
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();

    PopAnimRig::AnimStoppedReflectionDelegate onAnimStop; 
    zombossMech->GetAnimRig<ZombieAnimRig_ZombossMech>()->PlayJumpMid(onAnimStop);
    zombossMech->ForceAnimRateModifierForActiveStage();
    m_jumpMidAir = true;
}

void ZombossJumpActionHandler2::buildJumpCurve(const Sexy::SexyVector3 &i_startPosition, const Sexy::SexyVector3 &i_endPosition, float i_apexHeight, pvztime_t i_startTime, pvztime_t i_windupDuration, pvztime_t i_jumpDuration, pvztime_t i_landDuration, CurveCollection_Float &i_movementCurves) const
{
    i_movementCurves.Clear();
    i_movementCurves["x"].StartSequence(i_startTime, i_startPosition.x);
    i_movementCurves["y"].StartSequence(i_startTime, i_startPosition.y);
    i_movementCurves["z"].StartSequence(i_startTime, i_startPosition.z);

    appendJumpCurve(
        i_startPosition,
        i_endPosition,
        i_apexHeight,
        i_windupDuration,
        i_jumpDuration,
        i_landDuration,
        i_movementCurves
    );
}

void ZombossJumpActionHandler2::appendJumpCurve(const Sexy::SexyVector3 &i_startPosition, const Sexy::SexyVector3 &i_endPosition, float i_apexHeight, pvztime_t i_windupDuration, pvztime_t i_jumpDuration, pvztime_t i_landDuration, CurveCollection_Float &i_movementCurves) const
{
    //Unused part from original code
    //SexyVector3 test = ((i_endPosition - i_startPosition) / 2.0f) + i_startPosition;
    //test.z = i_apexHeight;

    i_movementCurves["x"].AddCurve(i_windupDuration, i_startPosition.x, CURVE_CONSTANT);
    i_movementCurves["x"].AddCurve(i_jumpDuration, i_endPosition.x, CURVE_LINEAR);
    i_movementCurves["x"].AddCurve(i_landDuration, i_endPosition.x, CURVE_CONSTANT);
    i_movementCurves["y"].AddCurve(i_windupDuration, i_startPosition.y, CURVE_CONSTANT);
    i_movementCurves["y"].AddCurve(i_jumpDuration, i_endPosition.y, CURVE_LINEAR);
    i_movementCurves["y"].AddCurve(i_landDuration, i_endPosition.y, CURVE_CONSTANT);
    i_movementCurves["z"].AddCurve(i_windupDuration, i_startPosition.z, CURVE_CONSTANT);
    i_movementCurves["z"].AddCurve(i_jumpDuration * 0.5f, i_apexHeight, CURVE_EASE_OUT);
    i_movementCurves["z"].AddCurve(i_jumpDuration * 0.5f, i_endPosition.z, CURVE_EASE_IN);
    i_movementCurves["z"].AddCurve(i_landDuration, i_endPosition.z, CURVE_CONSTANT);
}


RT_CLASS_IMPLEMENT(ZombossSpawnActionDefinition2)
void ZombossSpawnActionDefinition2::StaticClassInit()
{
    REFLECTION_CLASSBUILDER_BEGIN(ZombossSpawnActionDefinition2);
    REFLECTION_CLASSBUILDER_RTCLASS_BIND;
    REFLECTION_CLASSBUILDER_ANCESTOR(ZombieActionDefinition);

        REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<ZombossJumpActionDefinition2>, SpawnJumpAction);
        REFLECTION_CLASSBUILDER_FIELD(std::vector<std::string>, SpawnZombieTypes);
        REFLECTION_CLASSBUILDER_FIELD(float, SpawnChargeTime);
        REFLECTION_CLASSBUILDER_FIELD(float, SpawnCooldownTime);
        REFLECTION_CLASSBUILDER_FIELD(ValueRange, SpawnWavesBetweenPlantFood);
        REFLECTION_CLASSBUILDER_FIELD(ValueRange, SpawnZombieWavePointRange);

    REFLECTION_CLASSBUILDER_END(ZombossSpawnActionDefinition2);
}

bool ZombossSpawnActionDefinition2::TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions *i_zomboss) const
{
    Point jumpTarget;
    i_zomboss->Cast<ZombieZombossMech>()->PickRetreatTarget(jumpTarget);
    i_zomboss->QueueAction<ZombossJumpActionHandler2>(SpawnJumpAction)->SetJumpTarget(jumpTarget);
    i_zomboss->QueueAction<ZombossSpawnActionHandler2>(i_actionDef);
    return true;
}

void ZombossSpawnActionDefinition2::GatherResourceRequirements(std::set<std::string> &io_resourceGroupNames) const
{
    for (auto zombieName : SpawnZombieTypes) {
        gZombieTypeMgr->GetTypeFromTypeName(zombieName)->AddInGameResourceRequirements(io_resourceGroupNames);
    }
}


RT_CLASS_IMPLEMENT(ZombossSpawnActionHandler2)
void ZombossSpawnActionHandler2::StaticClassInit()
{
    REFLECTION_CLASSBUILDER_BEGIN(ZombossSpawnActionHandler2);
    REFLECTION_CLASSBUILDER_RTCLASS_BIND;
    REFLECTION_CLASSBUILDER_ANCESTOR(ZombieActionHandler);

        REFLECTION_CLASSBUILDER_FIELD(std::vector<ZombieTypePtr>, m_zombiesToSpawn); //todo check std::vector<RtWeakPtr<RtObject>>
        REFLECTION_CLASSBUILDER_FIELD(RtWeakPtr<class EffectAnimRig_ZombiePortal>, m_zombiePortalAnim); //RtWeakPtr<RtObject>
        REFLECTION_CLASSBUILDER_FIELD(pvztime_t, m_portalOpenedTime);
        REFLECTION_CLASSBUILDER_FIELD(bool, m_spawnedZombie);
        REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG(onPortalStartAnimDone, onPortalStartAnimDone, const std::string&)
        REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG(onPortalStopAnimDone, onPortalStopAnimDone, const std::string&)
        REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG(onZombiePortalOpenAnimDone, onZombiePortalOpenAnimDone, const std::string&)
        REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG(onZombiePortalCloseAnimDone, onZombiePortalCloseAnimDone, const std::string&)

    REFLECTION_CLASSBUILDER_END(ZombossSpawnActionHandler2);
}

void ZombossSpawnActionHandler2::AddToRenderQueue(class RenderQueue *i_queue)
{
    if (m_zombiePortalAnim.IsValid()) {
        int renderOrder = Board::MakeRenderOrder(RENDER_LAYER_GRAVE_STONE, getZombie()->CalcGridFootprint().mX, 1);
        Delegate1<Sexy::Graphics *> delegate = MakeDelegate(*this, &ZombossSpawnActionHandler2::drawZombieSpawnPortal);
        i_queue->Add(renderOrder, delegate);
    }
}

void ZombossSpawnActionHandler2::drawZombieSpawnPortal(Sexy::Graphics *i_graphics)
{
    if (m_zombiePortalAnim.IsValid()) {
        Rect zombossRect = getZombie()->CalcGridFootprint();
        Point portalGridPos = BoardTransforms::GridToBoardSpace(Point(zombossRect.mX - 1, zombossRect.mY));
        SexyTransform2D portalTransform;
        portalTransform.Translate(S(portalGridPos.mX - 200), S(portalGridPos.mY - 140));
        m_zombiePortalAnim->SetRenderTransform(portalTransform);
        m_zombiePortalAnim->Draw(i_graphics);
    }
}

void ZombossSpawnActionHandler2::onStartAction()
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();
    ZombieAnimRig_ZombossMech *zombossMechRig = zombossMech->GetAnimRig<ZombieAnimRig_ZombossMech>();

    if (zombossMech->GetNextZombieWaveWithPlantfood() == -1)
        zombossMech->SetNextZombieWaveWithPlantfood(pickPlantfoodSpawnDelay());

    pickZombiesForSpawn();
    m_spawnedZombie = false;
    m_portalOpenedTime = PVZ_EOT();

    PopAnimRig::AnimStoppedReflectionDelegate onAnimStop(GetPtr().GetId(), "onPortalStartAnimDone");
    zombossMechRig->PlayPortalStart(onAnimStop);
    zombossMech->ForceAnimRateModifierForActiveStage();

    if (!waveHasPlantfoodCarryingZombie(m_zombiesToSpawn))
        zombossMech->SetNextZombieWaveWithPlantfood(zombossMech->GetNextZombieWaveWithPlantfood() + 1);
}

int ZombossSpawnActionHandler2::pickPlantfoodSpawnDelay() const
{
    ZombossSpawnActionDefinition2 *zombossSpawnDef = getDefinition<ZombossSpawnActionDefinition2>();

    return Rand(
        zombossSpawnDef->SpawnWavesBetweenPlantFood.Max -
        zombossSpawnDef->SpawnWavesBetweenPlantFood.Min + 1
    ) + zombossSpawnDef->SpawnWavesBetweenPlantFood.Min - 1;
}

void ZombossSpawnActionHandler2::pickZombiesForSpawn()
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();
    ZombossSpawnActionDefinition2 *zombossSpawnDef = getDefinition<ZombossSpawnActionDefinition2>();

    float spawnBalance = CurveLerp<float>(
        0.0f, zombossMech->GetMaxHitpoints(),
        zombossMech->GetMaxHitpoints() - zombossMech->GetHitpoints(),
        zombossSpawnDef->SpawnZombieWavePointRange.Min,
        zombossSpawnDef->SpawnZombieWavePointRange.Max,
        CURVE_LINEAR
    );

    MTRand spawnRandom(CalcRandomSeed(SEED_CurrentTime));
    std::set<ZombieTypePtr> zombieTypesForSpawn;
    for (auto zombieName : zombossSpawnDef->SpawnZombieTypes) {
        ZombieTypePtr zombieType = gZombieTypeMgr->GetTypeFromTypeName(zombieName);
        if (isZombieValidForSpawnLocation(zombieType))
            zombieTypesForSpawn.insert(zombieType);
    }

    WaveHelpers::PickZombiesFromPool(spawnBalance, zombieTypesForSpawn, spawnRandom, m_zombiesToSpawn);
}

bool ZombossSpawnActionHandler2::waveHasPlantfoodCarryingZombie(const std::vector<ZombieTypePtr> i_zombies) const
{
    for (auto zombieType : i_zombies) {
        if (zombieType->GetProps()->CanSpawnPlantFood)
            return true;
    }

    return false;
}

bool ZombossSpawnActionHandler2::isZombieValidForSpawnLocation(const ZombieTypePtr i_zombieType) const
{
    Rect zombossRect = getZombie()->CalcGridFootprint();
    int row = 0;

    if (zombossRect.mHeight <= 0)
        return true;
    
    while (true) {
        if (!gLawnApp->m_board->RowCanHaveZombieType(zombossRect.mY + row, i_zombieType))
            return false;
        
        if (zombossRect.mHeight <= ++row)
            return true;
    }
}

void ZombossSpawnActionHandler2::onUpdateAction()
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();

    if (!zombossMech->TryChangeStage()) {
        if (m_zombiePortalAnim.IsValid())
            m_zombiePortalAnim->UpdateAnim(PVZ_T(), PVZ_Dt());

        if (m_portalOpenedTime != PVZ_EOT()) {
            ZombossSpawnActionDefinition2 *zombossSpawnDef = getDefinition<ZombossSpawnActionDefinition2>();

            pvztime_t spawnPeriod = zombossSpawnDef->SpawnChargeTime + zombossSpawnDef->SpawnCooldownTime;
            pvztime_t portalTime = zombossMech->GetZomboss_T() - m_portalOpenedTime;
            if (zombossSpawnDef->SpawnChargeTime < portalTime && !m_spawnedZombie) {
                Zombie *zombie = spawnZombie();
                if (zombie != nullptr) {
                    m_spawnedZombie = true;
                    int plantfoodZombieWave = zombossMech->GetNextZombieWaveWithPlantfood();
                    if (plantfoodZombieWave == zombossMech->GetZombieWaveCounter()) {
                        if (!waveHasPlantfoodCarryingZombie(m_zombiesToSpawn) ||
                            zombie->GetType()->GetProps()->CanSpawnPlantFood &&
                            1.0f / m_zombiesToSpawn.size() > Rand((int)m_zombiesToSpawn.size()) / m_zombiesToSpawn.size()
                        ) {
                            zombie->SetHasPlantFood(true);
                            zombossMech->SetNextZombieWaveWithPlantfood(plantfoodZombieWave + pickPlantfoodSpawnDelay() + 1);
                        }
                    }
                    std::vector<Loot> &zombiesLoot = zombossMech->GetLootForSpawnedZombies();
                    if (m_zombiesToSpawn.empty() && !zombiesLoot.empty())
                        zombie->SetLoot(zombiesLoot.back());
                }
            }
            if (spawnPeriod < portalTime) {
                if (m_zombiesToSpawn.empty()) {
                    m_portalOpenedTime = PVZ_EOT();
                    ZombieAnimRig_ZombossMech *zombossMechRig = zombossMech->GetAnimRig<ZombieAnimRig_ZombossMech>();

                    PopAnimRig::AnimStoppedReflectionDelegate onPortalAnimStop(GetPtr().GetId(), "onPortalStopAnimDone");
                    zombossMechRig->PlayPortalEnd(onPortalAnimStop);
                    PopAnimRig::AnimStoppedReflectionDelegate onZombiePortalAnimStop(GetPtr().GetId(), "onZombiePortalCloseAnimDone");
                    m_zombiePortalAnim->PlayClose(onZombiePortalAnimStop);

                    zombossMech->ForceAnimRateModifierForActiveStage();
                } else {
                    m_spawnedZombie = false;
                    m_portalOpenedTime = zombossMech->GetZomboss_T();
                }
            }
        }
    }
}

class Zombie *ZombossSpawnActionHandler2::spawnZombie()
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();
    Rect zombossRect = getZombie()->CalcGridFootprint();
    Board::SpawnZombieParams spawnParams;

    int zombieSpawnGridX = zombossRect.mX - 1;
    int zombieSpawnGridY = zombossRect.mY + Rand(zombossRect.mHeight);
    if (zombieSpawnGridY < 0)
        zombieSpawnGridY = 0;

    if (m_zombiesToSpawn.empty())
        return nullptr;

    spawnParams.m_level = zombossMech->GetSummonZombieLevel();
    spawnParams.m_bSkipDifficultLevel = true;

    Zombie *zombie = gLawnApp->m_board->SpawnZombie(m_zombiesToSpawn.back(), ZOMBIE_WAVE_SPECIAL, &spawnParams);
    m_zombiesToSpawn.pop_back();
    Point zombieSpawnGridPos(zombieSpawnGridX, zombieSpawnGridY);
    Point zombieSpawnBoardPos = BoardTransforms::GridToBoardSpace(zombieSpawnGridPos);

    zombie->StartWarpIn();
    SexyVector3 zombieSpawnPos(
        zombieSpawnBoardPos.mX - (BoardConstants::GRIDSQUARE_WIDTH() >> 2),
        zombieSpawnBoardPos.mY,
        0.0f
    );
    zombie->PlaceOnBoard(zombieSpawnPos);

    return zombie;
}

void ZombossSpawnActionHandler2::onEndAction()
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();

    zombossMech->PlayPositionalSound("Play_Zomb_Global_Zomboss_Attack_Portal_End");

    int plantfoodZombieWave = zombossMech->GetNextZombieWaveWithPlantfood();
    if (plantfoodZombieWave == zombossMech->GetZombieWaveCounter())
        zombossMech->SetNextZombieWaveWithPlantfood(plantfoodZombieWave + pickPlantfoodSpawnDelay() + 1);

    zombossMech->IncrementZombieWaveCounter();

    if (m_zombiePortalAnim.IsValid())
        m_zombiePortalAnim->Destroy();
    m_zombiePortalAnim.ClearId();
}

void ZombossSpawnActionHandler2::onPortalStartAnimDone(const std::string &i_animName)
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();
    ZombieAnimRig_ZombossMech *zombossMechRig = zombossMech->GetAnimRig<ZombieAnimRig_ZombossMech>();

    PopAnimRig::LoopingAnimContinuedReflectionDelegate onAnimLoop;
    zombossMechRig->PlayPortalLoop(onAnimLoop);
    zombossMech->ForceAnimRateModifierForActiveStage();

    m_zombiePortalAnim = PopAnimRig::CreateRig(GetPAMByName("POPANIM_EFFECTS_ZOMBOSS_TELEPORTATION_BALL"))->GetPtr();
    PopAnimRig::AnimStoppedReflectionDelegate onAnimStop(GetPtr().GetId(), "onZombiePortalOpenAnimDone");
    m_zombiePortalAnim->PlayOpen(onAnimStop);

    m_portalOpenedTime = zombossMech->GetZomboss_T();
}

void ZombossSpawnActionHandler2::onPortalStopAnimDone(const std::string &i_animName)
{
    markActionDone();
}

void ZombossSpawnActionHandler2::onZombiePortalOpenAnimDone(const std::string &i_animName)
{
    m_zombiePortalAnim->PlayLooped();
}

void ZombossSpawnActionHandler2::onZombiePortalCloseAnimDone(const std::string &i_animName)
{
    m_zombiePortalAnim->Destroy();
}


RT_CLASS_IMPLEMENT(ZombossRushActionDefinition2)
void ZombossRushActionDefinition2::StaticClassInit()
{
    REFLECTION_CLASSBUILDER_BEGIN(ZombossRushActionDefinition2);
    REFLECTION_CLASSBUILDER_RTCLASS_BIND;
    REFLECTION_CLASSBUILDER_ANCESTOR(ZombieActionDefinition);

        REFLECTION_CLASSBUILDER_FIELD(float, RushDamageToInterrupt);
        REFLECTION_CLASSBUILDER_FIELD(float, RushTime);
        REFLECTION_CLASSBUILDER_FIELD(float, RushLeadupTime);
        REFLECTION_CLASSBUILDER_FIELD(float, RushLeadupStartRate);
        REFLECTION_CLASSBUILDER_FIELD(float, RushLeadupEndRate);
        REFLECTION_CLASSBUILDER_FIELD(float, RushLeadupBackup);
        REFLECTION_CLASSBUILDER_FIELD(float, RushStartRate);
        REFLECTION_CLASSBUILDER_FIELD(float, RushEndRate);
        REFLECTION_CLASSBUILDER_FIELD(float, RushOvershoot);
        REFLECTION_CLASSBUILDER_FIELD(std::string, RushSound);

    REFLECTION_CLASSBUILDER_END(ZombossRushActionDefinition2);
}

bool ZombossRushActionDefinition2::TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions *i_zomboss) const
{
    Point zombossGridPos = i_zomboss->CalcGridPosition();
    Rect rushAttackRect(0, zombossGridPos.mY - 1, 10, 2);
    std::vector<BoardEntity *> plantsToTarget;

    EntityFinder::GetEntitiesInGridSquares(plantsToTarget, ENTITYTYPE_PLANT, rushAttackRect);
    if (!plantsToTarget.empty()) {
        i_zomboss->QueueAction<ZombossRushActionHandler2>(i_actionDef);
        return true;
    }

    return false;
}


RT_CLASS_IMPLEMENT(ZombossRushActionHandler2)
void ZombossRushActionHandler2::StaticClassInit()
{
    REFLECTION_CLASSBUILDER_BEGIN(ZombossRushActionHandler2);
    REFLECTION_CLASSBUILDER_RTCLASS_BIND;
    REFLECTION_CLASSBUILDER_ANCESTOR(ZombieActionHandler);

        REFLECTION_CLASSBUILDER_FIELD(bool, m_rushStartedRushing);
        REFLECTION_CLASSBUILDER_FIELD(CurveSequence_Float, m_rushAnimRateCurve);
        REFLECTION_CLASSBUILDER_FIELD(CurveCollection_Float, m_movementCurves);
        REFLECTION_CLASSBUILDER_METHOD_INSTANCE_NORETURN_ONEARG(onRushStompAnimDone, onRushStompAnimDone, const std::string&)

    REFLECTION_CLASSBUILDER_END(ZombossRushActionHandler2);
}

void ZombossRushActionHandler2::onStartAction()
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();
    ZombieAnimRig_ZombossMech *zombossMechRig = zombossMech->GetAnimRig<ZombieAnimRig_ZombossMech>();

    PopAnimRig::AnimStoppedReflectionDelegate onAnimStop(GetPtr().GetId(), "onRushStompAnimDone");
    zombossMechRig->PlayStomp(onAnimStop);
    zombossMech->ForceAnimRateModifierForActiveStage();
}

void ZombossRushActionHandler2::onRushStompAnimDone(const std::string &i_animName)
{
    startRushForward();
}

void ZombossRushActionHandler2::startRushForward()
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();
    ZombossRushActionDefinition2 *zombossRushDef = getDefinition<ZombossRushActionDefinition2>();
    ZombieAnimRig_ZombossMech *zombossMechRig = zombossMech->GetAnimRig<ZombieAnimRig_ZombossMech>();

    m_rushAnimRateCurve.StartSequence(zombossMech->GetZomboss_T(), zombossRushDef->RushLeadupStartRate);
    m_rushAnimRateCurve.AddCurve(zombossRushDef->RushLeadupTime, zombossRushDef->RushLeadupEndRate, CURVE_EASE_IN_OUT);
    m_rushAnimRateCurve.AddCurve(zombossRushDef->RushTime, zombossRushDef->RushEndRate, CURVE_EASE_IN);

    m_movementCurves["x"].StartSequence(zombossMech->GetZomboss_T(), zombossMech->GetPosition().x);
    m_movementCurves["x"].AddCurve(
        zombossRushDef->RushLeadupTime,
        zombossMech->GetPosition().x + zombossRushDef->RushLeadupBackup,
        CURVE_EASE_IN_OUT
    );
    m_movementCurves["x"].AddCurve(
        zombossRushDef->RushTime,
        BoardTransforms::GridToBoardSpaceX(0) - zombossRushDef->RushOvershoot,
        CURVE_EASE_IN
    );

    zombossMech->SetAnimRateModifier(zombossRushDef->RushStartRate);
    zombossMechRig->PlayRushForward();
    m_rushStartedRushing = true;
    zombossMech->PlayPositionalSound(zombossRushDef->RushSound);
}

void ZombossRushActionHandler2::onUpdateAction()
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();
    ZombieAnimRig_ZombossMech *zombossMechRig = zombossMech->GetAnimRig<ZombieAnimRig_ZombossMech>();

    if (!zombossMech->TryChangeStage()) {
        ZombossRushActionDefinition2 *zombossRushDef = getDefinition<ZombossRushActionDefinition2>();

        if (zombossMech->GetPlantfoodDamageCounterValue() <= (zombossMech->GetStunHpFactor() * zombossRushDef->RushDamageToInterrupt)) {
            if (!m_rushStartedRushing || CheckRushingDone())
                return;
            
            SexyVector3 zombossPosition = zombossMech->GetPosition();
            zombossPosition.x = m_movementCurves["x"][zombossMech->GetZomboss_T()];
            zombossMech->SetPosition(zombossPosition);

            if (!zombossMech->IsPlantfoodedPlantUnderfoot()) {
                zombossMech->SetAnimRateModifier(m_rushAnimRateCurve.GetValueAt(zombossMech->GetZomboss_T()));

                std::vector<BoardEntity *> plantsToCheck;
                Point zombossGridPos = zombossMech->CalcGridPosition();
                zombossMech->GatherEntitiesAtPosition(plantsToCheck, ENTITYTYPE_PLANT, zombossGridPos);

                bool blockZomboss = false;
                for (auto plant : plantsToCheck) {
                    //Original code used (Plant *)plant->TryBlockZombossRush(zombossMech);
                    blockZomboss |= plant->Cast<Plant>()->TryBlockZombossRush(zombossMech);
                }

                if (blockZomboss)
                    zombossMech->DoStun();
                else
                    zombossMech->StompEntitiesUnderfoot();

                return;
            }
        }
        zombossMech->DoStun();
    }
}

bool ZombossRushActionHandler2::CheckRushingDone()
{
    ZombieZombossMech *zombossMech = getZombie()->Cast<ZombieZombossMech>();

    if (!m_movementCurves["x"].IsTimeInSequence(zombossMech->GetZomboss_T())) {
        zombossMech->Retreat((ZombieState)ZombossIdle);
        return true;
    }

    return false;
}

void ZombossRushActionHandler2::onEndAction()
{
    getZombie()->Cast<ZombieZombossMech>()->ForceAnimRateModifierForActiveStage();
}
