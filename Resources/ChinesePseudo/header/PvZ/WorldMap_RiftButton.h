/*
 * WorldMap_RiftButton.h
 *
 *  Created on: 2020-5-27
 *      Author: Administrator
 */

#ifndef WORLDMAP_RIFTBUTTON_H_
#define WORLDMAP_RIFTBUTTON_H_

#include "UIEasyButtonWidget.h"
//#include "GameEventMgr.h"

class WorldMap_RiftButton : public UIEasyButtonWidget
{

public:
    RT_CLASS_DEFINE(WorldMap_RiftButton, UIEasyButtonWidget, RtClass);

    WorldMap_RiftButton();
    virtual ~WorldMap_RiftButton();

    void WaitForTutorialClick()
    {
        m_clicked = false;
    }
    bool WasClickedForTutorial()
    {
        return m_clicked;
    }

    void            DoPressButton();
    bool            CheckActivated();

protected:
    void            onNetworkError(int erroId);

private:
    void 			onRiftNetworkResponse(int i_context, int i_status);
    void			onSuccessResponse();
    void            onWorldLoaded();

    bool                m_clicked;
};


#endif /* WORLDMAP_RIFTBUTTON_H_ */
