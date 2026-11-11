//
//  ICloudListener.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen, Matt McDonald on 3/27/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ICloudListener_h
#define PlantsVersusZombies2_ICloudListener_h

class ICloudListener
{
public:
    // iCloud Account
    
    // iCloud initialized properly without account changes
    virtual void iCloudDidFinishInitialization() {}
    
    // User changed iCloud Account
    virtual void iCloudAccountDidChange() {}
    
    // User signed out iCloud Account
    virtual void iCloudAccountDidSignout() {}
    
    // User launched the app w/iCloud enabled first time
    virtual void iCloudAccountDidSignInFirstTime() {}
    
    // Something goes wrong with iCloud service.
    virtual void iCloudStorageNotAvailable() {}
    
    // iCloud Data Section
    /*
     A value changed in iCloud. This occurs when another device, running another instance of your app and attached to the same iCloud account, uploads a new value.
     */
    virtual void iCloudDataServerChangeWithChangedKeys(const char** keys) {}
    
    /*
     Your attempt to write to key-value storage was discarded because an initial download from iCloud has not yet happened. That is, before you can first write key-value data, the system must ensure that your app’s local, on-disk cache matches the truth in iCloud.
     Initial downloads happen the first time a device is connected to an iCloud account, and when a user switches their primary iCloud account.
     */
    virtual void iCloudDataInitialSyncChange() {}
    
    /*
     key-value store has exceeded its space quota on the iCloud server.
     */
    virtual void iCloudDataQuataViolationChange() {}
    
    /*
     The user has changed the primary iCloud account. The keys and values in the local key-value store have been replaced with those from the new account, regardless of the relative timestamps.
     */
    virtual void iCloudDataAccountChange() {}
    
};

#endif
