// create by lfy
// in 2023.05.18

#ifndef __GRIDITEMSARRACENIAFOSSIL_H__
#define __GRIDITEMSARRACENIAFOSSIL_H__


#include "GridItemGravestone.h"
#include "Board.h"

class GridItemSarraceniaFossil : public GridItemGravestone
{
public:
    RT_CLASS_DEFINE(GridItemSarraceniaFossil, GridItemGravestone, RtClass);

    virtual Sexy::Rect calcCollisionRect() override;
    int CalcRenderOrder() const { return Board::MakeRenderOrder(RENDER_LAYER_ZOMBIE, GetGridY(), 0); }
    void SetStoneHitpoints(float i_hitpoints) { m_stoneHitpoints = i_hitpoints; }
protected:
    // void		onUpdate() override;
    void		onDraw(Graphics* i_g) override;
    void		onGridItemInitialize() override;
    void		onTakeDamage(const DamageInfo& i_damage) override;
    PlantingReason GetCantPlantReason() const override;
private:
    void		drawAnimation(Graphics* i_g);
    void		drawHealthBar(Graphics* i_g);
    float m_stoneHitpoints = 0.0f;
};

#endif
