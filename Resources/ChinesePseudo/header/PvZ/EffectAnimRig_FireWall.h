//
//  EffectAnimRig_FireWall.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-9-24.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_EffectAnimRig_FireWall_h
#define PlantsVersusZombies2_EffectAnimRig_FireWall_h

#include "PopAnimRig.h"

class GridItemFireWall;
class EffectAnimRig_FireWall : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_FireWall, PopAnimRig, RtClass);
    
    EffectAnimRig_FireWall();
    
    virtual ~EffectAnimRig_FireWall();
    
    void onUpdate() override;
    
    void PlayFireWall();
    
    bool IsEnd() { return m_bNeedDestory; }
    
    void SetAvatar(bool isAvatar) { m_bAvatar = isAvatar; }
    
    void SetGridItemFireWall(RtWeakPtr<GridItemFireWall> pGridItemFireWall)
    {
        m_pGridItemFireWall = pGridItemFireWall;
    }
    
private:
    
    void OnPrevousAnimEnd(const std::string& strLabel);
    
    void OnLastAnimEnd(const std::string& strLabel);
    
private:
    
    pvztime_t m_iRunningTime;
    
    bool m_bNeedDestory;
    
    RtWeakPtr<GridItemFireWall> m_pGridItemFireWall;
    
    bool m_bAvatar;
    
};


#endif
