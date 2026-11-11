/*
 * PVZ1InfoUI.h
 *
 *  Created on: 2021-8-14
 *      Author: admin
 */

#ifndef PVZ1INFOUI_H_
#define PVZ1INFOUI_H_

#include "UIWidget.h"

class PVZ1InfoUI : public UIWidget
{
public:
    RT_CLASS_DEFINE(PVZ1InfoUI, UIWidget, RtClass);

    PVZ1InfoUI();
    virtual ~PVZ1InfoUI();

    // Public Interface (Inheritable)
    virtual void				Draw(Graphics* i_g) override;

protected:
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing);

    virtual void	initLoadingResourcesGroupList() override;

private:
    SexyString m_themeLabel;
    SexyString m_infoLabel;
    Rect m_themeRect;
    Rect m_infoRect;
};

#endif /* PVZ1INFOUI_H_ */
