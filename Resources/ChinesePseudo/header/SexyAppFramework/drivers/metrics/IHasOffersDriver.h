#pragma once
#ifndef IHASOFFERSDRIVER_H_INCLUDED
#define IHASOFFERSDRIVER_H_INCLUDED

namespace Sexy
{
    class IHasOffersDriver
    {
        
    public:
        static IHasOffersDriver* CreateHasOffersDriver();
        
        typedef std::pair< std::string, std::string > KeyValue;
        typedef std::vector< KeyValue > KeyValueVector;
        
        IHasOffersDriver(){};
        virtual ~IHasOffersDriver(){};
        
        virtual void    Init( const std::string& szAdvertiserId, const std::string& szAppKey ) = 0;
        // SetParameters is used to set arbitrary event parameters on the HasOffers SDK before SendAction is called
        virtual void    SetParamenters( KeyValueVector* parameters ) = 0;
        virtual void    SendAction( const std::string& szAction, KeyValueVector* parameters = NULL ) = 0;
        virtual void    SendPurchaseAction( const std::string& revenueAmount,
                                            const std::string& currencyCode,
                                            IHasOffersDriver::KeyValueVector* parameters ) = 0;
    
    };
}
#endif