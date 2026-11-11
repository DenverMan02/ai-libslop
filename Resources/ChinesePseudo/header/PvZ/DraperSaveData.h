//
//  DraperSaveData.h
//  PlantsVersusZombies2
//
//  Created by Alex Stajos on 5/9/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DraperSaveData__
#define __PlantsVersusZombies2__DraperSaveData__

#include "Precompile.h"
#include "RtObject.h"
#include "RtDb.h"

class DraperSaveData : public RtObject
{
	RT_CLASS_DEFINE(DraperSaveData, RtObject, RtClass);
public:
	DraperSaveData();
	
	time_t                          GetLastPlayTime() const { return m_lastPlayTime; }
    void                            SetLastPlayTime(time_t i_time);
    
    time_t                          GetLastSessionPlayTime() const { return m_lastSessionPlayTime; }
    
    time_t                          GetLastPurchaseTime() const { return m_lastPurchaseTime; }
    void							SetLastPurchaseTimeAndCountAndTotal(time_t i_time, int i_transCnt, int i_purchaseTotal);
	
	long							GetIndex() const { return m_index; }
    void                            SetIndex(long i_index) {m_index = i_index;}
	
	int								GetTransactionCount() const { return m_transactionCount; }
	
	float							GetPurchaseTotal() const { return m_purchaseTotal; }
	
private:
	time_t                          m_lastSessionPlayTime;
    time_t                          m_lastPlayTime;
    time_t                          m_lastPurchaseTime;
	long							m_index;
	int								m_transactionCount;		// How many times this profile has monetized
    float							m_purchaseTotal;		// How much (in USD) we've spent
};

namespace DraperHelpers
{
	DraperSaveData* GetDraperSaveData(int i_profileIndex);
}

#endif /* defined(__PlantsVersusZombies2__DraperSaveData__) */
