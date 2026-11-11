//
//  GridSquareCoveringFlame.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/15/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridSquareCoveringFlame__
#define __PlantsVersusZombies2__GridSquareCoveringFlame__

#include "BoardEntity.h"
#include "BoardEnums.h"

class Effect_PopAnim;

class GridSquareCoveringFlame : public BoardEntity
{
public:
    enum ScorchType
    {
        SCORCH_TEMPORARY,
        SCORCH_PERMANENT,
        SCORCH_PERMANENT_EDGE,
    };
    
    RT_CLASS_DEFINE(GridSquareCoveringFlame, BoardEntity, RtClass);
    
    GridSquareCoveringFlame();
    
    void StartFlameImpactEffect(Point i_gridLocation, float i_burnTime, BoardEntity* i_owner);
    void StartScorchEffect(Point i_gridLocation, float i_burnTime, BoardEntity* i_owner, const ScorchType i_scorchType);
    void SetOwner(BoardEntity* i_owner);
    bool ShouldDrawShadow() const override { return false; }
    void SetEndOfLifeTime(float i_burnTime);
    
    virtual void EndLife() { Destroy(); }
    
    const Sexy::Point& GetGridLocation() const { return m_gridLocation; }
protected:
    void registerForEvents() override;
    void onUpdate() override;
    void onDestroy() override;
    
    void tryCreateGridScorchEffect();
    void tryPlayScorchedGridOutro();
    
    RtWeakPtr<class Effect_PopAnim> m_flameEffect;
    pvztime_t m_endOfLife;
    
private:
    void onGatherPlantingRestrictions(const Sexy::Point& i_atLocation, const class PlantType* i_plantType, std::vector<PlantingReason> *io_plantingErrors);
    static Sexy::RtWeakPtr<Sexy::PopAnim> getScorchEffect(const ScorchType i_scorchType);
    static const std::string getScorchEffectResourceID(const ScorchType i_scorchType);
    
    virtual const char* getPamName() { return "POPANIM_EFFECTS_ZOMBOSS_DARK_FIREBALL"; }
    virtual const char* getImpactAnimName() { return "impact"; }
    virtual bool doScorchEffect() { return true; }
    virtual float getDPS() { return 5000.0f; }
    virtual void addStartingAnimationSequence(Effect_PopAnim* popAnim);
    virtual BoardEntityTypeFlag getDamageableEntityFlags() { return ENTITYTYPE_PLANT; }
    virtual bool isTargettableZombie(const Zombie* i_zombie);
    
    RtWeakPtr<class Effect_PopAnim> m_scorchEffect;
    BoardEntityPtr m_owner;
    pvztime_t m_spawnScorchAt;
    Point m_gridLocation;
};

#endif /* defined(__PlantsVersusZombies2__GridSquareCoveringFlame__) */
