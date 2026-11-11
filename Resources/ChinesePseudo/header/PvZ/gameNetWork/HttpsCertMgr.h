//
//  HttpsCertMgr.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/10/20.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef HttpsCertMgr_h
#define HttpsCertMgr_h

#include "RtDb.h"
#include "core.h"

class HttpsCertMgr : public LazySingleton<HttpsCertMgr>
{
public:
    HttpsCertMgr();
    bool InitHttpsCert();
    bool IsHttpsCertValid() { return m_isCertValid; }
    
private:    
    bool m_isCertValid = false;
};


#endif /* HttpsCertMgr_h */
