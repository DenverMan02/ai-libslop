/*
 * RiftPlayerInfoBank.h
 *
 *  Created on: 2020-6-8
 *      Author: Administrator
 */

#ifndef RIFTPLAYERINFOBANK_H_
#define RIFTPLAYERINFOBANK_H_

#include "RtObject.h"
#include "UIWidget.h"

class RiftPlayerInfoBank : public UIWidget
{
public:
    RT_CLASS_DEFINE(RiftPlayerInfoBank, UIWidget, RtClass);

    RiftPlayerInfoBank();
    virtual ~RiftPlayerInfoBank();

    // Public Interface (Inheritable)
    virtual void				Draw(Graphics* i_g) override;

protected:
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing);

    virtual void	initLoadingResourcesGroupList() override;

private:
    ImagePtr m_leagueImg;
    SexyString m_titleLabel;
    SexyString m_scoreLabel;
    SexyString m_rankLabel;
    Rect m_titleRect;
    Rect m_scoreRect;
    Rect m_rankRect;
    Rect m_leagueRect;
};


#endif /* RIFTPLAYERINFOBANK_H_ */
