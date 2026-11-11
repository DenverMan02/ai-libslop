//
//  OakArrowUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-10-28.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__OakArrowUI__
#define __PlantsVersusZombies2__OakArrowUI__

#include "UIWidget.h"
#include "OakTrainModule.h"

class OakArrowUI : public UIWidget
{
public:
    RT_CLASS_DEFINE(OakArrowUI, UIWidget, RtClass);
	
	OakArrowUI();
	virtual ~OakArrowUI(){}
    
	virtual void Draw(Graphics* i_g) override;
	virtual bool OnTouch(const Sexy::Touch& i_touch) override;
    
    void         SetArrowType(oak_arrow_type i_type);
    int          GetArrowType() const;
    
    void         SetArrowCount(int i_count);
    int          GetArrowCount() const;
    
    void         SetCanCoolDown(bool i_canCoolDown);
    
    bool         IsInCoolDown() const;
    
    void         SetArrowSelect(bool i_select);
    bool         IsArrowSelect() const;
    
protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;
	virtual void onUpdate() override;
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
    
    void         onOakArrowHitted(const int i_target_type, const int i_count);
    
private:
    
    int         m_arrow_type;
    int         m_arrow_count;
    
    bool        m_IsSelected;
    
    ImagePtr    m_arrowImage;
	ImagePtr	m_arrowDownImage;
    
    bool        m_canCoolDown;
    bool        m_isInCoolDown;
	float       m_timeRemaining;
};

#endif /* defined(__PlantsVersusZombies2__OakArrowUI__) */
