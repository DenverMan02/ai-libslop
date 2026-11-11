//
//  AdaptorJoustHowToPlayScreen.h
//  PlantsVersusZombies2
//
//  Created by Hoefler, Scarlett on 9/25/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorRiftHowToPlayScreen_h
#define AdaptorRiftHowToPlayScreen_h

#include "AdaptorHowToPlayScreen.h"
#include "HotUIAdaptor.h"
#include "ObjectTypeDescriptor.h"

class AdaptorRiftHowToPlayScreen : public HowToPlayScreen
{
    RT_CLASS_DEFINE(AdaptorRiftHowToPlayScreen, HowToPlayScreen, RtClass);
    
public:

    void ButtonDepress(int i_buttonID) override;
    
protected:
    void onLoadUIView() override;
    void onLayoutFinished() override;
    
private:
    
};

#endif
