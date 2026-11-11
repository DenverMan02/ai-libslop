#pragma once
#ifndef IOSHASOFFERSDRIVER_H_INCLUDED
#define IOSHASOFFERSDRIVER_H_INCLUDED

#include "IHasOffersDriver.h"

namespace Sexy
{

    class IOSHasOffersDriver : public IHasOffersDriver
    {
    public:
        
        IOSHasOffersDriver();
        virtual ~IOSHasOffersDriver();
    
        virtual void    Init( const std::string& szAdvertiserId, const std::string& szAppKey );
        // SetParameters is used to set arbitrary event parameters on the HasOffers SDK before SendAction is called
        virtual void    SetParamenters( KeyValueVector* parameters );
        virtual void    SendAction( const std::string& szAction, IHasOffersDriver::KeyValueVector* parameters = NULL );
        virtual void    SendPurchaseAction(const std::string& revenueAmount,
                                           const std::string& currencyCode,
                                           IHasOffersDriver::KeyValueVector* parameters );
    };
    
}
#endif