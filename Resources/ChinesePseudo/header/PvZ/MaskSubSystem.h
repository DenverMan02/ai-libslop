//
//  MaskSubSystem.h
//  PlantsVersusZombies2
//
//  Created by Li, Jie (Jeffty) on 15/8/6.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MaskSubSystem__
#define __PlantsVersusZombies2__MaskSubSystem__

#include "GameSubSystem.h"
#include "BoardEntity.h"
#include "RtReflectionDelegate.h"
#include "RenderQueue.h"


class MaskSubSystem : public GameSubSystem
{
    RT_CLASS_DEFINE(MaskSubSystem, GameSubSystem, RtClass);
    
    void DrawMaskItemList(Graphics* g, RenderItem* pMaskItemList, uint32 maskItemCount);
    
    void StartTestStencil(Graphics* g);
    void EndTestStencil(Graphics* g);
    
protected:
    void onInitialized() override;
    void registerForEvents() override;
    
    void StartUpdateStencil(Graphics* g);
    void EndUpdateStencil(Graphics* g);
    
    static bool RenderItemSortFunc(const RenderItem &i_item1, const RenderItem &i_item2);
};

#endif /* defined(__PlantsVersusZombies2__MaskSubSystem__) */
