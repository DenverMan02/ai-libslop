//
//  Effect_WalrusEarthTile.h
//  PlantsVersusZombies2
//
//  Created by NanLang on 03/13/15.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Effect_WalrusEarthTile_h
#define PlantsVersusZombies2_Effect_WalrusEarthTile_h

#include "RtObject.h"

namespace Message
{
    void RowMissWalrus(int iRow);
    void ColMissWalrus(int iCol);
}

class Effect_WalrusEarthTile : public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(Effect_WalrusEarthTile, Effect_PopAnim, RtClass);
	Effect_WalrusEarthTile();
    
    void SetInitDate(Sexy::Point& pt, pvztime_t iMissTime, bool bfragment = false);
	
protected:
	// Virtual internal dispatches
	void onUpdate() override;
	void onDraw(Graphics* i_g) override;
    void onInitialized() override;
    void registerForEvents() override;
    void onAnimStopped(const std::string& i_animLabel) override;
    void OnGatherPlantingRestrictions(const Sexy::Point& i_gridPosition
                                      , const PlantType* i_plantType,
                                      std::vector<PlantingReason>* io_plantingReasons);
    
    void OnRowMissWalrus(int iRow);
    void OnColMissWalrus(int iCol);
    
    void MissSelf();
    
private:
    
    Sexy::Point m_GridPoint;
    
    bool m_bMissing;
    
    bool m_bFragment;
    
    pvztime_t m_iMissTime;
	
};



#endif
