//
//  DandelionBomb.h
//  PlantsVersusZombies2
//
//  Created by Bokun Zhao on 14-8-22.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DandelionBomb__
#define __PlantsVersusZombies2__DandelionBomb__

#include <iostream>
#include "PopAnimRig.h"
#include "BoardEntity.h"
#include "Plant.h"
#include "Effect_PopAnim.h"

class DandelionBomb : public BoardEntity
{
public:
	RT_CLASS_DEFINE(DandelionBomb, BoardEntity, RtClass);
    
    DandelionBomb();
    
    enum DandelionBomb_State
    {
        STATE_DANDELION_PLANTING = STATE_FRAMEWORK_BEGIN,
        STATE_DANDELION_MOVING,
        STATE_DANDELION_PLANTFOOD_PLANTING,
        STATE_DANDELION_PLANTFOOD_MOVING,
        STATE_DANDELION_FADING
    };
    
    void SetOwner(BoardEntityPtr i_owner);
    void SetAttackCount(int i_count) { m_attackCount = i_count; }
    void SetPlantfood(bool i_isPlantfood);
    void SetAvatar(bool i_isAvatar) { m_isAvatar = i_isAvatar; }
    void SetPlantPos(const SexyVector3& i_pos) { m_plantPos = i_pos; }
    void SetIndex(int i_index) { m_index = i_index; }
    void SetTarget(BoardEntityPtr i_target) { m_target = i_target; }
    PopAnimRigPtr getAnimRig() {return m_animRig;}
    void CreateAnimRig(bool bigBomb = false);
protected:
	virtual void onPlaceOnBoard() override;

private:
    virtual void onInitialized() override;
	virtual void onUpdate() override;
    virtual void onDestroy() override;
    virtual void onDraw(Graphics* i_g) override;
    virtual int CalcRenderOrder() const override;
    
    void findTarget();
    void setState(uint i_plantState);
    void dropBomb();
    void calcAreaDamage(int i_posX, int i_posY);
    
    void onPlantFinished(const std::string &i_animName);
    void onDieFinished(const std::string &i_animName);
    void onBombExplode(class StandaloneEffect* i_effect);
    void onBombRespawn(const std::string &i_animName);
    
    uint m_state;
    float m_plantSpeed;
    float m_moveSpeed;
    PopAnimRigPtr m_animRig;
    BoardEntityPtr m_owner;
    BoardEntityPtr m_target;
    std::vector<BoardEntityPtr> m_hitTargets;
    SexyVector3 m_plantPos;
    std::vector<SexyVector3> m_explodePos;
    int m_attackRow;
    int m_attackColumn;
    int m_attackCount;
    int m_avatarLastDropCol;
    float m_damage;
    float m_extraDpsModifier;
    
    std::vector<BoardEntityPtr> m_hitEntities;
   
    //Plantfood
    bool m_isPlantfoodAttack;
    bool m_isAvatar;
    int m_index;

    bool m_bigBomb;// if this is a big bomb
    float m_bigBombDamageRatio;// big bomb damage ratio
    float m_roofKeepZ;
};


#endif /* defined(__PlantsVersusZombies2__DandelionBomb__) */
