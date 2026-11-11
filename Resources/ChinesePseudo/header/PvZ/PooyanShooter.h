//
//  PooyanShooter.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/6/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PooyanShooter__
#define __PlantsVersusZombies2__PooyanShooter__

#include "Plant.h"
#include "BoardEntity.h"

class PooyanShooter : public BoardEntity
{
public:
    RT_CLASS_DEFINE(PooyanShooter, BoardEntity, RtClass);
    
    PooyanShooter();
    virtual ~PooyanShooter();
    
    void MoveShooterTo(Sexy::SexyVector3 i_position);
    void PooyanShooterInitialize(PopAnim* i_popAnim, PopAnim* i_popAnimCore, Plant * i_plantPtr, bool i_enter = false);
    Plant * GetPlantPtr();
    void DeleteCurrentPlant();
    Rect GetPooyanShooterRect();
    void calcCloseAttack();
    bool canMove();
    void onDrawSpaceShip(Graphics* i_g);
    void onDrawCore(Graphics* i_g);
    void setVisible(bool i_visible) { m_visible = i_visible; }
    bool isVisible() { return m_visible; }
    bool IsDead() { return m_isDead; }
    bool IsInvincible() { return GetPlantPtr() ? GetPlantPtr()->IsInvincible() : false; }
    void SetDead(bool i_dead) { m_isDead = i_dead; setVisible(!m_isDead); }
    
    void addToRenderQueue(class RenderQueue* i_queue);
    
protected:
    /// GameObject interface
    virtual void onInitialized() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    // virtual void onDraw(Graphics* i_g);
    //virtual void onDrawShadow(Graphics* i_g);
    virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    
private:
    bool                                        m_visible;
    bool                                        m_isDead;
    bool                                        m_isMoving;
    Sexy::SexyVector3                           m_introPos;
    Sexy::SexyVector3                           m_readyPos;
    Plant *                                     m_plantPtr;
    pvztime_t                                   m_startMovingTime;
    pvztime_t                                   m_lastCloseAttackTime;
    RtWeakPtr<class PopAnimRig>                 m_popAnimRig;
    RtWeakPtr<class PopAnimRig>                 m_popAnimRigCore;
};

namespace Message
{
}

#endif /* defined(__PlantsVersusZombies2__PooyanShooter__) */
