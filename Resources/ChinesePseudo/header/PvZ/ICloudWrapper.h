//
//  ICloudWrapper.h
//  PlantsVersusZombies2
//
//  Created by Matt McDonald on 12/18/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ICloudWrapper_h
#define PlantsVersusZombies2_ICloudWrapper_h

#include <string>

class ICloudListener;
class ICloudWrapperImpl;

class ICloudWrapper
{
public:	
    virtual ~ICloudWrapper(){}
    
	virtual void SetListener(ICloudListener* listener){}
    virtual void StoreStringValue(const std::string& i_key, const std::string& i_value){}
    virtual std::string GetStringValue(const std::string& i_key) { return ""; }
    
    virtual void start(){}
    
    virtual bool Synchronize(){return false;}
    
private:
    void*   m_iCloudHandler;
};
#ifdef HOST_IPHONEOS
class ICloudWrapperImpl : public ICloudWrapper
{
public:
    
    ICloudWrapperImpl();
    virtual ~ICloudWrapperImpl();
    
	virtual void SetListener(ICloudListener* listener);
    virtual void StoreStringValue(const std::string& i_key, const std::string& i_value);
    virtual std::string GetStringValue(const std::string& i_key);
    
    virtual void start();
    
    virtual bool Synchronize();
    
private:
    void*   m_iCloudHandler;
};
#endif // HOST_IPHONEOS
#endif
