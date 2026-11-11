//
//  ConfigUpdateMgr.hpp
//  PlantsVersusZombies2
//
//  Created by chenjd on 16/5/19.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef ConfigUpdateMgr_hpp
#define ConfigUpdateMgr_hpp

#include "AssetsManagerEx.h"
#include "Singleton.h"

class ConfigUpdateMgr : public LazySingleton<ConfigUpdateMgr>, public AssetsManagerDelegateProtocol
{
public:
    
    ConfigUpdateMgr();
    virtual ~ConfigUpdateMgr();
    
    void CheckUpdate();
    
    void Init();
    
    bool IsUpdated() const;
    
    void ForceRestart();
    
    void dispatchEvent(AssetsManagerEx * manager,
                       EventCode code,
                       float percent,
                       float percentByFile,
                       const std::string& assetId,
                       const std::string& message,
                       int curle_code,
                       int curlm_code);
    
protected:
    
    const char* GetRSBFileName() const;
    
    void onRestart();
    
private:
    
    AssetsManagerEx * m_AssetsManagerEx;
    
    int               m_failCount;
    std::string       m_storagePath;
    
    bool              m_updated;
};

#endif /* ConfigUpdateMgr_hpp */
