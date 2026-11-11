//
//  ToadstoolGas.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/12/17.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef ToadstoolGas_h
#define ToadstoolGas_h

#include "Projectile.h"

class ToadstoolGas : public Projectile
{
public:
    RT_CLASS_DEFINE(ToadstoolGas, Projectile, RtClass);
    
    
protected:
    void onProjectileInitialized() override;
    void onSetInstigator(BoardEntity* i_instigator) override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    bool OnCollideGround() override;

private:
    int m_row;
    
};

#endif /* ToadstoolGas_h */
