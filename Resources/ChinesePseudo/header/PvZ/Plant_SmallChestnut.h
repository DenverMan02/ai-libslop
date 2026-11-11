//
//  Plant_SmallChestnut.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-4-9.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_SmallChestnut__
#define __PlantsVersusZombies2__Plant_SmallChestnut__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"

class PlantSmallChestnut : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantSmallChestnut, PlantFramework, RtClass);
    void Initialize() override;
    void UpdateActions() override;
    bool CanBeShoveled() override;
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    int CalcRenderOrder() override;
    CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    bool	 CanBeRangeTargeted() override;
    float GetShadowScaling() override;
    void	 PlayAttackAnimation() override;
    void SetDistanceOffsetParent(int range);
    void SetPositioinOffset(const SexyVector2& offset); // the offset make the chestnuts not stacked together
    void SetParent(const PlantPtr& parent);
    void FindTargetAndAttack();
    static bool IsDangerous(const Sexy::Point & grid);
    GridItemPtr FindTargetDamageableGridItem(Rect& i_rect, PlantWeapon i_plantWeapon) override;
private:
    void MoveLeft();
    void MoveRight();
    void SetDirectionLeft(bool left);
    void PlayHitEffect();
    void SetPositionAndUpdateRowColumn(const SexyVector3& oldPos, const SexyVector3& pos);
    bool RightHaveObstacle();
    bool LeftHaveObstacle();
    bool FindThreatInLeft();
    ValueRange GetMoveRange();
    SexyVector3 GetMoveSpeed();
private:
    bool m_left = false;
    int m_distance = 0;
    PlantPtr m_parent;
    SexyVector2 m_offset;
};

class PlantAnimRig_SmallChestnut : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_SmallChestnut, PlantAnimRig, RtClass);
    void PlayRunLooped();
};

class PlantTypeChestnut : public PlantType
{
public:
    RT_CLASS_DEFINE(PlantTypeChestnut, PlantType, RtClass);
    
    void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
};

#endif /* defined(__PlantsVersusZombies2__Plant_SmallChestnut__) */
