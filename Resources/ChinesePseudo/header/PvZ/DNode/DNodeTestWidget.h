//
//  DNodeTestWidget.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DNodeTestWidget_h
#define DNodeTestWidget_h

#include "DNodeWidget.h"

class DNodeTestWidget : public DNodeWidget
{
public:
    CREATE_FUNC(DNodeTestWidget)
    
    DNodeTestWidget();
    virtual ~DNodeTestWidget();
    
    virtual void Initialize() override;
};

#endif
