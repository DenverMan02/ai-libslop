//
//  LuaUpdateMgr.hpp
//  PlantsVersusZombies2
//
//  Created by chenjd on 16/5/31.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef LuaUpdateMgr_H
#define LuaUpdateMgr_H

#include "AssetsManagerEx.h"
#include "Singleton.h"
#include "PVZ2UIDialog.h"

class LuaUpdateMgr : public LazySingleton<LuaUpdateMgr>, public AssetsManagerDelegateProtocol
{
public:
    
    LuaUpdateMgr();
    virtual ~LuaUpdateMgr();
    
    void CheckUpdate();
    
    void DoUpdate();
    
    bool NeedUpdate() const;
    
    void Init();
    
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
    
    std::string GetPackageRSBFilePath();
    
    void LoadLuaRSB();
    
    void onLuaUpdateCancel();
    void onLuaUpdateOK();
    
    void onWaitingDialogClose();
    
private:
    
    AssetsManagerEx * m_AssetsManagerEx;
    
    PVZ2WaitingDialog * m_waitingDLG;
    
    int               m_failCount;
    std::string       m_storagePath;
    
    bool              m_bNeedUpdate;
    float             m_totalFileSize;
};

#endif /* LuaUpdateMgr_hpp */
