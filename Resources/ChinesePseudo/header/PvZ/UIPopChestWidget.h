/*
 * UIPopChestWidget.h
 *
 *  Created on: 2020-6-9
 *      Author: zhousen
 */

#ifndef UIPOPCHESTWIDGET_H_
#define UIPOPCHESTWIDGET_H_

#include "DNode/DNodeWidget.h"
#include "ResourceHelpers.h"
#include "NetworkData.h"

class UIPopChestWidget : public DNodeWidget
{
public:
    CREATE_FUNC(UIPopChestWidget);

    UIPopChestWidget();
    virtual ~UIPopChestWidget();

    virtual void Initialize() override;

    static UIPopChestWidget* Create(std::vector<S2C_BonusInfo> list);
    void setEndCallBack(const std::function<void(DTransformNode*)>& i_callBack) { m_endCallFunc = i_callBack; };
protected:
    void Initialize(std::vector<S2C_BonusInfo> list);

protected:
    class DAnimNode* _chestAnim;
    bool _bBoxIsOpen = false;
    std::function<void(DTransformNode*)>        m_endCallFunc;
};

#endif /* UIPOPCHESTWIDGET_H_ */
