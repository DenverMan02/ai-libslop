//
//  PVZRechargeCheckServer.h
//  PlantsVersusZombies2
//
//  Created by Leo Wu "Wu Xiangjun" on 13-8-8.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PVZRechargeCheckServer__
#define __PlantsVersusZombies2__PVZRechargeCheckServer__

#include "NetworkServiceManager.h"
#include "PVZDB.h"

namespace Message
{
    void RechargeCheckOnServerComplete();
}

class PVZRechargeCheckServer : public Sexy::NetworkServiceListener
{
public:
    PVZRechargeCheckServer();

    void                RequestRechargeCheck(int i_retries = 0);
    void                TryRequest();
    void                OnRequestFinished(std::string i_json);
    
    void                ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context);
    void                ServiceRequestFailed(const Sexy::StructuredData* i_response, const void* i_context);
    void                ServiceRequestCompleted(ImageLib::Image*&, const void* i_context);
    void                ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context);

    int32               GetPlayerRechargeAmount();
    int32               GetFreeGemAmount();
    int32               GetRechargeGemAmount();
    void                ResetGemAmount();
    bool                IsHacker();
private:
    int32               m_playerRechargeAmount;
    int32               m_playerGetFreeAmount;
    int                 m_retriesLeft;
    int32               m_randomSeed;
    bool                m_isHacker;
};

#endif /* defined(__PlantsVersusZombies2__PVZRechargeCheckServer__) */
